#include <conio.h>

#include "XGaloisLib\XGaloisLib.h"
using namespace XGALOIS_MATH_LIB;

static char buf1[1000];
static char format_string[200];

void print(char* s)
{
        char s1[300];
        CharToOem( s,s1);
        printf(s1);
}

int main(int argc, char* argv[])
{
	long double GFLog = 0;
	int m = 0; 
	unsigned int j = 0;

	print("\nВведите степень расширения m поля GF(2^m):  ");
    scanf("%u",&m);

	GF2m Element(m);


	print("\nИспользуемый неприводимый полином: ");
	printf("\nF(x) = 1");
	j = 0;
	while (GetF(m,0)->F_coeffs[j] != 0) 
	{
		printf(" + x^%d", GetF(m,0)->F_coeffs[j]);
		j++;
	}
	printf(" + x^%d", m);


	print("\nЭлементы поля");
    printf(" GF(2^%d):", Element.BitLength);
	
	Element.SetZero();
	printf("\nLog= %6.0f: ", GFLog);
	for (j=0; j < (Element.BitLength - Element.GetHighBit()-1); j++) printf("0");

	Element.SetOne();
    do
    {
		printf("\nLog= %6.0f: ", GFLog);
		for (j=0; j < (Element.BitLength - Element.GetHighBit()-1); j++) printf("0");
		printf("%s", Element.Print(FMT_BIN, buf1));
        Element++;
        GFLog++;
	} while (!Element.isOne());

	getch();
	return 0;
}

