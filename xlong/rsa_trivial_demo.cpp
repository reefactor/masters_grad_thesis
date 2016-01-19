#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "XLongMathLib\XLongMathLib.h"

using namespace XLONG_MATH_LIB;

char buf1[1000],m[100],c[100];
char s1[100],s2[100];

void print(char* s)
{
        char s1[300];
        CharToOem( s,s1);
        printf(s1);
}

int main(int argc, char* argv[])
{
    XLong e;
    XLong N;
    XLong d;
    XLong p,q;
    XLong phi;
    XLong M,M1,M2;
    XLong t;
    uint32 small_p,small_q,small_e,small_m;
    print(" *** Демонстрация формирования криптосистемы RSA ***\n");
    print(" Введите простые числа p и q: ");
    printf("\n p="); scanf("%u",&small_p); p = small_p;
    printf(" q="); scanf("%u",&small_q); q = small_q;
    N = p*q; // модуль
    print("\n введите шифруемое сообщение (число не превышающее модуля N=p*q) M: ");
    scanf("%u",&small_m); M = small_m;

    if (M >= N)
    {
      printf("\n error: M >= N\n");
      exit(0);
    }

    phi = (p-1)*(q-1);

    e = p*(1 + rand()); // 7; // выбираем начальное значение открытого ключа 
    //printf("\n выберите открытый ключ - простое число  e="); scanf("%u",&small_e); e = small_e;

    while (!evclm(e,phi,t)) ++e; 
    d = t/e;

    print("\n  Параметры криптосистемы:");
    printf("\n   p=%s", p.Print(buf1)); 
    printf("\n   q=%s", q.Print(buf1)); 
    printf("\n   N=p*q=%s", N.Print(buf1)); 
    printf("   ( Log2(N)=%u :: modulo=%u bit )\n", (p*q).Log2(), (p*q).Log2() +1 ); 
    print("   Открытый ключ:");printf(" e=%s", e.Print(buf1)); 
    print("   Закрытый ключ:");printf(" d=%s", d.Print(buf1)); 
    print("\n   Сообщение: ");printf(" M=%s", M.Print(buf1)); 
    M1 = modexp(M,e,N);
    print("\n\n Зашифрованное при помощи открытого ключа e сообщение С: ");
    printf("\n    C = M^e mod N = %s\n", M1.Print(buf1)); 
    M2 = modexp(M1,d,N);
    print("\n\n Расшифрованное при помощи закрытого ключа d сообщение T: ");
    printf("\n    T = C^d mod N = %s\n", M2.Print(buf1)); 
    print("\n\n Расшифрованное сообщение T равно исходному M");
    getch();
    return 0;
}

