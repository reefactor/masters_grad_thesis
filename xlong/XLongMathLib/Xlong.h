// Xlong.h: interface for the XLong class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_XLong_H_) && defined(_XLONGMATHLIB_H_)
#define _XLong_H_


namespace XLONG_MATH_LIB
{

enum formatType_t {	FMT_DEC, FMT_HEX, FMT_BIN};

//template <int size = 512>
class XLong
{
public:

    // constructors
	XLong(const uint32 value,const uint32 bitlen = DEFAULT_BIT_LEN);
	XLong(const XLong &other);
	XLong();

	// math functions
    uint32	Log2() const;

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
    uint32*	GetBuffer() const;
    
	uint32	GetBitLength() const; 
	uint32	GetHighInt32() const;
	uint32	GetInt32Length() const; 

    void	Clear();

    // math operators
    XLong&	operator =(const uint32 small_number);
    XLong&	operator =(const XLong &other);
    XLong	operator +(const XLong &other) const;
    XLong	operator +(const uint32 small_number) const;
    XLong&	operator +=(const XLong &other);
    XLong&	operator +=(const uint32 small_number);
    XLong	operator -(const XLong &other) const;
    XLong	operator -(const uint32 small_number) const;
    XLong&	operator -=(const XLong &other);
    XLong&	operator -=(const uint32 small_number);
    XLong&	operator ++();
    XLong&	operator --();
	XLong	operator *(const XLong &other) const;      
    XLong	operator *(const uint32 small_number) const;
    XLong	operator /(const XLong &other) const;
    

	// logical operators
    bool	operator ==(const uint32 small_number) const;
    bool	operator ==(const XLong &other) const;
    bool	operator !=(const uint32 small_number) const;
    bool	operator !=(const XLong &other) const;
    bool	operator >(const uint32 small_number) const;
    bool	operator >(const XLong &other) const;
    bool	operator <(const uint32 small_number) const;
    bool	operator <(const XLong &other) const;
    bool	operator >=(const uint32 small_number) const;
    bool	operator >=(const XLong &other) const;
    bool	operator <=(const uint32 small_number) const;
    bool	operator <=(const XLong &other) const;


    // bitwise operators
	XLong	operator %(const XLong &other) const;
    XLong	operator &(const XLong& other) const;
	XLong	operator |(const XLong& other) const;
	XLong	operator ^(const XLong& other) const;
    XLong	operator <<(const uint32 small_number); 
    XLong	operator >>(const uint32 small_number);


	// destructor
    virtual ~XLong();

protected:

	uint32*	n;
	uint32	bit_length;
	void	Init();

private:
	bool	_isBitLenMismatch(const XLong& other) const;
	bool	_checkBounds(const uint32 bit) const;
};

} // namespace XLONG_MATH_LIB

#endif // _XLong_H_