// Xlong.cpp: implementation of the XLong class.
//
/*///////////////////////////////////////////////////////////////////\

  Xlong math libraly ver 0.x
  Copyright (c) 2002 Dennis Shilko  (email: sdennis@tut.by)

  DESCRIPTION:
  fast math routines for very long numbers 

  for TODO list, known issues and history see ReadMe.txt

\*/////////////////////////////////////////////////////////////////////

#include "XLongMathLib.h"
namespace XLONG_MATH_LIB {

#include "Xlong.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void XLong::Init()
{
	// alignment must be according to BLOCK_BITLEN 
	if ((bit_length & (BLOCK_BITLEN-1)) != 0) 
		bit_length = (bit_length ^ (bit_length & (BLOCK_BITLEN-1) )) + BLOCK_BITLEN;
	
	// minimal size is 2*BLOCK_BITLEN
	if (bit_length < 2*BLOCK_BITLEN) bit_length = 2*BLOCK_BITLEN;

	// allocate given size  + 1 additional BLOCK_BITLEN
	// for specific of low-level '*' '+'... operations overflow case
	this->n = new uint32[GetInt32Length()+(BLOCK_BITLEN>>5)];

	Clear();
}

XLong::XLong(const XLong &other)
{
    bit_length = other.GetBitLength();
    Init();
	*this = other;
}

XLong::XLong()
{
    bit_length = DEFAULT_BIT_LEN;
    Init();
}

XLong::XLong(const uint32 value,const uint32 bitlen)
{
    bit_length = bitlen;
    Init();
    *this = value;
}


XLong::~XLong()
{
	delete [] n;
}

XLong& XLong::operator =(const uint32 small_number)
{
    Clear();
	n[0] = small_number;
    return *this;
}

XLong& XLong::operator =(const XLong &other)
{
	if (*this == other) return *this; // case A=A
	
    Clear();
    if (GetInt32Length() >= other.GetInt32Length())
    {
		memcpy(n, other.n, other.GetInt32Length() << 2 );
    }
    else 
    {
		if (other.GetHighInt32() > GetInt32Length())
		{
#ifdef STRICT_CHECKS
				ALERT(" a=b when a<b: value truncation in <Xlong::operator = ()>");
#endif
			return *this;  // returning "0" after Clear()
		}

	    memcpy(n, other.n, GetInt32Length() << 2 );
    }
    return *this;
}


XLong XLong::operator +(const XLong &other) const 
{

    int int32_length = GetInt32Length();
    XLong summ(0,GetBitLength());   // possible length mismatch

/* // trying to implement len_mismatch solution
	XLong* pBigger;

	uint32 summInt32Len,copyInt32Len;

	if (other.GetHighInt32() <= GetInt32Length())
		summInt32Len = GetInt32Length();
	else
		summInt32Len = other.GetInt32Length();

	XLong summ(0,summInt32Len);

	if (other.GetInt32Length() <= GetInt32Length())
	{
		copyInt32Len = other.GetInt32Length();
		pBigger = this;
	}
	else
	{
		copyInt32Len = GetInt32Length();
		pBigger = &other;
	}
*/
	if (!_isBitLenMismatch(other))
	{
		summ = *this;
		add(summ, other);
	}

/* // trying to implement len_mismatch solution
	while (copyInt32Len <= summInt32Len)
	{
		summ.n[copyInt32Len] = pBigger->n[copyInt32Len];
		copyInt32Len++;				
	}
*/
    return summ;
}

XLong& XLong::operator +=(const XLong &other)
{

/* // trying to implement len_mismatch solution
#	ifdef STRICT_CHECKS
		if (other.GetHighInt32() > GetInt32Length())
		{
			ALERT("value truncation in <Xlong::operator +=()>");
			return *this;
		}
#	endif
*/
	if (!_isBitLenMismatch(other))
	{
		add(*this, other);
	}
    return *this;
}

XLong& XLong::operator +=(const uint32 small_number)
{ 
	add(*this,small_number);
	return *this;
}

XLong XLong::operator +(const uint32 small_number) const 
{
	XLong t(0,GetBitLength());
	t= small_number;
	return ( (*this) + t);
}

XLong XLong::operator -(const uint32 small_number) const 
{
	XLong t(0,GetBitLength());
	t= small_number;
	return ( (*this) - t);
}

XLong XLong::operator -(const XLong& other) const 
{
    int int32_length = GetInt32Length();
	XLong difference(0,GetBitLength());   // possible length mismatch

	if (!_isBitLenMismatch(other)) 
	{
		difference = *this;
		sub(difference, other);
	}
    return difference;
}

XLong& XLong::operator -=(const XLong& other)
{
	if (!_isBitLenMismatch(other)) 
	{
		sub(*this,other);
	}
	return *this;
}


XLong& XLong::operator -=(const uint32 small_number)
{
	sub(*this, small_number);
    return *this;
}


XLong& XLong::operator ++()
{
	return ((*this) += 1);
}
XLong& XLong::operator --()
{
    return ((*this) -= 1);
}



bool XLong::operator ==(const uint32 small_number) const
{
    //if (cmp(small_number) == 0) return true; else return false;
	return ( cmp(*this, small_number) ? false:true);
}

bool XLong::operator ==(const XLong &other) const
{
    //if (cmp(other) == 0) return true; else return false;
	return ( cmp(*this, other) ? false:true);
}

bool XLong::operator !=(const uint32 small_number) const
{
    //if (cmp(small_number) == 0) return false; else return true;
	return ( cmp(*this, small_number) ? true:false);
}

bool XLong::operator !=(const XLong &other) const
{
    //if (cmp(other) == 0) return false; else return true;
	return ( cmp(*this, other) ? true:false);
}

bool XLong::operator >(const uint32 small_number) const
{
	if (cmp(*this, small_number) == 1) return true; else return false;
}

bool XLong::operator >(const XLong &other) const
{
	if (cmp(*this, other) == 1) return true; else return false;
}

bool XLong::operator <(const uint32 small_number) const
{
	if (cmp(*this, small_number) == 2) return true; else return false;
}

bool XLong::operator <(const XLong &other) const
{
	if (cmp(*this, other) == 2) return true; else return false;
}

bool XLong::operator >=(const uint32 small_number) const
{
	if (!(*this < small_number)) return true; else return false;
}

bool XLong::operator >=(const XLong &other) const
{
	if (!(*this < other)) return true; else return false;
}

bool XLong::operator <=(const uint32 small_number) const
{
	if (!(*this > small_number)) return true; else return false;
}

bool XLong::operator <=(const XLong &other) const
{
	if (!(*this > other)) return true; else return false;
}


XLong XLong::operator *(const XLong &other) const
{
//	return(mul(*this,other));
    XLong product(0, GetBitLength());
	if (!_isBitLenMismatch(other)) 
	{
		product = *this;
		mul(product, other);
	}	
	return product; //bitlen not eq

}

XLong XLong::operator *(const uint32 small_number) const
{
    XLong t(0,GetBitLength());
    t = small_number;
	if (small_number == 0) return t;
    return ( (*this)*t);
}


XLong XLong::operator /(const XLong &other) const
{
    XLong quotient(0,GetBitLength());
    XLong remainder(0,GetBitLength());

    div(*this, other, quotient, remainder);   
    return quotient;
}

XLong XLong::operator %(const XLong &other) const
{
	XLong t(*this);
	mod(t, other);
	return t;
}

//-----------------------------------------------------------------------------------
bool XLong::WriteTXTFile(const char *fname) const
{
    BYTE char_bits[32];
    FILE *pfile;

    memset(char_bits,0,sizeof(char_bits));

    if( (pfile = fopen( fname, "wb" )) != NULL )
    {
		for (int i=GetInt32Length()-1; i>=0; i--)
		{
			for (int j = 31;j>=0;j--)
			{
				//if (char_bits[31-j] == 1) pn1[2-i] |= (1 << j);
				if (n[i] & ((uint32 )(1 << j)) )
				   (char_bits[31-j] = '1'); else (char_bits[31-j] = '0');
			}
			fwrite(char_bits, 1, 32, pfile );
		}
		fclose( pfile);
		return true;
    }
    else
    {
		ALERT("error openning file in XLong::WriteTXTFile()");
		ALERT(fname);
		return false;
    }

}

bool XLong::ReadTXTFile(const char *fname)
{
    BYTE char_bits[32];
    FILE *pfile;
    Clear();

    if( (pfile = fopen( fname, "rb" )) != NULL )
    {
        for (int i=GetInt32Length()-1; i >= 0; i--)
        {
			memset(char_bits,0,sizeof(char_bits));
            fread(char_bits, 1, 32, pfile);
            for (int j = 31;j>=0;j--)
            {
                //if (char_bits[31-j] == 1) pn1[2-i] |= (1 << j);
                if (char_bits[31-j] == '1')  
                        n[i] |= (uint32 )(1 << j);
            }
        }
        fclose( pfile );
		return true;
    }
    else
	{
		ALERT("error openning file in XLong::ReadTXTFile()");
		ALERT(fname);
		return false;
	}
}

bool XLong::ReadBINFile(const char* fname)
{
    FILE *pfile;

	Clear();

    if( (pfile = fopen( fname, "rb" )) != NULL )
    {
	fread((uint32*)n, sizeof(uint32), GetInt32Length(), pfile);
	fclose(pfile);
	return true;
    }
    else
	{
		ALERT("error openning file in XLong::ReadBINFile()");
		ALERT(fname);
		return false;
    }

}

bool XLong::WriteBINFile(const char* fname) const
{
    FILE *pfile;

    if( (pfile = fopen( fname, "wb" )) != NULL )
    {
        fwrite((uint32*)n, sizeof(uint32), GetInt32Length(), pfile);
        fclose( pfile);
        return true;
	}
    else
    {
		ALERT("error openning file in XLong::WriteBINFile()");
		ALERT(fname);
		return false;
	}             
}

bool XLong::bt(uint32 bit) const
{
	//2OPTIMIZE: make in assembler
	//return (  (n[bit >> 5] & (1 << (bit % 32)))?1:0 );
	if (_checkBounds(bit))
		return (  (n[bit >> 5] & (1 << (bit & 31)))?1:0 );
	else
		return false;
}

void XLong::bs(uint32 bit)
{
	if (_checkBounds(bit))
		n[bit >> 5] |= (1 << (bit & 31)) ;
}

void XLong::bc(uint32 bit) 
{
	if (_checkBounds(bit))
		n[bit >> 5] &= ((1 << (bit & 31)) ^ 0xffffffff);
}

bool XLong::_checkBounds(uint32 bit) const 
{
	if (bit < GetBitLength()) return true;else return false; 
}

void XLong::Clear()
{
    memset(n,0,GetInt32Length() << 2);
}

uint32 XLong::GetBitLength() const
{
    return bit_length;
}

uint32 XLong::GetInt32Length() const
{
	return (GetBitLength() >> 5);
}

uint32 XLong::GetHighInt32() const
{
	int32 HighInt32;
	
	for (HighInt32=GetInt32Length()-1;HighInt32>=0;HighInt32--)
		if (n[HighInt32] != 0) return HighInt32;
	return 0;
}

uint32* XLong::GetBuffer() const
{
    return n;
}

XLong XLong::operator <<(uint32 small_number)
{
	XLong result(*this);
	shl(result,small_number);
	return result;
}

XLong XLong::operator >>(uint32 small_number)
{
	XLong result(*this);
	shr(result, small_number);
	return result;
}

uint32 XLong::Log2() const
{
	/* // slow but simple
	int i=length-1;
	while (1)
	{
		if (bt(i)) return i+1;
		i--;
		if (i < 0) return 0; // maybe need exception handling.. 
	}*/
	
	// optimized
	int32 i = GetHighInt32();
	if ((i==0) && (n[i] == 0)) return 0; //Log2(0) doesn't exist

	uint32 j = 1 << 31;
	while (!(n[i]&j)) j = j >> 1;
	i = i << 5;
	while (j > 0)
	{
		j = j >> 1;
		i++;
	}
	return i-1;
}


XLong XLong::operator & (const XLong &other) const
{
	XLong result(*this);
	if (_isBitLenMismatch(other)) return (result=0);

	uint32 int32_length = GetInt32Length();
	uint32 i = 0;

	while (i < int32_length) 
	{
		//result.GetBuffer()[i] = n[i] &= other.GetBuffer()[i];
		result.n[i] &= other.n[i];
		i++;
	}
	return result;

}
XLong XLong::operator | (const XLong &other) const
{
	XLong result(*this);
	if (_isBitLenMismatch(other)) return (result=0);

	uint32 int32_length = GetInt32Length();
	uint32 i = 0;

	while (i < int32_length) 
	{
		result.n[i] |= other.n[i];
		i++;
	
	}
	return result;
}
XLong XLong::operator ^ (const XLong &other) const
{
	XLong result(*this);
	if (_isBitLenMismatch(other)) return (result=0);

	uint32 int32_length = GetInt32Length();
	uint32 i = 0;

	while (i < int32_length) 
	{
		result.n[i] ^= other.n[i];
		i++;
	
	}
	return result;
}
       

// just a quick buggy draft version 2
char* XLong::Print(const formatType_t fmt, uint32 textBufSize, char* textBuffer) const
{
    char str1[40];
	int32 i1=0;

    int32 i = GetInt32Length() - 1;
    if (textBufSize > 0)
	{
		if (fmt == FMT_DEC)
		{
			if ((uint32)i*20 > textBufSize)   // approx ??
				i = textBufSize / 20;
		}
		else if (fmt == FMT_HEX)
		{
			if ((uint32)i*4 > textBufSize)  
				i = textBufSize / 4;
		}
		else if (fmt == FMT_BIN)
		{
			if ((uint32)i*32 > textBufSize) 
				i = textBufSize / 32;
		}
		else 
		{
		    sprintf(textBuffer,"ERROR!: bad formatType_t");
			return textBuffer;
		}
	}
    sprintf(textBuffer,"");

    while(i>=0)
    {
		sprintf(str1,"");
		if (fmt == FMT_DEC)
		{
			if (n[i] != 0)
			{

				if (strlen(textBuffer) > 0)
					strcat(textBuffer, " + ");
				if (i>0) 
					sprintf(str1,"%u*(2^%u)", n[i],32*i);
				else 
					sprintf(str1,"%u", n[i]);
			}

		}
		else if (fmt == FMT_HEX)
		{
			if (n[i] != 0)
			{
				if (strlen(textBuffer)>0)
					sprintf(str1,"%.8x", n[i]);
				else
					sprintf(str1,"%x", n[i]);
			}
		}
		else if (fmt == FMT_BIN)
		{
            if ((strlen(textBuffer)>0) || (n[i] != 0))
            {
                if (strlen(textBuffer)>0)
                {
                    for (i1 = 0;i1<32;i1++)
                    {
                        if (this->bt((i<<5)+31-i1)) 
                            str1[i1] = '1';
                        else 
                            str1[i1] = '0';
                
                    }
                    str1[32] = 0;
                }
                else
                {
                    int i2=0;
                    str1[0] = 0;
                    for (i1 = 0;i1<32;i1++)
                    {
                        if (this->bt((i<<5)+31-i1)) 
                        {
                            str1[i1+i2] = '1';
                        }
                        else 
                        {
                            if (str1[0] == 0)
                                i2--;
                            else
                                str1[i1+i2] = '0';
                        }
                
                    }
                    str1[i1+i2] = 0;
                }
            }
		}

        if ((strlen(textBuffer)+strlen(str1)) < (textBufSize-1))
            strcat(textBuffer, str1);
        else 
        {
            textBuffer[strlen(textBuffer)-2] = '.';
            textBuffer[strlen(textBuffer)-1] = '.';
            break;
        }
        i--;
    }
    if (strlen(textBuffer) == 0)  sprintf(textBuffer,"0");
	return textBuffer;
}

char* XLong::Print(formatType_t fmt, char* textBuffer) const
{
    return (Print(fmt, 0, textBuffer));
}

char* XLong::Print(char* textBuffer) const 
{
    return (Print(FMT_DEC, textBuffer));
}


/*
uint32 XLong::GetLog2()
{
	return Log2();
}
uint32 XLong::GetOrder()
{
	return Log2()+1;
}

uint32 XLong::GetLength()
{
	return GetBitLength();

}*/



bool XLong::_isBitLenMismatch(const XLong& other) const
{
	if (this->GetBitLength() == other.GetBitLength()) return false;
#ifdef STRICT_CHECKS
	ALERT("trying to perform math operations between XLong objects of different bit length");
#endif
	return true;
}




} // namespace XLONG_MATH_LIB 
