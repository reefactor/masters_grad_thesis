
#include "XGaloisLib.h"


// standard core uses intel 80386 assembler
#if (MATH_CORE == STD_I386)

namespace XGALOIS_MATH_LIB {


void add(GF2m& a, const GF2m& b)
{
	///* XOR x and y */

	int int32_length = a.GetInt32Length();
    uint32* pn = a.n;
    uint32* pn2 = b.n;

	if (a == b) 
	{
		a.Clear();
		return;
	}

    _asm
    {
        pushad

        mov edi,pn
        mov esi,pn2

        mov ecx,int32_length
        xor ebx,ebx
        l1:
        mov eax,dword ptr [esi+4*ebx]
        xor dword ptr [edi+4*ebx],eax
        inc ebx
        loop l1

        popad
    }
}

void mul(GF2m& a, const GF2m& b) 
{
	GF2m c(a);
	GF2m d(a);
	c.SetZero();

	//for (uint32 b_bit = 0; b_bit < b.BitLength; b_bit++)
	for (uint32 b_bit = 0; b_bit <= b.GetHighBit(); b_bit++)
	{
		if (b.bt(b_bit))
		{
			c += d;
		}
		inc(d);
	}
	a = c;
}

void inc(GF2m& a)
{
	int HighestShiftedOutBit = 0;
	int i = 0;

	int int32_length = a.GetInt32Length();
	uint32* pn = a.n;

	int LastBlockBitmask = 0;
	if ((a.BitLength % BLOCK_BITLEN) != 0)
	{
		LastBlockBitmask = (1 << (a.BitLength % BLOCK_BITLEN)) - 1;
	}

	_asm
	{
		pushad

		mov edi,pn
		
		mov ecx,int32_length
		xor ebx,ebx
		xor eax,eax
		clc

l1:
		mov edx,eax
		xor eax,eax
		shl dword ptr [edi+4*ebx],1
		adc eax,0
		add dword ptr [edi+4*ebx],edx
		inc ebx
		loop l1

		// now in eax last shifted bit

		cmp LastBlockBitmask, 0
		jz no_mask

		mov ebx, int32_length
		dec ebx
		mov ecx, LastBlockBitmask
		mov HighestShiftedOutBit, 0
		mov edx, dword ptr [edi+4*ebx]
		cmp LastBlockBitmask, edx
		ja done

		mov HighestShiftedOutBit, 1
		and edx, LastBlockBitmask           // trim to real bit length
		mov dword ptr [edi+4*ebx], edx
		jmp done
no_mask:
		mov HighestShiftedOutBit, eax
done:
		popad
	}
	//
	// rotate and mask
	if (HighestShiftedOutBit != 0)
	{
		//
		//a.n[0] |= 1; // shifted out bit is going to lowest bit (rotating element)
		for (i = 0; i < int32_length; i++)
		{
			a.n[i] ^= a.F[i];  //masking field element by F
		}
	}
}

void dec(GF2m& a)
{
	int HighestShiftedOutBit = 0;
	int i = 0;

	int int32_length = a.GetInt32Length();
	uint32* pn = a.n;

	int LastBlockBitmask = 0;
	if ((a.BitLength % BLOCK_BITLEN) != 0)
	{
		LastBlockBitmask = (1 << (a.BitLength % BLOCK_BITLEN)) - 1;
	}

	_asm
	{
		pushad

		mov edi,pn
		
		mov ecx,int32_length
		mov ebx,ecx
		dec ebx
		xor eax,eax
		clc

l1:
		mov edx,eax
		xor eax,eax
		shr dword ptr [edi+4*ebx],1
		adc eax,0
		shl edx,31
		or dword ptr [edi+4*ebx],edx
		dec ebx
		loop l1

		// now in eax last shifted bit
		mov HighestShiftedOutBit, eax

		popad
	}
	//
	// rotate and mask
	if (HighestShiftedOutBit != 0)
	{
		a.bs(a.BitLength-1); // shifted out bit is going to highest bit (rotating element)
		for (i = 0; i < int32_length; i++)
		{
			a.n[i] ^= a.F[i] >> 1;  //masking field element by F
			if (i < (int32_length-1)) 
			{
				a.n[i] ^= ((a.F[i+1] & 1) << 31);
			}

		}
	}
}

} // namespace XGALOIS_MATH_LIB 


#endif  // MATH_CORE == STD_I386
