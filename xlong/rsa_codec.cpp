
#include "XLongMathLib\XLongMathLib.h"

using namespace XLONG_MATH_LIB;

void rsa_encrypt(char* Src, int srcBitLen, XLong& e_key, XLong& N, char* Dst)
{
	int keyi8Len;
	int i8Len;
	XLong x1(e_key),x2(e_key);
	char* px1;
	char* px2;


	i8Len = srcBitLen / 8;
	if ((srcBitLen % 8) != 0) i8Len++;

	keyi8Len = N.Log2()/8;
	if ((N.Log2()  % 8) != 0) keyi8Len++;

	px1 = (char*) x1.GetBuffer();
	px2 = (char*) x2.GetBuffer();

	int i=0, j=0;

	if (i8Len != 0)	for (i=0;i<i8Len; i++  )
	{
		x1 = 0;
		for (j=0;j<keyi8Len; j++  )
		{
			if ((i+j) > i8Len) break;
			(char) px1[i+j] = (char) Src[i+j];
		}
		x2 = modexp(x1,e_key,N);
		for (j=0;j<keyi8Len; j++  )
		{
			if ((i+j) > i8Len) break;
			(char) Dst[i+j] = (char ) x2.GetBuffer()[i+j];
		}
	
	}
}