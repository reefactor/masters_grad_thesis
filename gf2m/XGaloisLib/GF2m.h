// GF2m.h: interface for the GF2m class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_GF2m_H_) && defined(_XGALOISLIB_H_)
#define _GF2m_H_

namespace XGALOIS_MATH_LIB
{

typedef struct {
    uint32 degree;
    uint32 exp;
    uint32 Coeffs[1000];
}   F_entry;


enum formatType_t {	FMT_DEC, FMT_HEX, FMT_BIN};

F_entry* GetFTable();
void SetFCoeff(uint32 m, uint32* Coeffs);
F_entry* GetF(uint32 m, uint32 index);

class GF2m
{
public:

    // constructors
	GF2m(const uint32 bitlen);
	GF2m(const GF2m &other);
	//GF2m();


	// bitwise operations
    void	bc(const uint32 bit);                  
    bool	bt(const uint32 bit) const;
    void	bs(const uint32 bit);

    // service and I/O routines
	char*	Print(char* textBuffer) const;
    char*	Print(const formatType_t fmt, char* textBuffer) const;
    char*	Print(const formatType_t fmt,const uint32 textBufSize, char* textBuffer) const;
	bool	ReadBINFile(const char* fname);
    bool	WriteBINFile(const char* fname) const;
    bool	ReadTXTFile(const char *fname);
    bool	WriteTXTFile(const char* fname) const;
    
    void	Clear();
    uint32  GetHighInt32() const;
    uint32  GetHighBit() const;
	uint32  GetInt32Length() const; 

    // math operators
    GF2m&	operator =(const uint32 small_number);
    GF2m&	operator =(const GF2m &other);
    
	GF2m	operator +(const GF2m &other) const;
    GF2m	operator +(const uint32 small_number) const;
	GF2m&	operator +=(const GF2m &other);
    GF2m&	operator +=(const uint32 small_number);
	GF2m	operator *(const GF2m &other) const;      
	GF2m&	operator *=(const GF2m &other);      
    GF2m	operator *(const uint32 small_number) const;
    GF2m	operator /(const GF2m &other) const;
    GF2m&	operator /=(const GF2m &other);

	// logical operators
    bool	operator ==(const GF2m &other) const;
    bool	operator !=(const GF2m &other) const;
    bool    operator ==(const uint32 small_number) const;
    bool    operator !=(const uint32 small_number) const;

    GF2m&	operator ++();
    GF2m&	operator --();

    bool isZero() const;
    bool isOne() const;
	bool isPrimitive() const;

	void SetZero();
	void SetPrimitive();
	void SetOne();

	void Square();
	void Inverse();

 
	// destructor
    virtual ~GF2m();

	uint32*	n;
	uint32*	F;
	uint32	BitLength;

protected:

	void	Init();

private:

    bool    _isBitLenMismatch(const GF2m& other) const;
    bool    _checkBounds(const uint32 bit) const;

};

} // namespace XGALOIS_MATH_LIB

#endif // _GF2m_H_