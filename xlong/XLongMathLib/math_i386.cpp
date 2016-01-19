
#include "XLongMathLib.h"


// standard core uses intel 80386 assembler
#if (MATH_CORE == STD_I386)

namespace XLONG_MATH_LIB {


void shl(XLong& a, uint32 n_shifts)
{
	int32 ptr;
    if (!n_shifts) return; // check for 0 shifts

    int int32_length = a.GetInt32Length();
	uint32* pn = a.GetBuffer();

#ifdef OPTIMIZED_SHIFTS
	// faster
	int32 n_int32 = (n_shifts >> 5);
	if (n_int32 > 0)
	{
		n_shifts = n_shifts & 31;
		
		ptr = a.GetInt32Length()-1;
		while (ptr >= n_int32)
		{
			pn[ptr] = pn[ptr-n_int32];
			ptr--;
		
		}
		while (ptr >= 0)
		{
			pn[ptr] = 0;
			ptr--;
		}
	}

    if (!n_shifts) return; // check for 0 shifts

#ifdef FAST_SINGLE_PASS_SHIFT
	// fast single pass shift
	_asm
	{
		pushad
		mov esi,pn
		mov ebx,esi

		mov eax,int32_length
		dec eax		// from int32_length-1
		shl eax,2  // *4
		add esi,eax

		mov ecx,n_shifts
		mov edx,32
		sub edx,ecx

		//boundary conditions
		shl dword ptr [esi],cl
		sub esi,4
l1:		
		mov eax, dword ptr [esi]
		push ecx
		mov ecx,edx
		shr eax,cl
		pop ecx
		or dword ptr [esi+4], eax
		shl dword ptr [esi],cl
		sub esi,4
		cmp esi,ebx
		jae l1           //  ?.. jge  signed/unsigned
		popad
	}
#endif // FAST_SINGLE_PASS_SHIFT
#endif  // OPTIMIZED_SHIFTS

    if (!n_shifts) return; // check for 0 shifts
    
#if !defined(FAST_SINGLE_PASS_SHIFT) 
	 //universal but slow, per-bit, (n_shifts&31)-pass shift
	_asm
    {
        pushad
        mov ecx,n_shifts
l3:
        push ecx
        mov esi,pn
        mov ecx,int32_length
        xor ebx,ebx
        xor edx,edx
        mov edi,edx
        clc
l1:
        mov eax,dword ptr [esi+4*ebx]
        mov edx,edi  // exchange of overflow bit storage
        xor edi,edi  // 
        shl eax,1
        adc edi,0    // mov edi,1 if overflow 
        or eax,edx   // in previous dword to add 1 in next
        mov dword ptr [esi+4*ebx],eax
        inc ebx
        loop l1
        pop ecx
        loop l3

        popad
    }
#endif // !defined(FAST_SINGLE_PASS_SHIFT) 
}


void shr(XLong& a, uint32 n_shifts)
{
	int32 ptr;
    if (!n_shifts) return; // check for 0 shifts

	int int32_length = a.GetInt32Length();
    uint32* pn = a.GetBuffer();

#ifdef OPTIMIZED_SHIFTS
	// faster
	int32 n_int32 = (n_shifts >> 5);
	if (n_int32 > 0)
	{
		n_shifts = n_shifts & 31;
		
		ptr = 0;
		while (ptr < (int32)(a.GetInt32Length()-n_int32))
		{
			pn[ptr] = pn[ptr+n_int32];
			ptr++;
		}
		while (ptr < (int32)a.GetInt32Length())
		{
			pn[ptr] = 0;
			ptr++;
		}
	}
	
    if (!n_shifts) return; // check for 0 shifts

#ifdef FAST_SINGLE_PASS_SHIFT
	// fast single pass shift
	_asm
	{
		pushad

		mov ecx,n_shifts
		mov esi,pn
		mov ebx,int32_length
		dec ebx      // till  int32_length-1
		shl ebx,2    // *4
		add ebx,esi
		mov edx,32
		sub edx,ecx
l1:		
		shr dword ptr [esi],cl
		mov eax,dword ptr [esi+4]
		push ecx
		mov ecx,edx
		shl eax,cl
		pop ecx
		or dword ptr [esi],eax
		add esi,4
		cmp esi,ebx
		jb l1           //  ?.. jl  signed/unsigned
		//boundary conditions
		shr dword ptr [esi],cl
		
		popad
	}
#endif //FAST_SINGLE_PASS_SHIFT
#endif  //OPTIMIZED_SHIFTS
	
    if (!n_shifts) return; // check for 0 shifts
    
#if !defined(FAST_SINGLE_PASS_SHIFT) 
	 // universal but slow, per-bit, (n_shifts&31)-pass shift
	_asm
    {
		pushad

		mov ecx,n_shifts
l3:
        push ecx
        mov esi,pn
        mov ecx,int32_length
        xor ebx,ebx
        xor edx,edx
        mov edi,edx
        clc
l1:
        dec ecx
        mov eax,dword ptr [esi+4*ecx]
        mov edx,edi  // exchange of overflow bit storage
        xor edi,edi  // 
        shr eax,1
        rcr edi,1    // mov edi,0x8000000 if overflow 
        or eax,edx   // in add overflow bit from prev. dword
        
        mov dword ptr [esi+4*ecx],eax
        inc ecx
        loop l1
        pop ecx
        loop l3

        popad
    }
#endif // !defined(FAST_SPASS_SHIFT) 
}

void add(XLong& a, const XLong& b)
{
	int int32_length = a.GetInt32Length();
    uint32* pn = a.GetBuffer();
    uint32* pn2 = b.GetBuffer();

    _asm
    {
        pushad

        mov edi,pn
        mov esi,pn2

        mov ecx,int32_length
        xor ebx,ebx
        clc
        l1:
        mov eax,dword ptr [esi+4*ebx]
        adc dword ptr [edi+4*ebx],eax
        inc ebx
        loop l1

        popad
    }

}

void add(XLong& a, const uint32 b)
{
    int int32_length = a.GetInt32Length();
    uint32* pn = a.GetBuffer();

    _asm
    {
        pushad

        mov edi,pn

        mov ecx,int32_length
        xor ebx,ebx
        clc
        mov eax,b
        add dword ptr [edi+4*ebx],eax
        inc ebx
        mov eax,0
l1:
        adc dword ptr [edi+4*ebx],eax
        inc ebx
        loop l1

        popad
    }
}

void sub(XLong& a, const XLong& b)
{
    int int32_length = a.GetInt32Length();
    uint32* pn = a.GetBuffer();
    uint32* pn2 = b.GetBuffer();

    _asm
    {
        pushad

        mov esi,pn
        mov edi,pn2

        mov ecx,int32_length
        xor ebx,ebx
        clc
        l1:
        mov eax,dword ptr [edi+4*ebx]
        sbb dword ptr [esi+4*ebx],eax
        inc ebx
        loop l1

        popad
    }

}

void sub(XLong& a, const uint32 b)
{
    int int32_length = a.GetInt32Length();
    uint32* pn = a.GetBuffer();
    _asm
    {
        pushad

        mov edi,pn
        mov ecx,int32_length
        xor ebx,ebx
        clc
        mov eax,b
        sub dword ptr [edi+4*ebx],eax
        inc ebx
        mov eax,0
l1:
        sbb dword ptr [edi+4*ebx],eax
        inc ebx
        loop l1

        popad
 
    }
}

void mul(XLong& a, const XLong& b)
{
	XLong t(0, a.GetBitLength());

    int int32_length = a.GetInt32Length(); 

    uint32* pn = a.GetBuffer();
    uint32* pn2 = b.GetBuffer();
    uint32* pn3 = t.GetBuffer();

	_asm  
    {
		pushad
		mov edi,pn2
		xor ecx,ecx
		clc
lb11:
		xor ebx,ebx
		clc
lb1:
		mov esi,pn
		mov eax,dword ptr [esi+4*ecx]
		mul dword ptr [edi+4*ebx]
		add ebx,ecx
		mov esi,pn3
		add dword ptr [esi+4*ebx],eax
		adc dword ptr [esi+4*ebx+4],edx

		inc ebx
		cmp ebx,int32_length
		pushf		// to save flags
		sub ebx,ecx
		popf

		jne lb1

		inc ecx
		cmp ecx,int32_length
		jne lb11

		popad
    }

	a = t;    // 2do shit slow:  a*=b := a=t=a*b.... 
}

void div(const XLong &a,const XLong &b, XLong &quot, XLong &rem)
{
	// may be not needed ?
	/*if (_isBitLenMismatch(other) ||
		_isBitLenMismatch(quot) ||
		_isBitLenMismatch(rem))
	{
		quot = 0;
		rem = 0;
		return;
	}*/

    if (a == 0)    //  0/b =0
    {
		quot = 0;
		rem = 0;
		return;
    }

	if (b == 0)    //  a/0 -> trow divise by zero exception
	{
		// need to implement exception handling !!!
		EXCEPT("div() caused division by zero!"); //2do?!
		quot = 0;
		rem = 0;
		return;
    }
    if (b == 1)    //  a/1 == a 
    {
		quot = a;
		rem = 0;
		return;
    }       

    switch (cmp(a,b))   // compare a to b
    {
    case 0: //  a == b
            quot = 1;
            rem = 0;
            return;
            
    case 2: //  a < b
            quot = 0;
            rem = a;
            return;
            
    case 1: //  a > b
			XLong a1(a);
			XLong b1(b);

			// X/Y == (X/a)/(Y/a)
			// !!! bit 0 is missed ?
			while (!a1.bt(0) && !b1.bt(0)) {shr(a1,1); shr(b1, 1);}
                
			/// div routine by Maxim Kuzmich ///
			int bitptr=0;
			quot=0;
			while (b1 < a1) {shl(b1,1); bitptr++;} 
			if (b1 > a1) {shr(b1,1); bitptr--;} 
			while (bitptr >=0)
			{
				if (a1 >= b1)
				//if ( a1.cmp(b1) != 2 )
				{
					quot.bs(bitptr);
					a1 -=b1;
				}
				/*else //if quotent is not clear
					quotient.bc(bitptr);*/
				shr(b1,1);
				bitptr--;
			}
			rem = a1;
			return;
    }
}


} // namespace XLONG_MATH_LIB 


#endif  // MATH_CORE == STD_I386
