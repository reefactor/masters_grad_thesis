// GF2m.cpp: implementation of the GF2m class.
//
/*///////////////////////////////////////////////////////////////////\

  GF2m math libraly ver 0.x
  Copyright (c) 2004 Dennis Shilko

\*/////////////////////////////////////////////////////////////////////

#include "XGaloisLib.h"
namespace XGALOIS_MATH_LIB {

#include "GF2m.h"


static F_entry F_Table[] = {
	{ 1, 1, {1}  },				// F(x) = 1 + x 
	{ 2, 2, {1}  },				// F(x) = 1 + x + x^2
	{ 3, 3, {1}  },				// F(x) = 1 + x + x^3
	{ 4, 4, {1}  },				// F(x) = 1 + x + x^4
	{ 5, 5, {2}  },				// F(x) = 1 + x^2 + x^5
	{ 6, 6, {1}  },				// F(x) = 1 + x + x^6
	{ 7, 7, {1}  },				// F(x) = 1 + x + x^7
	{ 8, 8, {2,3,4}  },			// F(x) = 1 + x^2 + x^3 + x^4 + x^8
	{ 9, 9, {4}  },				// F(x) = 1 + x^4 + x^9
	{ 10, 10, {3}  },			// F(x) = 1 + x^3 + x^10
	{ 11, 11, {2}  },				
	{ 12, 12, {1,4,6}  },				
	{ 13, 13, {1,3,4}  },				
	{ 14, 14, {1,3,5}  },				
	{ 15, 15, {1}  },				
	{ 16, 16, {2,3,5}  },				
	{ 17, 17, {3}  },				
	{ 18, 18, {7}  },				
	{ 19, 19, {1,2,5}  },				
	{ 20, 20, {3}  },				
	{ 21, 21, {2}  },				
	{ 22, 22, {1}  },				
	{ 23, 23, {5}  },				
	{ 24, 24, {1,2,7}  },				
	{ 25, 25, {3}  },				
	{ 26, 26, {1,2,6}  },				
	{ 27, 27, {1,2,5}  },				
	{ 28, 28, {3}  },				
	{ 29, 29, {2}  },				
	{ 30, 30, {1,4,6}  },				
	{ 31, 31, {3}  },				
	{ 32, 32, {1,2,22}  },			// F(x) = 1 + x + x^2 + x^22 + x^32
	{ 33, 33, {13}  },				// F(x) = 1 + x^13 + x^33
	{ 34, 34, {1,2,27}  },				
	{ 35, 35, {2}  },				
	{ 36, 36, {11}  },				
	{ 37, 37, {1,2,3,4,5}  },				
	{ 38, 38, {1,5,6}  },				
	{ 39, 39, {4}  },				
	{ 40, 40, {3,4,5}  },				
	{ 41, 41, {3}  },				
	{ 42, 42, {1,2,3,4,5}  },				
	{ 43, 43, {3,4,6}  },				
	{ 44, 44, {2,5,6,}  },				
	{ 45, 45, {1,3,4}  },				
	{ 46, 46, {1,2,3,5,8}  },				
	{ 47, 47, {5}  },				
	{ 48, 48, {1,2,4,5,7}  },				
	{ 49, 49, {4,5,6}  },				
	{ 50, 50, {2,3,4}  },
	{ 51, 51, {1,3,6}  },
	{ 52, 52, {3}  },
	{ 53, 53, {1,2,6}  },
	{ 54, 54, {2,3,4,5,6}  },
	{ 55, 55, {1,2,6}  },
	{ 56, 56, {2,4,7}  },
	{ 57, 57, {2,3,5}  },
	{ 58, 58, {1,5,6}  },
	{ 59, 59, {1,3,4,5,6}  },
	{ 60, 60, {1}  },
	{ 61, 61, {1,2,5}  },
	{ 62, 62, {3,5,6}  },
	{ 63, 63, {1}  },
	{ 64, 64, {1,3,4}  },
	{ 65, 65, {1,3,4}  },
	{ 66, 66, {2,3,5,6,8}  },
	{ 67, 67, {1,2,5}  },
	{ 68, 68, {1,5,7}  },
	{ 69, 69, {2,5,6}  },
	{ 70, 70, {1,3,5}  },
	{ 71, 71, {1,2,3}  },
	{ 72, 72, {1,2,3,4,6}  },
	{ 73, 73, {2,3,4}  },
	{ 74, 74, {3,4,7}  },
	{ 75, 75, {1,3,6}  },
	{ 76, 76, {2,4,5}  },
	{ 77, 77, {2,5,6}  },
	{ 78, 78, {1,2,7}  },
	{ 79, 79, {2,3,4}  },
	{ 80, 80, {1,2,3,5,7}  },
	{ 81, 81, {4}  },
	{ 82, 82, {1,4,6,7,8}  },
	{ 83, 83, {2,4,7}  },
	{ 84, 84, {1,3,5,7,8}  },
	{ 85, 85, {1,2,8}  },
	{ 86, 86, {2,5,6}  },
	{ 87, 87, {1,5,7}  },
	{ 88, 88, {1,3,4,5,8}  },
	{ 89, 89, {3,5,6}  },
	{ 90, 90, {2,3,5}  },
	{ 91, 91, {2,3,5,6,7}  },
	{ 92, 92, {2,5,6}  },
	{ 93, 93, {2}  },
	{ 94, 94, {1,5,6}  },
	{ 95, 95, {1,2,4,5,6}  },
	{ 96, 96, {2,3,4,6,7}  },
	{ 97, 97, {6}  },
	{ 98, 98, {1,2,3,4,7}  },
	{ 99, 99, {4,5,7}  },
	{ 100, 100, {2,7,8}  },
	{ 107, 107, {1,2,3,5,7}  },
	{ 127, 127, {1}  },					// F(x) = 1 + x + x^127
	{ 167, 167, {6,167}  },				// F(x) = 1 + x^6 + x^167
};


F_entry* GetFTable() 
{
	return F_Table;
}

F_entry* GetF(uint32 m, uint32 index) 
{

	for (int i = 0; i < (sizeof(F_Table)/sizeof(F_entry)); i++)
	{
		if (F_Table[i].degree == m) 
		{
			if (index == 0)	return &F_Table[i];
			index--;
		}
	}

	return NULL;
}


void SetFCoeff(uint32 m, uint32* Coeffs, uint32 index)
{
	int j = 0;
	int i = 0;
	uint32* pTableCoeffs = NULL;

	for (i = 0; i < (sizeof(F_Table)/sizeof(F_entry)); i++)
	{
		if (F_Table[i].degree == m) 
		{
			if (index == 0) 
			{
				pTableCoeffs = F_Table[i].Coeffs;
				break;
			}
			index--;
		}
	}
	
	if (pTableCoeffs == NULL) return;

	i = 0;
	if ((Coeffs[i] == 0) && (Coeffs[i+1] != 0))
	{
		i = 1;
	}

	while (!Coeffs[j] == 0) 
	{
		if (Coeffs[j] >= m)
		{
			pTableCoeffs[j] = 0;
			break;
		}
		pTableCoeffs[j] = Coeffs[j];
		j++;
	}
	pTableCoeffs[j] = 0; // mark end of list of coeffs
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void GF2m::Init()
{
	this->n = new uint32[GetInt32Length()]; 
	int i = 0;
	uint32* F_coeffs = NULL;
	for (i = 0; i < (sizeof(F_Table)/sizeof(F_entry)); i++)
	{
		if ((F_Table[i].degree == BitLength) && (F_Table[i].exp == BitLength))
		{
			F_coeffs = F_Table[i].Coeffs;
			break;
		}
	}
	//
	if (F_coeffs == NULL) CRASH("this bit length is not supported (F not found)");

	this->F = new uint32[GetInt32Length()];
    memset(F,0,GetInt32Length() << 2);
	i = 0;
	while (F_coeffs[i] != 0) 
	{
		F[F_coeffs[i] >> 5] |= (1 << (F_coeffs[i] & 31)) ;
		i++;
	}
	F[0] |= 1;	// F(x) = 1+ ... ; 
				//lowest bit in inc; not affects in dec because of  (F_Coeffs[i] >> 1)
	Clear();
}

GF2m::GF2m(const GF2m &other)
{
    BitLength = other.BitLength;
    Init();
	*this = other;
}

GF2m::GF2m(const uint32 bitlen)
{
    BitLength = bitlen;
    Init();
}

GF2m::~GF2m()
{
	delete [] n;
	delete [] F;
}

GF2m& GF2m::operator =(const uint32 small_number)
{
    Clear();
	n[0] = small_number;
    return *this;
}

GF2m& GF2m::operator =(const GF2m &other)
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
			ALERT(" a=b when a<b: value truncation in <GF2m::operator = ()>");
#endif
			return *this;  // returning "0" after Clear()
		}

	    memcpy(n, other.n, GetInt32Length() << 2 );
    }
    return *this;
}

GF2m GF2m::operator +(const uint32 small_number) const
{
    GF2m summ(*this);   
    GF2m t(*this);   
	t = small_number;
	add(summ,t);
    return summ;
}


GF2m GF2m::operator +(const GF2m &other) const
{
    GF2m summ(*this);   

	add(summ,other);
    return summ;
}

GF2m& GF2m::operator +=(const GF2m &other)
{
	add(*this, other);
    return *this;
}

GF2m& GF2m::operator +=(const uint32 small_number)
{
    GF2m t(*this);   
	t = small_number;
	add(*this, t);
    return *this;
}

GF2m GF2m::operator *(const GF2m &other) const 
{
    GF2m product(*this);
    mul(product, other);
    return product; 
}

GF2m& GF2m::operator *=(const GF2m &other)
{
	mul(*this, other);
	return *this;
}


GF2m GF2m::operator /(const GF2m &other) const 
{
    GF2m quot(*this);
	GF2m t(other);

	t.Inverse();
	mul(quot,t);
	return quot;
}

GF2m& GF2m::operator /=(const GF2m &other) 
{
	GF2m t(other);

	t.Inverse();
	mul(*this, t);
	return *this;
}


bool GF2m::operator ==(const uint32 small_number) const
{
	return ( cmp(*this, small_number) ? false:true);
}

bool GF2m::operator ==(const GF2m &other) const
{
	return ( cmp(*this, other) ? false:true);
}

bool GF2m::operator !=(const uint32 small_number) const
{
	return ( cmp(*this, small_number) ? true:false);
}

bool GF2m::operator !=(const GF2m &other) const
{
	return ( cmp(*this, other) ? true:false);
}

bool GF2m::isZero() const
{
  return (this == 0);
}

bool GF2m::isOne() const
{

	if (n[0] == 1 ) 
	{
		if (this->GetHighInt32() == 0) return true;
	}

	return false;
}

bool GF2m::isPrimitive() const
{
	if (this->GetHighInt32() == 0)
	{
		if (n[0] == 2 ) 
		{
		  return true;
		}
	}
	return false;
}

GF2m& GF2m::operator ++()
{
	inc(*this);
	return *this;
}

GF2m& GF2m::operator --()
{
	dec(*this);
	return *this;
}

bool GF2m::bt(uint32 bit) const
{
	//2OPTIMIZE: make in assembler
	//return (  (n[bit >> 5] & (1 << (bit % 32)))?1:0 );
	if (_checkBounds(bit))
		return (  (n[bit >> 5] & (1 << (bit & 31)))?1:0 );
	else
		return false;
}

void GF2m::bs(uint32 bit)
{
	if (_checkBounds(bit))
		n[bit >> 5] |= (1 << (bit & 31)) ;
}

void GF2m::bc(uint32 bit) 
{
	if (_checkBounds(bit))
		n[bit >> 5] &= ((1 << (bit & 31)) ^ 0xffffffff);
}


void GF2m::Clear()
{
    memset(n,0,GetInt32Length() << 2);
}

uint32 GF2m::GetInt32Length() const
{
	uint32 i = BitLength;
    //if ((i & (BLOCK_BITLEN-1)) != 0) i = (i ^ (i & (BLOCK_BITLEN-1) )) + BLOCK_BITLEN;
	// i = i >> 5;
	i = BitLength >> 5;
	if ((BitLength & 31) != 0) i++;

	return i;
}

uint32 GF2m::GetHighInt32() const
{
	int32 HighInt32;
	
	for (HighInt32=GetInt32Length()-1;HighInt32>=0;HighInt32--)
		if (n[HighInt32] != 0) return HighInt32;
	return 0;
}

uint32 GF2m::GetHighBit() const
{
	uint32 HighestInt32 = GetHighInt32();
	uint32 HighestBit = HighestInt32 << 5; 
	/*uint32 i = 0xFFFFFFFF;//1 << 31;
	HighestBit += 31;
	while (n[HighestInt32] < i)
	{
		HighestBit--;
		i = i >> 1;
	}*/
	uint32 HighestInt32value = n[HighestInt32];
	while (HighestInt32value != 0) 
	{
		HighestInt32value = HighestInt32value >> 1;
		HighestBit++;
	}

	return HighestBit;
}

void GF2m::SetZero()
{
	Clear();
}

void GF2m::SetPrimitive()
{
	Clear();
	bs(1);
}

void GF2m::SetOne()
{
	Clear();
	bs(0);
}

void GF2m::Square()
{
	mul(*this,*this);
}

void GF2m::Inverse()
{
	GF2m t(*this);
	
	SetOne();
	
	t.Square();
	//t = t*t;
	for (uint32 i = 0; i< BitLength-1 ; i++)
	{
		mul(*this,t);
		//t = t*t; 
		t.Square();
	}
}


//-----------------------------------------------------------------------------------
bool GF2m::WriteTXTFile(const char *fname) const
{
    BYTE char_bits[32];
    uint32 i,j;
    FILE *pfile;

    memset(char_bits,0,sizeof(char_bits));

    if( (pfile = fopen( fname, "wb" )) != NULL )
    {
		for (i=0;i < GetInt32Length();i++)
		{
			for (j = 0;j<32;j++)
			{
				//if (char_bits[31-j] == 1) pn1[2-i] |= (1 << j);
				if (n[i] & ((uint32 )(1 << j)) )
				   (char_bits[j] = 0x31); else (char_bits[j] = 0x30);
			}
			fwrite(char_bits, 1, 32, pfile );
		}
		fclose( pfile);
		return true;
    }
    else
    {
		ALERT("error openning file in GF2m::WriteTXTFile()");
		ALERT(fname);
		return false;
    }

}

bool GF2m::ReadTXTFile(const char *fname)
{
    BYTE char_bits[32];
    uint32 i,j;
    FILE *pfile;
    Clear();

    if( (pfile = fopen( fname, "rb" )) != NULL )
    {
        for (i=0;i<GetInt32Length();i++)
        {
			memset(char_bits,0,sizeof(char_bits));
            fread(char_bits, 1, 32, pfile);
            for (j = 0;j<32;j++)
            {
                //if (char_bits[31-j] == 1) pn1[2-i] |= (1 << j);
                if (char_bits[j] == 0x31)  
                        n[i] |= (uint32 )(1 << j);
            }
        }
        fclose( pfile );
		return true;
    }
    else
	{
		ALERT("error openning file in GF2m::ReadTXTFile()");
		ALERT(fname);
		return false;
	}
}

bool GF2m::ReadBINFile(const char* fname)
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
		ALERT("error openning file in GF2m::ReadBINFile()");
		ALERT(fname);
		return false;
    }

}

bool GF2m::WriteBINFile(const char* fname) const
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
		ALERT("error openning file in GF2m::WriteBINFile()");
		ALERT(fname);
		return false;
	}             
}

 

// just a quick buggy draft version 2
char* GF2m::Print(const formatType_t fmt, uint32 textBufSize, char* textBuffer) const
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

char* GF2m::Print(formatType_t fmt, char* textBuffer) const
{
    return (Print(fmt, 0, textBuffer));
}

char* GF2m::Print(char* textBuffer) const 
{
    return (Print(FMT_DEC, textBuffer));
}

bool GF2m::_isBitLenMismatch(const GF2m& other) const
{
	if (this->BitLength == other.BitLength) return false;
#ifdef STRICT_CHECKS
	ALERT("trying to perform math operations between GF2m objects of different bit length");
#endif
	return true;
}

bool GF2m::_checkBounds(uint32 bit) const 
{
	if (bit < BitLength) return true;else return false; 
}



} // namespace XGALOIS_MATH_LIB 
