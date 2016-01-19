// LongMathLib.cpp
//
//////////////////////////////////////////////////////////////////////
#include "GF2m.h"
#include "XGaloisLib.h"

namespace XGALOIS_MATH_LIB {


void EXCEPT(const char* alert_str) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(	NULL,alert_str,
				"XGALOIS math library Exception !",MB_ICONERROR || MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nGF2m::EXCEPT(): ",alert_str);
#endif
	CRASH("crash due to exception");
}

void CRASH(const char* info_string) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(NULL,info_string,"GF2m::CRASH() !",MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nGF2m::CRASH(): ",info_string);
#endif
	exit(1);
}

void ALERT(const char* info_string) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(NULL,info_string,"GF2m::ALERT() !",MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nGF2m::ALERT(): ",info_string);
#endif
}

int cmp(const GF2m& a, const uint32 small_number)
{
	// return 0 - equal; 1 - non equal

	//if (a.BitLength > 32) CRASH("fields size mismatch");

    uint32* pn = a.n;
	if (a.GetHighInt32() == 0)
	{
	    if (pn[0] == small_number) return 0;
	}
	return 1;
}

int cmp(const GF2m& a, const GF2m& b)
{
	// return 0 - equal; 1 - non equal

	if (a.BitLength > b.BitLength) CRASH("fields sizes are not equal");

	uint32* pn1 = a.n;
	uint32* pn2 = b.n;

	for (int32 i=a.GetInt32Length(); i >= 0; i--)
    {
        if (pn1[i] != pn2[i]) return 1;
    }
	return 0;
}

/*XLong power(XLong& x, XLong& n)
{
	XLong t(0,x.BitLength);
	XLong result(0,x.BitLength);
	uint32 i = 0;
	result = 1;
	t = x;
	uint32 j = n.Log2();

	while (i <= j )
	{
		if (n.bt(i))	result = result * t;
		t = (t*t);
		i++;
	}
	return result;
}*/

void power(GF2m& a, uint32 b)
{
	GF2m result(a);
	GF2m t(a);

	result.SetOne();
	
	uint32 i = 0;
	uint32 j = 1 << 31;
	while (j > b) j = j >> 1;

	while (i <= j)
	{
		if (b & (1 << i)) 
		{
			result *= t;
		}
		t.Square();
		i++;
	}
	a = result;
}

void power2(GF2m& a, uint32 b)
{
	uint32 j = 0;

	uint32 i = 1 << 31;
	while ((b & i) == 0) 
	{
		i = i >> 1;
		if (i == 0) return;
	}

	b = b ^ i;
	power2(a,b);
	
	j = 0;
	while (i != 0) 
	{
		j++;
		i = i >> 1;
	}
	j--;

	i = 1;
	for (uint32 i1 = 0; i1< j; i1++)
	{
		i = i*2;
	}

	j = i;
	//j = 2 << j; 
	for (uint32 j1 = 0; j1 < j; j1++)
	{
		a.Square();
	}
}


} // namespace XGALOIS_MATH_LIB
