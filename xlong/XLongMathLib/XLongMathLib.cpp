// LongMathLib.cpp
//
//////////////////////////////////////////////////////////////////////
#include "xlong.h"
#include "XLongMathLib.h"

namespace XLONG_MATH_LIB {


void EXCEPT(const char* alert_str) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(	NULL,alert_str,
				"XLong math library Exception !",MB_ICONERROR || MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nXLong::EXCEPT(): ",alert_str);
#endif
	CRASH("crash due to exception");
}

void CRASH(const char* info_string) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(NULL,info_string,"XLong::CRASH() !",MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nXLong::CRASH(): ",info_string);
#endif
	exit(1);
}

void ALERT(const char* info_string) 
{
#ifdef TARGET_IS_WIN32
	MessageBox(NULL,info_string,"XLong::ALERT() !",MB_OK);
#endif
#ifdef ENABLE_DEBUG_CONSOLE
	printf("\nXLong::ALERT(): ",info_string);
#endif
}

int cmp(const XLong& a, const uint32 small_number)
{
    // return values
    // 1: pn1 > pn2
    // 2: pn1 < pn2
    // 0: pn1 = pn2

	uint32* pn = a.GetBuffer();

	//!!! if (GetInt32Length() == 4) then n[3] is the last dword
    for (uint32 i=(a.GetInt32Length()-1);i>=1;i--)
		if (pn[i]) return 1;
    if (pn[0] > small_number) return 1;
    if (pn[0] < small_number) return 2;
    return 0;
}

int cmp(const XLong& a, const XLong& b)
{
    // return values
    // 1: pn1 > pn2
    // 2: pn1 < pn2
    // 0: pn1 = pn2

	uint32* pn1 = a.GetBuffer();
	uint32* pn2 = b.GetBuffer();
	
	if (a.GetHighInt32() > b.GetHighInt32())	return 1;
	else if (a.GetHighInt32() < b.GetHighInt32())	return 2;
	else for (int32 i=a.GetHighInt32(); i >= 0; i--)
    {
        if (pn1[i] > pn2[i]) return 1;
        else
        if (pn1[i] < pn2[i]) return 2;
    }
	return 0;
}


void mod(XLong& a, const XLong& b)
{
	XLong t(0,a.GetBitLength());

	//slow version
	/*
	XLong quotient(GetLength());
	div(other,quotient,remainder);   
	*/

	// fast version:
	for (int bitptr = a.Log2();bitptr >=0;bitptr--)
	{
		shl(t,1);
		if (a.bt(bitptr)) t.bs(0);
		if (t >= b) t -= b;
	}

	a = t;  // shit slow  a=t=a mod b
}




bool evcl(XLong& e,XLong& N, XLong& result)
{
	XLong m(N);
	XLong n(e);
	XLong p(0,e.GetBitLength());
	XLong q(0,e.GetBitLength());
	XLong r(0,e.GetBitLength());
	XLong s(0,e.GetBitLength());
	p=1;
	q=0;
	r=0;
	s=1;

	while (!((m==0)||(n==0)))
	{
		if (m>=n)
		{
			m-=n;
			p-=r;
			q-=s;
		}
		else
		{
			n-=m;
			r-=p;
			s-=q;
		}
	}
	if (m==0)
	{
		result = e*s;
    	if (n != 1) return false;
	    return true;
	}
	else
	{
		result = e*q;
    	if (m != 1) return false;
	    return true;
	}

}

// not optimized draft !
bool GCD(XLong& e,XLong& N, XLong& result)
{
	XLong m(N);
	XLong n(e);
	XLong p(0,e.GetBitLength());
	XLong q(0,e.GetBitLength());
	XLong r(0,e.GetBitLength());
	XLong s(0,e.GetBitLength());
	XLong z1(0,e.GetBitLength());
	p=1;
	q=0;
	r=0;
	s=1;

	//!2OPTIMIZE: replace % and / by div one time 
	while (!((m==0)||(n==0)))
	{

		if (m >= n)	
		{
			z1 = m/n;
			m = m % n;
			p -= r*z1;
			q -= s*z1;
		}
		else
		{
			z1 = n/m;
			n = n % m;
			r -= p*z1;
			s -= q*z1;
		}
	}
	if (m==0)
	{
		result = n;
		return true;
	}
	else
	{
		p += r;
		q += s;
		result = m;
		return true;
	}
}


bool evclm(XLong& e,XLong& N, XLong& result)
{
	XLong m(N);
	XLong n(e);
	XLong p(0,e.GetBitLength());
	XLong q(0,e.GetBitLength());
	XLong r(0,e.GetBitLength());
	XLong s(0,e.GetBitLength());
	XLong z1(0,e.GetBitLength());
	p=1;
	q=0;
	r=0;
	s=1;

	//!2OPTIMIZE: replace % and / by div one time 
	while (!((m==0)||(n==0)))
	{

		if (m >= n)	
		{
			z1 = m/n;
			m = m % n;
			p -= r*z1;
			q -= s*z1;
		}
		else
		{
			z1 = n/m;
			n = n % m;
			r -= p*z1;
			s -= q*z1;
		}
	}
	if (m==0)
	{
		result = e*s;
		if (n != 1) 
		{
			result = 0;
			return false;
		}
		return true;
	}
	else
	{
//		CRASH("evclm:right exc");
		p += r;
		q += s;
		result = e*q;
		if (m != 1) 
		{
			result = 0;
			return false;
		}
		return true;
	}
}

bool evclm(uint32 e,XLong& N, XLong& result)
{
	XLong e1(0,N.GetBitLength());
	e1 = e;
	return (evclm(e1,N,result));

}

bool evclm(uint32 e,uint32 N, XLong& result)
{
	XLong e1(0,result.GetBitLength());
	e1 = e;
	XLong N1(0,result.GetBitLength());
	N1 = N;
	return (evclm(e1,N1,result));

}

inline XLong modexp(const XLong& M, const XLong& exp, const XLong& N)
{
	XLong t(0,M.GetBitLength());
	XLong result(0,M.GetBitLength());
	uint32 i = 0;
	result = 1;
	t = M;

	uint32 j = exp.Log2();

	while (i <= j )
	{
		if (exp.bt(i))
			result = (result * t) % N;
		t = (t*t);
		t = t % N;
		i++;
	}
	return result;

}

XLong power(const XLong& x, const XLong& n)
{
	XLong t(0,x.GetBitLength());
	XLong result(0,x.GetBitLength());
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
}


// find x^(1/n)
XLong root(XLong& x, uint32 n)
{
	XLong a(0,x.GetBitLength()),b(0,x.GetBitLength());

	if (x==0) return XLong(0);

	int32 pbit = x.GetBitLength()-1;
	// get highest bit of x
	while (!x.bt(pbit)) --pbit;

	// initial value
	b.bs( pbit/n + 1 );
	do
	{
		a = b;
		b =  ( a*(n-1) + x/power(a,XLong(n-1,x.GetBitLength())) ) / XLong(n,x.GetBitLength());

	} while (a>b);
  	return a;
}

// Checks if given number if prime 
bool isPrime(XLong& number)
{
	// if number is even it can't ne prime
	if (!number.bt(0)) return false;

	/*
	// algorithm #1 (school like)
	// if (P mod i) == 0, for all (i = 2..t) or (i = 2..sqrt(t))
	// then P is prime 
	//
	XLong i(0,number.GetBitLength());
	XLong t(0,number.GetBitLength());
	t = root(number,2);	//t = number;
	//
    for (i=2; i< t; i++)
    {
        if (number % i == 0)  // check 
            return false;
    }
    return true;*/


/*
	// algorithm #2 (strong)
	// if  M^P,mod P = M, where M <= P
	// then P is prime 
	//
	XLong M(0,number.GetBitLength());
	XLong M1(0,number.GetBitLength());
	M = 2; // any constant < number
#if 1 
	M1 = modexp(M,number,number); 
#else
	M1 = power(M,number);M1 = M1%number;
#endif
	if (M1 == M)
	{
		return true;
	}
*/
	
	
	// algorithm #3 (strongest)
	// if  M^((P-1)/2),mod P = +-1 (1 or P-1), where M <= P
	// then P is prime 
	//
	XLong M(0,number.GetBitLength());
	XLong M1(0,number.GetBitLength());
	M = 2; // any constant
	M1 = modexp(M,(number-1)/2,number);
	if ((M1 == 1) || (M1 == (number-1)))
	{
		//printf("ff");
		return true;
	}
	//
	//
	return false;
}

// Gets first found prime number from numbers greater that left
void getPrime(XLong& left, XLong& prime)
{
	XLong i(0, left.GetBitLength());
	XLong prospective_prime(left);

    if (prospective_prime < 2) prospective_prime = 2-1;

    while (1)
    {
        if (isPrime(prospective_prime)) break;
        ++prospective_prime;
    }
	prime = prospective_prime;
    return;
}


} // namespace XLONG_MATH_LIB
