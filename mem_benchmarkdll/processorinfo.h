#pragma once
#include <windows.h>
#include <malloc.h>    
#include <stdio.h>
#include <tchar.h>



typedef struct processorinfo {
	DWORD logicalProcessorCount;
	DWORD numaNodeCount;
	DWORD processorCoreCount;
	DWORD processorL1CacheCount;
	DWORD processorL2CacheCount;
	DWORD processorL3CacheCount;

	DWORD processorL1Cachesize;
	DWORD processorL2Cachesize;
	DWORD processorL3Cachesize;

	DWORD processorPackageCount;

} processorinfo;



typedef BOOL(WINAPI *LPFN_GLPI)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
	PDWORD);
int _cdecl getprocessorinfo(processorinfo &thisprocessorinfo);