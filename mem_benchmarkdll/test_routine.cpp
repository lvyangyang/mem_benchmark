#include"stdafx.h"
#include "test_routine.h"

int RandomAccess(void *ptr_begin, unsigned long length_test, unsigned long loops)
{
	_asm {
	
		push	ebx
		push	ecx
		push	edx

		mov	ecx, loops; [esp + 12 + 12]; loops to do.

		mov	edx, ptr_begin; [esp + 4 + 12]; ptr to memory chunk.
	
		

		L1:
		mov	edx, ptr_begin; [esp + 4 + 12]
		mov	ebx, length_test; [esp + 8 + 12]

		L2:
		mov eax, [edx]
		mov edx, [eax]
	
		sub ebx,2
		jnz L2

		sub ecx,1
		jnz L1

		pop	edx
		pop	ecx
		pop	ebx
	
	}
	return 0;
}



int Reader(void *ptr_begin, unsigned long length_test, unsigned long loops)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		Reader
		; Purpose:	Reads 32 - bit values sequentially from an area of memory.
		; Params:
		;		[esp + 4] = ptr to memory area
			; 		[esp + 8] = length in bytes
			; 		[esp + 12] = loops
			; ------------------------------------------------------------------------------
			; align 64
			; Reader:
		; _Reader:
		push	ebx
			push	ecx
			push	edx

			mov	ecx, loops; [esp + 12 + 12]; loops to do.

			mov	edx, ptr_begin; [esp + 4 + 12]; ptr to memory chunk.
			mov	ebx, edx; ebx = limit in memory
			add	ebx, length_test; [esp + 8 + 12]

			L1:
		mov	edx, ptr_begin; [esp + 4 + 12]

			L2 :
			mov	eax, [edx]
			mov	eax, [4 + edx]
			mov	eax, [8 + edx]
			mov	eax, [12 + edx]
			mov	eax, [16 + edx]
			mov	eax, [20 + edx]
			mov	eax, [24 + edx]
			mov	eax, [28 + edx]
			mov	eax, [32 + edx]
			mov	eax, [36 + edx]
			mov	eax, [40 + edx]
			mov	eax, [44 + edx]
			mov	eax, [48 + edx]
			mov	eax, [52 + edx]
			mov	eax, [56 + edx]
			mov	eax, [60 + edx]
			mov	eax, [64 + edx]
			mov	eax, [68 + edx]
			mov	eax, [72 + edx]
			mov	eax, [76 + edx]
			mov	eax, [80 + edx]
			mov	eax, [84 + edx]
			mov	eax, [88 + edx]
			mov	eax, [92 + edx]
			mov	eax, [96 + edx]
			mov	eax, [100 + edx]
			mov	eax, [104 + edx]
			mov	eax, [108 + edx]
			mov	eax, [112 + edx]
			mov	eax, [116 + edx]
			mov	eax, [120 + edx]
			mov	eax, [124 + edx]

			mov	eax, [edx + 128]
			mov	eax, [edx + 132]
			mov	eax, [edx + 136]
			mov	eax, [edx + 140]
			mov	eax, [edx + 144]
			mov	eax, [edx + 148]
			mov	eax, [edx + 152]
			mov	eax, [edx + 156]
			mov	eax, [edx + 160]
			mov	eax, [edx + 164]
			mov	eax, [edx + 168]
			mov	eax, [edx + 172]
			mov	eax, [edx + 176]
			mov	eax, [edx + 180]
			mov	eax, [edx + 184]
			mov	eax, [edx + 188]
			mov	eax, [edx + 192]
			mov	eax, [edx + 196]
			mov	eax, [edx + 200]
			mov	eax, [edx + 204]
			mov	eax, [edx + 208]
			mov	eax, [edx + 212]
			mov	eax, [edx + 216]
			mov	eax, [edx + 220]
			mov	eax, [edx + 224]
			mov	eax, [edx + 228]
			mov	eax, [edx + 232]
			mov	eax, [edx + 236]
			mov	eax, [edx + 240]
			mov	eax, [edx + 244]
			mov	eax, [edx + 248]
			mov	eax, [edx + 252]

			add	edx, 256
			cmp	edx, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	edx
			pop	ecx
			pop	ebx
	
	}

	return 0;
}

int Writer(void *ptr_begin, unsigned long length_test, unsigned long loops, unsigned long value)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		Writer
		; Purpose:	Writes 32 - bit value sequentially to an area of memory.
		; Params:
		;		[esp + 4] = ptr to memory area
			; 		[esp + 8] = length in bytes
			; 		[esp + 12] = loops
			; 		[esp + 16] = value to write
			; ------------------------------------------------------------------------------
			; align 64
			; Writer:
			; _Writer:
			push	ebx
			push	ecx
			push	edx

			mov	ecx, loops; [esp + 12 + 12]
			mov	eax, value; [esp + 16 + 12]

			mov	edx, ptr_begin; [esp + 4 + 12]; edx = ptr to chunk
			mov	ebx, edx
			add	ebx,  length_test  ; [esp + 8 + 12]; ebx = limit in memory

			L1:
		mov	edx, ptr_begin; [esp + 4 + 12]

			L2 :
			mov[edx], eax
			mov[4 + edx], eax
			mov[8 + edx], eax
			mov[12 + edx], eax
			mov[16 + edx], eax
			mov[20 + edx], eax
			mov[24 + edx], eax
			mov[28 + edx], eax
			mov[32 + edx], eax
			mov[36 + edx], eax
			mov[40 + edx], eax
			mov[44 + edx], eax
			mov[48 + edx], eax
			mov[52 + edx], eax
			mov[56 + edx], eax
			mov[60 + edx], eax
			mov[64 + edx], eax
			mov[68 + edx], eax
			mov[72 + edx], eax
			mov[76 + edx], eax
			mov[80 + edx], eax
			mov[84 + edx], eax
			mov[88 + edx], eax
			mov[92 + edx], eax
			mov[96 + edx], eax
			mov[100 + edx], eax
			mov[104 + edx], eax
			mov[108 + edx], eax
			mov[112 + edx], eax
			mov[116 + edx], eax
			mov[120 + edx], eax
			mov[124 + edx], eax

			mov[edx + 128], eax
			mov[edx + 132], eax
			mov[edx + 136], eax
			mov[edx + 140], eax
			mov[edx + 144], eax
			mov[edx + 148], eax
			mov[edx + 152], eax
			mov[edx + 156], eax
			mov[edx + 160], eax
			mov[edx + 164], eax
			mov[edx + 168], eax
			mov[edx + 172], eax
			mov[edx + 176], eax
			mov[edx + 180], eax
			mov[edx + 184], eax
			mov[edx + 188], eax
			mov[edx + 192], eax
			mov[edx + 196], eax
			mov[edx + 200], eax
			mov[edx + 204], eax
			mov[edx + 208], eax
			mov[edx + 212], eax
			mov[edx + 216], eax
			mov[edx + 220], eax
			mov[edx + 224], eax
			mov[edx + 228], eax
			mov[edx + 232], eax
			mov[edx + 236], eax
			mov[edx + 240], eax
			mov[edx + 244], eax
			mov[edx + 248], eax
			mov[edx + 252], eax

			add	edx, 256
			cmp	edx, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	edx
			pop	ecx
			pop	ebx
		
	}

	return 0;
}

int RandomReader(void *ptr_p, unsigned long n_chunks, unsigned long loops)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		RandomReader
		; Purpose:	Reads 32 - bit values randomly from an area of memory.
		; Params:
		;		[esp + 4] = ptr to array of chunk pointers
			; 		[esp + 8] = # of 128 - byte chunks
			; 		[esp + 12] = loops
			; ------------------------------------------------------------------------------
			; align 64
			; RandomReader:
		; _RandomReader:
		push	ebx
			push	ecx
			push	edx

			mov	ecx, loops; [esp + 12 + 12]; loops to do.

			 L0:
		mov	ebx, n_chunks; [esp + 8 + 12]; # chunks to do

			 L1:
		sub	ebx, 1
			jc L2

			mov	edx, ptr_p; [esp + 4 + 12]; get ptr to memory chunk.
			mov	edx, [edx + 4 * ebx]

			mov	eax, [edx + 160]
			mov	eax, [edx + 232]
			mov	eax, [edx + 224]
			mov	eax, [96 + edx]
			mov	eax, [edx + 164]
			mov	eax, [76 + edx]
			mov	eax, [100 + edx]
			mov	eax, [edx + 220]
			mov	eax, [edx + 248]
			mov	eax, [104 + edx]
			mov	eax, [4 + edx]
			mov	eax, [edx + 136]
			mov	eax, [112 + edx]
			mov	eax, [edx + 200]
			mov	eax, [12 + edx]
			mov	eax, [edx + 128]
			mov	eax, [edx + 148]
			mov	eax, [edx + 196]
			mov	eax, [edx + 216]
			mov	eax, [edx]
			mov	eax, [84 + edx]
			mov	eax, [edx + 140]
			mov	eax, [edx + 204]
			mov	eax, [edx + 184]
			mov	eax, [124 + edx]
			mov	eax, [48 + edx]
			mov	eax, [64 + edx]
			mov	eax, [edx + 212]
			mov	eax, [edx + 240]
			mov	eax, [edx + 236]
			mov	eax, [24 + edx]
			mov	eax, [edx + 252]
			mov	eax, [68 + edx]
			mov	eax, [20 + edx]
			mov	eax, [72 + edx]
			mov	eax, [32 + edx]
			mov	eax, [28 + edx]
			mov	eax, [52 + edx]
			mov	eax, [edx + 244]
			mov	eax, [edx + 180]
			mov	eax, [80 + edx]
			mov	eax, [60 + edx]
			mov	eax, [8 + edx]
			mov	eax, [56 + edx]
			mov	eax, [edx + 208]
			mov	eax, [edx + 228]
			mov	eax, [40 + edx]
			mov	eax, [edx + 172]
			mov	eax, [120 + edx]
			mov	eax, [edx + 176]
			mov	eax, [108 + edx]
			mov	eax, [edx + 132]
			mov	eax, [16 + edx]
			mov	eax, [44 + edx]
			mov	eax, [92 + edx]
			mov	eax, [edx + 168]
			mov	eax, [edx + 152]
			mov	eax, [edx + 156]
			mov	eax, [edx + 188]
			mov	eax, [36 + edx]
			mov	eax, [88 + edx]
			mov	eax, [116 + edx]
			mov	eax, [edx + 192]
			mov	eax, [edx + 144]

			jmp L1

			L2:
		sub	ecx, 1
			jnz L0

			pop	edx
			pop	ecx
			pop	ebx

	
	}

	return 0;

}

int ReaderSSE2(void *ptr_begin, unsigned long length_test, unsigned long loops)
{
	_asm{
		; ------------------------------------------------------------------------------
		; Name:		ReaderSSE2
		; Purpose:	Reads 128 - bit values sequentially from an area of memory.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; ------------------------------------------------------------------------------
		push    eax
		push	ebx
		push	ecx

		mov	ecx, loops; [esp + 12 + 8]

		mov	eax, length_test; [esp + 4 + 8]
		mov	ebx, eax
		add	ebx, ptr_begin; [esp + 8 + 8]; ebx points to end.

			L1:
		mov	eax, ptr_begin; [esp + 4 + 8]

			L2 :
			movdqa	xmm0, [eax]; Read aligned @ 16 - byte boundary.
			movdqa	xmm0, [16 + eax]
			movdqa	xmm0, [32 + eax]
			movdqa	xmm0, [48 + eax]
			movdqa	xmm0, [64 + eax]
			movdqa	xmm0, [80 + eax]
			movdqa	xmm0, [96 + eax]
			movdqa	xmm0, [112 + eax]

			movdqa	xmm0, [128 + eax]
			movdqa	xmm0, [144 + eax]
			movdqa	xmm0, [160 + eax]
			movdqa	xmm0, [176 + eax]
			movdqa	xmm0, [192 + eax]
			movdqa	xmm0, [208 + eax]
			movdqa	xmm0, [224 + eax]
			movdqa	xmm0, [240 + eax]

			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx
			pop eax
			; ret
	
	}

	return 0;


}

int WriterSSE2(void *ptr_begin, unsigned long length_test, unsigned long loops, unsigned long value_write)
{
	_asm {
	
		; ------------------------------------------------------------------------------
		; Name:		WriterSSE2
		; Purpose:	Write 128 - bit values sequentially from an area of memory.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; 		[esp + 16] = value(ignored)
		; ------------------------------------------------------------------------------

		push	ebx
		push	ecx

			mov	eax, value_write; [esp + 16 + 8]
			movd	xmm0, eax; Create a 128 - bit replication of the 32 - bit
			movd	xmm1, eax; value that was provided.
			movd	xmm2, eax
			movd	xmm3, eax
			pslldq	xmm1, 32
			pslldq	xmm2, 64
			pslldq	xmm3, 96
			por	xmm0, xmm1
			por	xmm0, xmm2
			por	xmm0, xmm3

			mov	ecx, loops; [esp + 12 + 8]

			mov	eax, ptr_begin; [esp + 4 + 8]
			mov	ebx, eax
			add	ebx, length_test; [esp + 8 + 8]; ebx points to end.

			L1:
		mov	eax, ptr_begin ;[esp + 4 + 8]

			L2 :
			movdqa[eax], xmm0
			movdqa[16 + eax], xmm0
			movdqa[32 + eax], xmm0
			movdqa[48 + eax], xmm0
			movdqa[64 + eax], xmm0
			movdqa[80 + eax], xmm0
			movdqa[96 + eax], xmm0
			movdqa[112 + eax], xmm0

			movdqa[128 + eax], xmm0
			movdqa[144 + eax], xmm0
			movdqa[160 + eax], xmm0
			movdqa[176 + eax], xmm0
			movdqa[192 + eax], xmm0
			movdqa[208 + eax], xmm0
			movdqa[224 + eax], xmm0
			movdqa[240 + eax], xmm0

			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx
		
	}
	return 0;

}

int CopySSE(void* ptr_s, void* ptr_d, unsigned long length_test, unsigned long loops)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		CopySSE
		; Purpose:	Copies memory chunks that are 16 - byte aligned.
		; Params:	[esp + 4] = ptr to destination memory area
		;		[esp + 8] = ptr to source memory area
		; 		[esp + 12] = length in bytes
		; 		[esp + 16] = loops
		; ------------------------------------------------------------------------------
		;	align 64
		; CopySSE:
		; _CopySSE:
		; Register usage :
		; esi = source
			; edi = dest
			; ecx = loops
			; edx = length
			push	esi
			push	edi
			push	ecx
			push	edx

			mov	edi, ptr_d; [esp + 4 + 16]
			mov	esi, ptr_s; [esp + 8 + 16]
			mov	edx, length_test; [esp + 12 + 16]
			mov	ecx, loops; [esp + 16 + 16]

			shr	edx, 7; Ensure length is multiple of 128.
			shl	edx, 7

			; Save our non - parameter XMM registers.
			sub	esp, 64
			movdqu[esp], xmm4
			movdqu[16 + esp], xmm5
			movdqu[32 + esp], xmm6
			movdqu[48 + esp], xmm7

			L1:
		mov	eax, edx

			L2 :
			movdqa	xmm0, [esi]
			movdqa	xmm1, [16 + esi]
			movdqa	xmm2, [32 + esi]
			movdqa	xmm3, [48 + esi]
			movdqa	xmm4, [64 + esi]
			movdqa	xmm5, [80 + esi]
			movdqa	xmm6, [96 + esi]
			movdqa	xmm7, [112 + esi]

			; 32 - bit lacks xmm8 - xmm15.

			movdqa[edi], xmm0
			movdqa[16 + edi], xmm1
			movdqa[32 + edi], xmm2
			movdqa[48 + edi], xmm3
			movdqa[64 + edi], xmm4
			movdqa[80 + edi], xmm5
			movdqa[96 + edi], xmm6
			movdqa[112 + edi], xmm7

			add	esi, 128
			add	edi, 128

			sub	eax, 128
			jnz L2

			sub	esi, edx; rsi now points to start.
			sub	edi, edx; rdi now points to start.

			dec	ecx
			jnz L1

			movdqu	xmm4, [0 + esp]
			movdqu	xmm5, [16 + esp]
			movdqu	xmm6, [32 + esp]
			movdqu	xmm7, [48 + esp]
			add	esp, 64

			pop	edx
			pop	ecx
			pop	edi
			pop	esi
	
	}
	return 0;

}

int ReaderAVX(void *ptr_begin, unsigned long length_test, unsigned long loops)
{
	_asm {

		; ------------------------------------------------------------------------------
		; Name:		ReaderAVX
		; Purpose:	Reads 256 - bit values sequentially from an area of memory.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; ------------------------------------------------------------------------------
		; align 64
		; ReaderAVX:
		; _ReaderAVX:
			vzeroupper

			push	ebx
			push	ecx

			mov	ecx, loops; [esp + 12 + 8]

			mov	eax, ptr_begin; [esp + 4 + 8]
			mov	ebx, eax
			add	ebx, length_test; [esp + 8 + 8]; ebx points to end.

			L1:
		mov	eax, ptr_begin; [esp + 4 + 8]

			L2 :
			vmovdqa	ymm0, [eax]; Read aligned @ 16 - byte boundary.
			vmovdqa	ymm0, [32 + eax]
			vmovdqa	ymm0, [64 + eax]
			vmovdqa	ymm0, [96 + eax]
			vmovdqa	ymm0, [128 + eax]
			vmovdqa	ymm0, [160 + eax]
			vmovdqa	ymm0, [192 + eax]
			vmovdqa	ymm0, [224 + eax]

			
			
			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx
			

	
	}
	return 0;

}

int WriterAVX(void *ptr_begin, unsigned long length_test, unsigned long loops, unsigned long value)
{
	_asm {
	
		; ------------------------------------------------------------------------------
		; Name:		WriterAVX
		; Purpose:	Write 256 - bit values sequentially from an area of memory.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; 		[esp + 16] = value(ignored)
		; ------------------------------------------------------------------------------
		; align 64
		; WriterAVX:

			vzeroupper

			push	ebx
			push	ecx

			mov	eax, value; [esp + 16 + 8]
			movd	xmm0, eax; Create a 128 - bit replication of the 32 - bit
			movd	xmm1, eax; value that was provided.
			movd	xmm2, eax
			movd	xmm3, eax
			pslldq	xmm1, 32
			pslldq	xmm2, 64
			pslldq	xmm3, 96
			por	xmm0, xmm1
			por	xmm0, xmm2
			por	xmm0, xmm3

			mov	ecx, loops; [esp + 12 + 8]

			mov	eax, ptr_begin; [esp + 4 + 8]
			mov	ebx, eax
			add	ebx, length_test; [esp + 8 + 8]; ebx points to end.

			L1:
			mov	eax, ptr_begin; [esp + 4 + 8]

			L2 :
			vmovdqa[eax], ymm0
			vmovdqa[32 + eax], ymm0
			vmovdqa[64 + eax], ymm0
			vmovdqa[96 + eax], ymm0
			vmovdqa[128 + eax], ymm0
			vmovdqa[160 + eax], ymm0
			vmovdqa[192 + eax], ymm0
			vmovdqa[224 + eax], ymm0

			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx
	
	}
	return 0;
}

int CopyAVX(void* ptr_s, void* ptr_d, unsigned long length_test, unsigned long loops)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		CopyAVX
		; Purpose:	Copies memory chunks that are 32 - byte aligned.
		; Params:	[esp + 4] = ptr to destination memory area
		;		[esp + 8] = ptr to source memory area
		; 		[esp + 12] = length in bytes
		; 		[esp + 16] = loops
		; ------------------------------------------------------------------------------
		; align 64
		; CopyAVX:
		; _CopyAVX:
		vzeroupper
			; Register usage :
		; esi = source
			; edi = dest
			; ecx = loops
			; edx = length
			push	esi
			push	edi
			push	ecx
			push	edx

			mov	edi, ptr_d        ; [esp + 4 + 16]
			mov	esi, ptr_s        ; [esp + 8 + 16]
			mov	edx, length_test  ; [esp + 12 + 16]
			mov	ecx, loops        ; [esp + 16 + 16]

			shr	edx, 8; Ensure length is multiple of 256.
			shl	edx, 8

			L1:
		mov	eax, edx

			L2 :
			vmovdqa	ymm0, [esi]
			vmovdqa	ymm1, [32 + esi]
			vmovdqa	ymm2, [64 + esi]
			vmovdqa	ymm3, [96 + esi]

			vmovdqa[edi], ymm0
			vmovdqa[32 + edi], ymm1
			vmovdqa[64 + edi], ymm2
			vmovdqa[96 + edi], ymm3

			vmovdqa	ymm0, [128 + esi]
			vmovdqa	ymm1, [128 + 32 + esi]
			vmovdqa	ymm2, [128 + 64 + esi]
			vmovdqa	ymm3, [128 + 96 + esi]

			vmovdqa[128 + edi], ymm0
			vmovdqa[128 + 32 + edi], ymm1
			vmovdqa[128 + 64 + edi], ymm2
			vmovdqa[128 + 96 + edi], ymm3

			add	esi, 256
			add	edi, 256

			sub	eax, 256
			jnz L2

			sub	esi, edx; rsi now points to start.
			sub	edi, edx; rdi now points to start.

			dec	ecx
			jnz L1

			pop	edx
			pop	ecx
			pop	edi
			pop	esi
	}

	return 0;
}

int WriterAVX_bypass(void *ptr_begin, unsigned long length_test, unsigned long loops, unsigned long value)
{
	_asm {

		; ------------------------------------------------------------------------------
		; Name:		WriterAVX_bypass
		; Purpose:	Write 256 - bit values sequentially from an area of memory,
		;		bypassing the cache.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; 		[esp + 16] = value(ignored)
		; ------------------------------------------------------------------------------

		; align 64
		; WriterAVX_bypass:
		; _WriterAVX_bypass:
		vzeroupper

			push	ebx
			push	ecx

			mov	eax, value; [esp + 16 + 8]
			movd	xmm0, eax; Create a 128 - bit replication of the 32 - bit
			movd	xmm1, eax; value that was provided.
			movd	xmm2, eax
			movd	xmm3, eax
			pslldq	xmm1, 32
			pslldq	xmm2, 64
			pslldq	xmm3, 96
			por	xmm0, xmm1
			por	xmm0, xmm2
			por	xmm0, xmm3

			mov	ecx, loops; [esp + 12 + 8]

			mov	eax, ptr_begin; [esp + 4 + 8]
			mov	ebx, eax
			add	ebx, length_test; [esp + 8 + 8]; ebx points to end.

			L1:
		mov	eax, ptr_begin; [esp + 4 + 8]

			L2 :
			vmovntdq[eax], ymm0; Write bypassing cache.
			vmovntdq[32 + eax], ymm0
			vmovntdq[64 + eax], ymm0
			vmovntdq[96 + eax], ymm0
			vmovntdq[128 + eax], ymm0
			vmovntdq[160 + eax], ymm0
			vmovntdq[192 + eax], ymm0
			vmovntdq[224 + eax], ymm0

			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx
	
	}

	return 0;
}


int WriterSSE2_bypass(void *ptr_begin, unsigned long length_test, unsigned long loops, unsigned long value)
{
	_asm {
	
		; ------------------------------------------------------------------------------
		; Name:		WriterSSE2_bypass
		; Purpose:	Write 128 - bit values sequentially from an area of memory,
		;		bypassing the cache.
		; Params:	[esp + 4] = ptr to memory area
		; 		[esp + 8] = length in bytes
		; 		[esp + 12] = loops
		; 		[esp + 16] = value(ignored)
		; ------------------------------------------------------------------------------
		; align 64
		; WriterSSE2_bypass:
		; _WriterSSE2_bypass:
			push	ebx
			push	ecx

			mov	eax, value; [esp + 16 + 8]
			movd	xmm0, eax; Create a 128 - bit replication of the 32 - bit
			movd	xmm1, eax; value that was provided.
			movd	xmm2, eax
			movd	xmm3, eax
			pslldq	xmm1, 32
			pslldq	xmm2, 64
			pslldq	xmm3, 96
			por	xmm0, xmm1
			por	xmm0, xmm2
			por	xmm0, xmm3

			mov	ecx, loops; [esp + 12 + 8]

			mov	eax, ptr_begin; [esp + 4 + 8]
			mov	ebx, eax
			add	ebx, length_test; [esp + 8 + 8]; ebx points to end.

			L1:
		mov	eax, ptr_begin; [esp + 4 + 8]

			L2 :
			movntdq[eax], xmm0; Write bypassing cache.
			movntdq[16 + eax], xmm0
			movntdq[32 + eax], xmm0
			movntdq[48 + eax], xmm0
			movntdq[64 + eax], xmm0
			movntdq[80 + eax], xmm0
			movntdq[96 + eax], xmm0
			movntdq[112 + eax], xmm0

			movntdq[128 + eax], xmm0
			movntdq[144 + eax], xmm0
			movntdq[160 + eax], xmm0
			movntdq[176 + eax], xmm0
			movntdq[192 + eax], xmm0
			movntdq[208 + eax], xmm0
			movntdq[224 + eax], xmm0
			movntdq[240 + eax], xmm0

			add	eax, 256
			cmp	eax, ebx
			jb L2

			sub	ecx, 1
			jnz L1

			pop	ecx
			pop	ebx

	
	}

	return 0;
}

int CopySSE_bypass(void* ptr_s, void* ptr_d, unsigned long length_test, unsigned long loops)
{
	_asm {
		; ------------------------------------------------------------------------------
		; Name:		CopySSE
		; Purpose:	Copies memory chunks that are 16 - byte aligned.
		; Params:	[esp + 4] = ptr to destination memory area
		;		[esp + 8] = ptr to source memory area
		; 		[esp + 12] = length in bytes
		; 		[esp + 16] = loops
		; ------------------------------------------------------------------------------
		;	align 64
		; CopySSE_bypass:
		; _CopySSE_bypass:
		; Register usage :
		; esi = source
			; edi = dest
			; ecx = loops
			; edx = length
			push	esi
			push	edi
			push	ecx
			push	edx

			mov	edi, ptr_d; [esp + 4 + 16]
			mov	esi, ptr_s; [esp + 8 + 16]
			mov	edx, length_test; [esp + 12 + 16]
			mov	ecx, loops; [esp + 16 + 16]

			shr	edx, 7; Ensure length is multiple of 128.
			shl	edx, 7

			; Save our non - parameter XMM registers.
			sub	esp, 64
			movdqu[esp], xmm4
			movdqu[16 + esp], xmm5
			movdqu[32 + esp], xmm6
			movdqu[48 + esp], xmm7

			L1 :
		mov	eax, edx

			L2 :
		movntdqa	xmm0, [esi]
			movntdqa	xmm1, [16 + esi]
			movntdqa	xmm2, [32 + esi]
			movntdqa	xmm3, [48 + esi]
			movntdqa	xmm4, [64 + esi]
			movntdqa	xmm5, [80 + esi]
			movntdqa	xmm6, [96 + esi]
			movntdqa	xmm7, [112 + esi]

			; 32 - bit lacks xmm8 - xmm15.

			movntdq[edi], xmm0
			movntdq[16 + edi], xmm1
			movntdq[32 + edi], xmm2
			movntdq[48 + edi], xmm3
			movntdq[64 + edi], xmm4
			movntdq[80 + edi], xmm5
			movntdq[96 + edi], xmm6
			movntdq[112 + edi], xmm7

			add	esi, 128
			add	edi, 128

			sub	eax, 128
			jnz L2

			sub	esi, edx; rsi now points to start.
			sub	edi, edx; rdi now points to start.

			dec	ecx
			jnz L1

			movdqu	xmm4, [0 + esp]
			movdqu	xmm5, [16 + esp]
			movdqu	xmm6, [32 + esp]
			movdqu	xmm7, [48 + esp]
			add	esp, 64

			pop	edx
			pop	ecx
			pop	edi
			pop	esi

	}
	return 0;

}