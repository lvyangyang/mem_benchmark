// sysinfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "processorinfo.h"



// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

int _cdecl getprocessorinfo(processorinfo &thisprocessorinfo)
{
	LPFN_GLPI glpi;
	BOOL done = FALSE;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
	DWORD returnLength = 0;
	DWORD logicalProcessorCount = 0;
	DWORD numaNodeCount = 0;
	DWORD processorCoreCount = 0;
	DWORD processorL1CacheCount = 0;
	DWORD processorL2CacheCount = 0;
	DWORD processorL3CacheCount = 0;
	DWORD processorL1Cachesize=0;
	DWORD processorL2Cachesize=0;
	DWORD processorL3Cachesize=0;
	DWORD processorPackageCount = 0;
	DWORD byteOffset = 0;
	PCACHE_DESCRIPTOR Cache;
	processorinfo myprocessorinfo;

	glpi = (LPFN_GLPI)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")),
		"GetLogicalProcessorInformation");
	if (NULL == glpi)
	{
		_tprintf(TEXT("\nGetLogicalProcessorInformation is not supported.\n"));
		return (1);
	}

	while (!done)
	{
		DWORD rc = glpi(buffer, &returnLength);

		if (FALSE == rc)
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					free(buffer);

				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
					returnLength);

				if (NULL == buffer)
				{
					_tprintf(TEXT("\nError: Allocation failure\n"));
					return (2);
				}
			}
			else
			{
				_tprintf(TEXT("\nError %d\n"), GetLastError());
				return (3);
			}
		}
		else
		{
			done = TRUE;
		}
	}

	ptr = buffer;

	while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
	{
		switch (ptr->Relationship)
		{
		case RelationNumaNode:
			// Non-NUMA systems report a single record of this type.
			numaNodeCount++;
			break;

		case RelationProcessorCore:
			processorCoreCount++;

			// A hyperthreaded core supplies more than one logical processor.
			logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
			break;

		case RelationCache:
			// Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
			Cache = &ptr->Cache;
			if (Cache->Level == 1)
			{
				processorL1CacheCount++;
				if (Cache->Type == CacheData||Cache->Type == CacheUnified)
					processorL1Cachesize += Cache->Size;
			}
			else if (Cache->Level == 2)
			{
				processorL2CacheCount++;
				if (Cache->Type == CacheData || Cache->Type == CacheUnified)
					processorL2Cachesize += Cache->Size;
			}
			else if (Cache->Level == 3)
			{
				processorL3CacheCount++;
				if (Cache->Type == CacheData || Cache->Type == CacheUnified)
					processorL3Cachesize += Cache->Size;
			}
			break;

		case RelationProcessorPackage:
			// Logical processors share a physical package.
			processorPackageCount++;
			break;

		default:
			_tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
			break;
		}
		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}



	thisprocessorinfo.logicalProcessorCount = logicalProcessorCount;
	thisprocessorinfo.numaNodeCount = numaNodeCount;
	thisprocessorinfo.processorCoreCount = processorCoreCount;
	thisprocessorinfo.processorL1CacheCount = processorL1CacheCount;
	thisprocessorinfo.processorL2CacheCount = processorL2CacheCount;
	thisprocessorinfo.processorL3CacheCount = processorL3CacheCount;
	thisprocessorinfo.processorL1Cachesize = processorL1Cachesize;
	thisprocessorinfo.processorL2Cachesize = processorL2Cachesize;
	thisprocessorinfo.processorL3Cachesize = processorL3Cachesize;
	thisprocessorinfo.processorPackageCount = processorPackageCount;

	free(buffer);

	return 0;
}
