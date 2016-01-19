//////////////////////////////////////////////////////////////////////////////
   < XLong Integer Math Library >
   Copyright (c) 2002-2003 Dennis Shilko
   email: **************

   fast math routines for very long values
   size is up to 2^(2^32) :-) 
   made and optimized for ********* project at GRSU  

//////////////////////////////////////////////////////////////////////////////
  todo list: 
  ---------

  -CInflong
  -portability to linux, unix, other C++ compilers 
                

  known isues:

  /////////////////////////////////////////////////////////
  -exception handling ? Nice stuff, but do I need it ???


  /////////////////////////////////////////////////////////
   overflow check is not used because of class XLong models 
   long version of CPU register and it behave is the same
   it is residue ring modulo 2^object_given_bit_length 
   (because of speed optimizations object_given_bit_length
   rounds up to be ((object_given_bit_length mod 32) = 0)) 
   like Intel x86 CPU 32bit registers are residue rings
   modulo 2^32. Hence XLong  can be interpret as unsigned
   or signed (highest bit will mean sign). 
   For more 'high level' representation can be created
   classes Inflong or XInteger derived from XLong or use it as 
   private member.


  /////////////////////////////////////////////////////////
  does XLong::operator &(XLong& other ) 
    '&X' can be taken as an ADDR(X) 
     Stroustrup says yes, but I didn't noticed yet that bug

  {
        XLong x,y;
        y = 2+x;     // doesn't work (may be (XLong)2+x) or implement
                                //  friend XLong operator+(uint32, XLong)        
  }
 
 ///////////////////////////////////////////////////////////
   
   currently due to achieve maximal speed
   all math calculation MUST be done 
   between numbers with EQUAL BIT LENGTH i.e.
         
         Xlong A(0,512),B(0,1024);
         ...
         A+B // ERROR! cause of (A.GetBitLength() != B.GetBitLength)
        
   exception is <XLong operator =() >
   and comparison operators ( ==, !=, <, >, <=, >=, cmp() ). 
   It can be used to  exchange values between objects of
   different bit length,
   but of course assign of bigger value to an object
   with smaller bit length will cause data loss and error i.e.
   
   Xlong A(0,512), B(0,1024), C(0,1024), D(0,2048); 
 
        ... 
        D = B*C; // OK 
        C = A;   // OK
        A = B+C; // may be OK if value of B and C are small
                        // will cause an error if value (B+C) is 
                        // longer than A can be assigned to.
        if ( A > D ) {...}  // OK

  ////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////

  History:

 --- 0.x ----------------------------------------------------------

11.1.2003:
 -the hell with this history because I've lost count of changes 
  and improvements so it's useless now.


11.2002:
 -removed m$-specific precompiled headers
 -DWORD replaced with uint32
 -added int32 type 
 -fixed: new Log2() = old Log2()-1; coz 2^0=1


22.10.2002:
 -last version before big changes due to decision that this project
  will be my diplom project and so there are much to do with XLong class
  After several month of usage of it in **************ct there is a big
  todo-list as well as some new conceptual ideas like CInflong and known
  issues.
  Current status is 99% math bug free routines. 

 
27.5.2002:
 -no more stupid 0.* versions (I'm tired of this) until final release
  (I hope it will be finnished some day %))
 -fixed bug in operator *(XLong &other) caused memory bounds violation
 -other small fixes
 -added operator *(DWORD small_number)
 -need to implement exception handling !!!
 -added Format( ) member like in MFC's CString but of course simplified
  !!! need to fix buffer allocation problem which occur 
  in calls like printf("%s %s", X.Format(FMT_DEC), X.Format(FMT_HEX))
 -cleaned mess in this readme.txt and removed notes.txt (appended to readme.txt)

22.8.2002:

-minor definition changes in constructor and some new one
 in order to work with ( (XLong) _DWORD-VALUE_ ) 
 I'm not sure if it right because of leak of imformation about type
 conversion in classes (or coz of I'm too lazy ;)
-small changes, additions and fixes I can't remember and to lazy to 
 log here ;)



 --- 0.95 15.4.2002 --------------------------------------------------------------
 -fixed bug in cmp(DWORD small_number)
 -added XLong& operator +=(DWORD small_number);
 -fixed bug with buffer size when ((bitlen % 32) != 0)
 -other small fixes
 -fixed bugs in "/" and "%" operators calls to div

    finishing poor beta code;
    found&killed many-many stupid bugs;

 --- 0.92 13.4.2002 --------------------------------------------------------------
 
 -Moved from 0.8* to 0.9* by defining new class XLong 
  now using c++ class architecture; big piece of work
 -tests are still in progress. Fixed many bugs, still looking for new
 -reliability of proper work of routines ~70%
  reliability list min-! max-!!!!
  {
   =       !!
   +=      !!
   -       !!
   -=      !!
   <<      !!!
   >>      !!!
   ==      !!
   !=      !!
   >       !!
   <       !!
   >=      !!
   <=      !!
   bt() !!!
   bc() !!!
   bs() !!!
   *       !!
   /       !!
  }
 - ULONG changed to DWORD
 - char in some places changed to BYTE 


 --- 0.8999 13.4.2002 ---------------------------------------------------
 
 -this is last version without use of cpp classes 
  I should use classes from the begining, but I'm too lazy
  also I didn't think it will be serious project
 -making last small fixes before porting to class


 --- 0.0....1 ~26.3.2002 -------------------------------------------------
 -Official (or maybe non official ;) Xlong-project start !!! 



/////////////////////////////////////////////////////////////////////////
/////////////  NOTES ////////////////////////////////////////////////////
-------------------------------------------------------------------
tests for < > == !=

        a = 447; // vary 
        b = 446; // combinations

        a << 69;
        b << 69;
        
        if (a == b) printf("==\n");
        if (a != b) printf("!=\n");
        if (a < b) printf("<\n");
        if (a > b) printf(">\n");
        if (a <= b) printf("<=\n");
        if (a >= b) printf(">=\n");
-------------------------------------------------------------------
test for bt()

        b.ReadTXTFile("d:\\a0.txt");

        for (int i=0;i<70;i++)
          printf ("%u", b.bt(i));
        printf("\n");



