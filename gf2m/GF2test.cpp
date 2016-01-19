// GF2test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>


//
// 2 important lines need for use of XGalois lib
//
#include "XGaloisLib\XGaloisLib.h"
using namespace XGALOIS_MATH_LIB;

#include "XLongMathLib\XLongMathLib.h"
//using namespace XLONG_MATH_LIB;


static char buf1[1000];
static char buf2[1000];

void print(char* s)
{
        char s1[300];
        CharToOem( s,s1);
        printf(s1);
}


void check_F()
{
	// 33 - 37 - wrong F
	// last checked field: 37
	//GF2m Elem1(37);

	//uint32 Coeffs[] = {1,18};
	//SetFCoeff(19, Coeffs);

	GF2m Elem1(44);
	GF2m Elem2(Elem1);

	long double GFLog = 0;
	long double T = 0;
	//printf("\n %2d: %032s", value_index, Elem1.Print(FMT_BIN, buf1));

	printf("\n GF(2^%d)", Elem1.BitLength);

	Elem1.SetOne();
	Elem2 = Elem1;
	GFLog = 0;
	printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

	Elem1.SetPrimitive();
	GFLog++;
	printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
    //printf("\n");


	T = pow(2,Elem1.BitLength)-1;
	while(!Elem1.isOne())
	{
		//Elem1 = Elem1 * Elem2; // square
		
		Elem1++;
		//Elem1--;
		
		GFLog++;
		
		if (GFLog == T+1) 
		{
		    printf("\n !!! WRONG F(x) ");
			printf("\n ... \nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
			printf("\n GF(2^%d) T= %.0f ", Elem1.BitLength,T );
			//break;
		}
		/*if ((GFLog & 65535) == 0) 
			printf("\rLog = %4d", GFLog);*/

		//printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

		//if 	(Elem2 == Elem1)  printf("\n!!! LOOP Log = %4d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	}
	if (GFLog  == T )  
	{
		printf("\n !!! Found F(x) !!! \n");
		printf("\n ... \nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
		printf("\n GF(2^%d) T= %.0f ", Elem1.BitLength,T );
		getch();

	}
    printf("\n\n\n\n\n");

}


void f1(uint32 order)
{
	// last checked field: 33
	GF2m Elem1(order);
	GF2m Elem2(Elem1);

	long double GFLog = 0;
	long double T = 0;
	//printf("\n %2d: %032s", value_index, Elem1.Print(FMT_BIN, buf1));

	printf("\n GF(2^%d)", Elem1.BitLength);

	T = pow(2,Elem1.BitLength)-1;
	printf("\n GF(2^%d) T= %.0f ", Elem1.BitLength,T );

	long double x1 = 2;
	while (x1 < T) 
	{
		if ( (double)((int)(T / x1)) == (double)(T / x1)) 
		{
			printf(" %.0f,", x1);
		}
		x1++;
	}

	printf("\n\t (%.0f),", T+1);
	x1 = 2;
	while (x1 < T+(double)1) 
	{
		if ( (double)((int)((T+1) / x1)) == (double)((T+1) / x1)) 
		{
			printf(" %.0f,", x1);
		}
		x1++;
	}


	/////////////////////////////////////////////////////////////////////////////


	Elem1.SetPrimitive();

	Elem2 = Elem1;
	Elem2.Inverse();

	Elem1 = Elem2;
	Elem1++;

	printf("\n inverse = %032s", Elem1.Print(FMT_BIN, buf1));

	Elem2.SetPrimitive();
	power2(Elem2,Elem2.BitLength);
	dec(Elem2);
	printf("\n power2  = %032s", Elem2.Print(FMT_BIN, buf1));

	if (Elem1 == 1)
	{
		Elem1.SetOne();
		Elem2 = Elem1;
		GFLog = 0;
		printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

		Elem1.SetPrimitive();
		GFLog++;
		printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

		GFLog = 1;
		Elem1.SetPrimitive();
		while(GFLog < T)
		{
			//Elem1 = Elem1 * Elem2; // square
			Elem1++;
			GFLog++;

			//printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
			if (Elem1.isOne()) 
			{
				printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
				printf(" ***");
				break;
			}
		}

		printf("\n !!! Found F(x) !!! \n");
		getch();
	}


	
	/*while(!Elem1.isOne())
	{
		//Elem1 = Elem1 * Elem2; // square
		Elem1++;
		GFLog++;
		
		if (GFLog > T) 
		{
		    printf("\n !!! WRONG F(x) ");
			break;
		}
		//if ((GFLog & 65535) == 0) printf("\rLog = %4d", GFLog);

		printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
		if (Elem1.n[0] == 57) printf("\t***");

		//if 	(Elem2 == Elem1)  printf("\n!!! LOOP Log = %4d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	}

	printf("\n ... \nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	printf("\n GF(2^%d) T= %.0f ", Elem1.BitLength,T );


	if (GFLog  == T )  
	{
		printf("\n !!! Found F(x) !!! \n");
		getch();

	}*/

	/////////////////////////////////////////////////////////////////////////////
    printf("\n\n");
}

void check_prime_F()
{
	

	int i = 0;
	uint32* F_coeffs = NULL;
	/*for (i = 0; i < (sizeof(F_Table)/sizeof(F_entry)); i++)
	{
		if (F_Table[i].F_order == 8) 
		{
			F_coeffs = F_Table[i].F_coeffs;
			break;
		
		}
	}*/


#define CHECKING_ORDER 8

	XLONG_MATH_LIB::XLong prime1,order,x1;

	prime1.bs(CHECKING_ORDER);
	prime1.bs(0);

	int k = 0;
    while (prime1.Log2() < CHECKING_ORDER+1) 
    {
		prime1++;prime1++;
		//prime1++; while (!XLONG_MATH_LIB::isPrime(prime1)) prime1++;
			
		

		k = 0;
		for (int j = 1; j < prime1.Log2()-1;j++)
		{
			if (prime1.bt(j))
			{
				//F_coeffs[k] = j;
				GetFTable()[CHECKING_ORDER-1].Coeffs[k] = j;
				k++;
			}
			GetFTable()[CHECKING_ORDER-1].Coeffs[k] = 0;
		}

		printf("\n F(x)= %s (%s)", prime1.Print(buf1), prime1.Print(XLONG_MATH_LIB::FMT_BIN, buf2) );

		if (XLONG_MATH_LIB::isPrime(prime1))
		{
			printf(" prime");
		}
		else
		{
			x1 = 2;
			while (x1 < prime1) 
			{
				if ( (prime1 % x1) == 0) 
				{
					printf(" %s,", x1.Print(XLONG_MATH_LIB::FMT_DEC, buf1));
				}
				x1++;
			}
		}

		f1(CHECKING_ORDER);
	}

}

void mul_test()
{
	GF2m Elem1(5);
	GF2m Elem2(5);
	int GFLog = 0;

	Elem1.SetOne();
	Elem2.SetPrimitive();

	GFLog = 0;
	for (int i=0; i<32; i++)
	{
		Elem1 = Elem1 * Elem2; // square
		GFLog++;
		printf("\nLog = %2d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	}

}


void print_GF2_5()
{
	GF2m Elem1(5);
	GF2m Elem2(5);

	int GFLog = 0;
	//printf("\n %2d: %032s", value_index, Elem1.Print(FMT_BIN, buf1));

	Elem1.SetOne();
	GFLog = 0;
	printf("\nLog = %2d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

	Elem1.SetPrimitive();
	GFLog++;
	printf("\nLog = %2d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

	Elem2 = Elem1;
	for (int i=0; i<32; i++)
	{
		//Elem1 = Elem1 * Elem2; // square
		Elem1++;
		GFLog++;
		printf("\nLog = %2d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	}

}

void test_power()
{
	GF2m a(4);
	GF2m b(4);

	a.SetPrimitive();

	printf("\na    = %032s", a.Print(FMT_BIN, buf1));

	for (int i = 1; i< 20; i++)
	{
		b = a;
		power(b,i);
		printf("\na^%2d = %032s", i, b.Print(FMT_BIN, buf1));
	}


}

void test_inverse()
{
	GF2m a(5);
	GF2m b(5);

	a.SetOne();
	for (int i = 1; i< 44; i++)
	{
		b = a;
		printf("\nLog = %d",i);
		printf("\na    = %032s", b.Print(FMT_BIN, buf1));
		
		b.Inverse();
		//power(b,14);

		
		printf("\na^-1 = %032s", b.Print(FMT_BIN, buf1));
		
		//power(b,14);
		b.Inverse();
		
		printf("\na^1  = %032s", b.Print(FMT_BIN, buf1));

		a++;
	}


}

void test_div()
{
	GF2m a(5);
	GF2m b(5);
	GF2m c(5);
	

	a.SetOne();
	for (int i = 1; i< 20; i++)
	{
		b = a;
		b.Inverse();
		c = a*b;

		printf("\nLog = %d",i);
		printf("\na      = %032s", b.Print(FMT_BIN, buf1));
		
		//power(b,14);

		
		printf("\na*a^-1 = %032s", c.Print(FMT_BIN, buf1));
		


		a++;
	}

}


void test_decr()
{

	GF2m Elem1(6);

	long double GFLog = 0;
	long double T = 0;
	//printf("\n %2d: %032s", value_index, Elem1.Print(FMT_BIN, buf1));

	printf("\n GF(2^%d)", Elem1.BitLength);

	Elem1.SetPrimitive();
	GFLog = 1;
	//printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
    //printf("\n");
	Elem1.Inverse();
	printf("\n prim inverse = %032s", Elem1.Print(FMT_BIN, buf1));

	T = pow(2,Elem1.BitLength)-1;
	while(!Elem1.isOne())
	{
		//Elem1 = Elem1 * Elem2; // square
		
		//Elem1++;
		Elem1--;
		
		GFLog++;
		
		if (GFLog > T) 
		{
//		    printf("\n !!! WRONG F(x) ");
//			break;
		}
		/*if ((GFLog & 65535) == 0) 
			printf("\rLog = %4d", GFLog);*/

		printf("\nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));

		//if 	(Elem2 == Elem1)  printf("\n!!! LOOP Log = %4d: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	}
	printf("\n ... \nLog = %10.0f: %032s", GFLog, Elem1.Print(FMT_BIN, buf1));
	printf("\n GF(2^%d) T= %.0f ", Elem1.BitLength,T );
}

test_power2()
{
	//GF2m b(4);
	GF2m* b;

	for (int i=3;i< 50;i++)
	{
		b = new GF2m(i);

		b->SetPrimitive();
		power2(*b,b->BitLength);
	//	b.Square();
		dec(*b);
		printf("\nm=%i  b = %062s",i, b->Print(FMT_BIN, buf1));

		delete b;
	}

	/*b.SetPrimitive();
	power2(b,b.BitLength);
//	b.Square();
	b--;
	printf("\n b = %032s", b.Print(FMT_BIN, buf1));*/
	
}

void SearchF()
{
	GF2m* a;
	GF2m* b;

	for (int i=3;i< 50;i++)
	{
		a = new GF2m(i);
		b = new GF2m(i);

		a->SetOne();
		b->SetPrimitive();

		a->Inverse();
		//dec(*a);
		printf("\nm=%i  inverse() = %050s",i, a->Print(FMT_BIN, buf1));

		power2(*b,b->BitLength);
	//	b.Square();
		dec(*b);
		printf("\nm=%i  ^2^m-1    = %050s",i, b->Print(FMT_BIN, buf1));

		printf("\n");
		delete b;
		delete a;
	}

	{
		i = 167;
		a = new GF2m(i);
		b = new GF2m(i);

		a->SetOne();
		b->SetPrimitive();

		a->Inverse();
		//dec(*a);
		printf("\nm=%i  inverse() = %050s",i, a->Print(FMT_BIN, buf1));

		power2(*b,b->BitLength);
	//	b.Square();
		dec(*b);
		printf("\nm=%i  ^2^m-1    = %050s",i, b->Print(FMT_BIN, buf1));

		printf("\n");
		delete b;
		delete a;

	}
	
}


int main(int argc, char* argv[])
{
	print_GF2_5();
	check_F();
	f1();
	check_prime_F();
	mul_test();
	test_power();
	test_inverse();
	test_div();
	test_decr();
	test_power2();
	SearchF();

    getch();
	return 0;
}

