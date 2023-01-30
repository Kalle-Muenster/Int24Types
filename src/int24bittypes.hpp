/*///////////////////////////////////////////////////////////*\
||                                                           ||
||     File:      int24bittypes.hpp                          ||
||     Version:   0.0.0.5                                    ||
||                                                           ||
\*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


#ifndef VERSION_24BIT_DATATYPES
#define VERSION_24BIT_DATATYPES (0x00000005)

#ifndef DECLARE_24BIT_NAMESPACE
#define DECLARE_24BIT_NAMESPACE stepflow
#endif

#ifdef  INT24_LITERAL_OPERATORS
#if     INT24_LITERAL_OPERATORS == 0
#undef  INT24_LITERAL_OPERATORS
#endif
#else
#define INT24_LITERAL_OPERATORS (1)
#endif

#ifdef  INT24_TYPETRAIT_SUPPORT
#if     INT24_TYPETRAIT_SUPPORT == 0
#undef  INT24_TYPETRAIT_SUPPORT
#endif
#else
#define INT24_TYPETRAIT_SUPPORT (1)
#endif


#include <stdint.h>

#define longi long long

#ifndef COMMANDLINER_ESCENTIALS_DEFINED
#include <WaveLib.inl/numbersendian.h>
typedef unsigned char      byte;
typedef unsigned short     word;
#ifndef QT_VERSION
typedef unsigned int       uint;
#define ulong unsigned long long
#endif
typedef signed longi       slong;
typedef float              single;
#define COMMANDLINER_ESCENTIALS_DEFINED (1)
#endif

#ifdef  USE_NAMESPACER 
#include <WaveLib.inl/namespacer.h>
#define BEGIN_INT24SPACE BEGIN_NAMESPACE
#define ENDOF_INT24SPACE ENDOF_NAMESPACE
#define USING_INT24SPACE USING_NAMESPACE
#define INT24TYPES_API NAMESPACE_API
#define Int24sNameSpace(decl) NameSpace(decl)
#else
#ifndef BEGIN_INT24SPACE
#define BEGIN_INT24SPACE namespace DECLARE_24BIT_NAMESPACE {
#define ENDOF_INT24SPACE }
#define USING_INT24SPACE using namespace DECLARE_24BIT_NAMESPACE;
#define INT24TYPES_API
#define Int24sNameSpace( decl ) DECLARE_24BIT_NAMESPACE:: decl
#endif
#endif

#ifdef  HALF_HALF_HPP
#define USE_HALFFLOAT (1)
#elif defined( USE_HALFFLOAT )
namespace half_float { class half; }
#else
#define F16DEF( definition )
#define FLOAT_16BIT
#define f16
#endif

#if defined( USE_HALFFLOAT )
#define F16DEF( definition ) \
typedef INT24TYPES_API definition;
typedef half_float::half FLOAT_16BIT;
#endif

#if NUMBER_ENDIANES == __BIG_ENDIAN
#define SIZE24_MASK 0x00ffffffu
#define PADDINGMASK 0xff000000
#define _24BIT_MASK 0x00ffffff
#define HIGHESTBYTE 2
#else
#define SIZE24_MASK 0xffffff00u
#define PADDINGMASK 0x000000ff
#define _24BIT_MASK 0xffffff00
#define HIGHESTBYTE 0
#endif



/*---------------------------------------*\
* Audiodata sampletype type definitions: *
\*---------------------------------------*/
BEGIN_INT24SPACE
struct UINT_24BIT;
struct INT_24BIT;

// datatypes used for audio sample data:
// (s's are signed, i's are unsigned)
typedef INT24TYPES_API signed char    s8;
typedef INT24TYPES_API unsigned char  i8;
typedef INT24TYPES_API signed short   s16;
typedef INT24TYPES_API unsigned short i16;
F16DEF( INT24TYPES_API FLOAT_16BIT    f16)
typedef INT24TYPES_API UINT_24BIT     i24;
typedef INT24TYPES_API INT_24BIT      s24;
typedef INT24TYPES_API signed int     s32;
typedef INT24TYPES_API unsigned int   i32;
typedef INT24TYPES_API signed longi   s64;
typedef INT24TYPES_API unsigned longi i64;
typedef INT24TYPES_API float          f32;
typedef INT24TYPES_API double         f64;


// additional sample data type limits
// which <stdint.h> not defines, but
// which often may become quiet handy
// when operating audio related data
#define INT8_0DB    ('\x00')
#define UINT8_MIN   ('\x00')
#define UINT8_0DB   ('\x80')
#define INT16_0DB   (0)
#define UINT16_MIN  (0u)
#define UINT16_0DB  (32768u)
#define INT24_MAX   (8388607)
#define INT24_MIN   (-8388608)
#define INT24_0DB   (0)
#define UINT24_MAX  (0xFFFFFFu)
#define UINT24_MIN  (0u)
#define UINT24_0DB  (8388608u)
#define INT32_0DB   (0)
#define UINT32_MIN  (0u)
#define UINT32_0DB  (2147483648u)
#define INT64_0DB   (0ll)
#define UINT64_MIN  (0llu)
#define UINT64_0DB  (9223372036854775808llu)

// type limits of most integer types maybe
// used for transporting audio data,..
// each completed with the constants above 
#define i8_MIN UINT8_MIN
#define i8_MAX UINT8_MAX
#define i8_0DB UINT8_0DB
#define s8_MIN INT8_MIN
#define s8_MAX INT8_MAX
#define s8_0DB INT8_0DB
#define i16_MIN UINT16_MIN
#define i16_MAX UINT16_MAX
#define i16_0DB UINT16_0DB
#define s16_MIN INT16_MIN
#define s16_MAX INT16_MAX
#define s16_0DB INT16_0DB
#define i24_MIN UINT24_MIN
#define i24_MAX UINT24_MAX
#define i24_0DB UINT24_0DB
#define s24_MIN INT24_MIN
#define s24_MAX INT24_MAX
#define s24_0DB INT24_0DB
#define i32_MIN UINT32_MIN
#define i32_MAX UINT32_MAX
#define i32_0DB UINT32_0DB
#define s32_MIN INT32_MIN
#define s32_MAX INT32_MAX
#define s32_0DB INT32_0DB
#define i64_MIN UINT64_MIN
#define i64_MAX UINT64_MAX
#define i64_0DB UINT64_0DB
#define s64_MIN INT64_MIN
#define s64_MAX INT64_MAX
#define s64_0DB INT64_0DB

// Get distinct limit <tLim> of given type <dTyp>  ...like DataTypeLimit(i24,0DB)
#define DataTypeLimmit(dTyp,tLim) dTyp##_##tLim



/*----------------------------------------*\
|* Implementation of 24bit integer types  *|
\*----------------------------------------*/


// helper for proper safe pasting 4on3 / 3on4 bytes
template< typename T32, typename T8 > union Truncator {
    T32  block32;
    T8   byte[4];
};

// abstract base class defining just type relation only
template< typename DataTy = signed, typename BaseTy = char,
template< typename aT = DataTy,typename dT = BaseTy >
          typename Trunc = Truncator > struct
    _24bitTypeAbstractor {
    typedef BaseTy               ArrayDataType;
    typedef const DataTy         AritmeticType;
    typedef Trunc<DataTy,BaseTy> TruncatorType;
    typedef _24bitTypeAbstractor Base24BitType;
    ArrayDataType                bytes[3];
};

// safe paste operator which handles assigning 32bit integers to data arrays of 3byte steplegths
// which ensures no data which follows before or after a target frames 3byte boundary get damaged 
template< typename InputBlock, typename ChannelData > inline
void safePaste4on3( _24bitTypeAbstractor<InputBlock,ChannelData>* ptr_3ByteBlock,
                    const InputBlock val_4ByteBlock ) {
    const union Truncator<InputBlock,ChannelData> truncator = { val_4ByteBlock };
#if NUMBER_ENDIANES == __BIG_ENDIAN
    //ptr_3ByteBlock->bytes[0] = truncator.byte[0];
    //ptr_3ByteBlock->bytes[1] = truncator.byte[1];
    //ptr_3ByteBlock->bytes[2] = truncator.byte[2];
    memcpy( ptr_3ByteBlock, &truncator.byte[0], 3 );
#else
    //ptr_3ByteBlock->bytes[0] = truncator.byte[1];
    //ptr_3ByteBlock->bytes[1] = truncator.byte[2];
    //ptr_3ByteBlock->bytes[2] = truncator.byte[3];
    memcpy( ptr_3ByteBlock, &truncator.byte[1], 3 );
#endif
}


//------------------------------------
// type i24  - UINT_24BIT

typedef struct UINT_24BIT
    : public _24bitTypeAbstractor<uint,byte>
{
    UINT_24BIT( void ) {
        safePaste4on3<uint,byte>( this, 0u );
        // bytes[0] = bytes[1] = bytes[2] = 0;
    };
    UINT_24BIT( const UINT_24BIT& copy ) {
        //bytes[0] = copy.bytes[0];
        //bytes[1] = copy.bytes[1];
        //bytes[2] = copy.bytes[2];
        memcpy( &bytes[0], &copy, 3 );
    }
    UINT_24BIT( const AritmeticType& converted ) {
        safePaste4on3<uint,byte>( this, converted );
    }
    UINT_24BIT( int converted )
        : UINT_24BIT( *(AritmeticType*)&converted ) {
    }
    explicit UINT_24BIT( float abnormal )
        : UINT_24BIT( (AritmeticType)(int)abnormal ) {
    }
    explicit UINT_24BIT( double abnormal )
        : UINT_24BIT( (AritmeticType)(int)abnormal ) {
    }
#ifdef USE_HALFFLOAT
    explicit UINT_24BIT( Float16 abnormal ) // rounding towards 'wave center' (8388608.0_h) would be better here, (but hance to thats no option, rounding to nearest is chosen)
        : UINT_24BIT( half_float::half_cast<WORD_PRCISION,std::round_to_nearest,Float16>( abnormal ) ) {
    }
#endif
    UINT_24BIT( slong cast )
        : UINT_24BIT( (AritmeticType)cast ) {
    }

    inline UINT_24BIT convertFrom( i32 sample ) {
        safePaste4on3<uint, byte>( this, AritmeticType(((i64)sample * UINT24_MAX) / UINT32_MAX) );
        return *this;
    }
    inline UINT_24BIT convertFrom( s16 sample ) {
        safePaste4on3<uint, byte>( this, AritmeticType((((i64)INT16_MAX + sample) * UINT24_MAX) / UINT16_MAX) );
        return *this;
    }
#ifdef USE_HALFFLOAT
    inline UINT_24BIT convertFrom( f16 sample ) {
        safePaste4on3<uint, byte>( this, AritmeticType( half_float::half_cast<WORD_PRCISION,std::round_toward_zero,f16>( sample ) * INT24_MAX ) + UINT24_0DB );
        return *this; }
#endif
    inline UINT_24BIT convertFrom( f32 sample ) {
        safePaste4on3<uint, byte>( this, AritmeticType((sample * INT24_MAX) + UINT24_0DB) );
        return *this;
    }
    inline UINT_24BIT convertFrom( f64 sample ) {
        safePaste4on3<uint, byte>( this, AritmeticType((sample * INT24_MAX) + UINT24_0DB) );
        return *this;
    }

    inline AritmeticType arithmetic_cast() const {
        return SIZE24_MASK & *reinterpret_cast<AritmeticType*>( &bytes[0] );
    }
    inline operator AritmeticType() const {
        return arithmetic_cast();
    }
    inline operator uint() {
        return arithmetic_cast();
    }

    const UINT_24BIT& operator =( const UINT_24BIT& assigned ) {
        //bytes[0] = assigned.bytes[0];
        //bytes[1] = assigned.bytes[1];
        //bytes[2] = assigned.bytes[2];
        return *(UINT_24BIT*)memcpy( &bytes[0], &assigned, 3 );
    }

    const UINT_24BIT& operator =( const AritmeticType& assign ) {
        safePaste4on3<uint,byte>( this, assign );
        return *this;
    }

    inline UINT_24BIT operator +=( const UINT_24BIT& add ) {
        safePaste4on3<uint, byte>( this, arithmetic_cast() + add.arithmetic_cast() );
        return *this;
    }
    inline UINT_24BIT operator -=( const UINT_24BIT& sub ) {
        safePaste4on3<uint, byte>( this, arithmetic_cast() - sub.arithmetic_cast() );
        return *this;
    }
    inline UINT_24BIT operator *=( const UINT_24BIT& mul ) {
        safePaste4on3<uint, byte>( this, arithmetic_cast() * mul.arithmetic_cast() );
        return *this;
    }
    inline UINT_24BIT operator /=( const UINT_24BIT& div ) {
        safePaste4on3<uint, byte>( this, arithmetic_cast() / div.arithmetic_cast() );
        return *this;
    }

    inline bool operator ==( const UINT_24BIT& that ) const {
        return this->arithmetic_cast() == that.arithmetic_cast();
    }
    inline bool operator !=( const UINT_24BIT& that ) const {
        return !operator==( that );
    }
    inline bool operator !(void) const {
        return arithmetic_cast() == 0u;
    }

} UINT_24BIT, *PTR_UINT24, &UINT24_REF;



//-----------------------------------
// type s24  - INT_24BIT

typedef struct INT_24BIT
    : public _24bitTypeAbstractor<int,char>
{
    INT_24BIT( void ) {
    //  bytes[0] = bytes[1] = bytes[2] = 0;
        safePaste4on3<int,char>( this, 0 );
    }
    INT_24BIT( const INT_24BIT& copy ) {
    //  bytes[0] = copy.bytes[0];
    //  bytes[1] = copy.bytes[1];
    //  bytes[2] = copy.bytes[2];
        memcpy( &bytes[0], &copy, 3 );
    }
    INT_24BIT( const AritmeticType& converted ) {
        safePaste4on3<int,char>( this, converted );
    }
#ifdef USE_HALFFLOAT
    explicit INT_24BIT( f16 abnormal )
        : INT_24BIT( half_float::half_cast<WORD_PRCISION,std::round_toward_zero,f16>( abnormal ) ) {
    }
#endif
    explicit INT_24BIT( f32 abnormal )
        : INT_24BIT( (AritmeticType)abnormal ) {
    }
    explicit INT_24BIT( f64 abnormal )
        : INT_24BIT( (AritmeticType)abnormal ) {
    }
    INT_24BIT( slong cast )
        : INT_24BIT( (const AritmeticType)cast ) {
    }

    inline const INT_24BIT& convertFrom( i32 sample ) {
        safePaste4on3<int, char>( this, AritmeticType( ( ((i64)sample * UINT24_MAX) / UINT32_MAX ) - UINT24_0DB ) );
        return *this;
    }
    inline const INT_24BIT& convertFrom( s16 sample ) {
        safePaste4on3<int, char>( this, AritmeticType( ((s64)sample * INT24_MAX) / INT16_MAX ) );
        return *this;
    }
#ifdef USE_HALFFLOAT
    inline const INT_24BIT& convertFrom( f16 sample ) {
        safePaste4on3<int, char>( this, AritmeticType( half_float::half_cast<WORD_PRCISION,std::round_toward_zero,f16>( sample ) * INT24_MAX ) );
        return *this; }
#endif
    inline const INT_24BIT& convertFrom( f32 sample ) {
        safePaste4on3<int, char>( this, AritmeticType( sample * INT24_MAX ) );
        return *this;
    }
    inline const INT_24BIT& convertFrom( f64 sample ) {
        safePaste4on3<int, char>( this, AritmeticType( sample * INT24_MAX ) );
        return *this;
    }

    inline AritmeticType arithmetic_cast() const {
        return ( ( _24BIT_MASK & *reinterpret_cast<AritmeticType*>( &bytes[0] ) ) 
               | ( bytes[HIGHESTBYTE] < 0 ? PADDINGMASK : 0x00000000 ) );
    }
    inline operator AritmeticType() const {
        return arithmetic_cast();
    }
    inline operator int() {
        return arithmetic_cast();
    }

    INT_24BIT& operator =( const INT_24BIT& assigned ) {
    //  bytes[0] = assigned.bytes[0];
    //  bytes[1] = assigned.bytes[1];
    //  bytes[2] = assigned.bytes[2];
        return *(INT_24BIT*)memcpy( &bytes[0], &assigned, 3 );
    //  return *this;
    }
    const INT_24BIT& operator =( const AritmeticType& assign ) {
        safePaste4on3<int, char>( this, assign );
        return *this;
    }

    inline INT_24BIT operator +=( const INT_24BIT& add ) {
        safePaste4on3<int, char>( this, arithmetic_cast() + add.arithmetic_cast() );
        return *this;
    }
    inline INT_24BIT operator -=( const INT_24BIT& sub ) {
        safePaste4on3<int, char>( this, arithmetic_cast() - sub.arithmetic_cast() );
        return *this;
    }
    inline INT_24BIT operator *=( const INT_24BIT& mul ) {
        safePaste4on3<int, char>( this, arithmetic_cast() * mul.arithmetic_cast() );
        return *this;
    }
    inline INT_24BIT operator /=( const INT_24BIT& div ) {
        safePaste4on3<int, char>( this, arithmetic_cast() / div.arithmetic_cast() );
        return *this;
    }

    inline bool operator ==( const INT_24BIT& that ) const {
        return arithmetic_cast() == that.arithmetic_cast();
    }
    inline bool operator !=( const INT_24BIT& that ) const {
        return !operator==(that);
    }
    inline bool operator !(void) const {
     // return (bytes[0] | bytes[1] | bytes[2]) == 0;
        return !arithmetic_cast();
    }

    inline INT_24BIT operator -(void) const {
        return INT_24BIT( -arithmetic_cast() );
    }

} INT_24BIT, *PTR_INT24, &INT24_REF;

ENDOF_INT24SPACE



// typedefs making defined 24bit types accessible global:: 
typedef Int24sNameSpace(UINT_24BIT)  UInt24;
typedef Int24sNameSpace(INT_24BIT)   Int24;
typedef Int24sNameSpace(UINT_24BIT*) UINT24_PTR;
typedef Int24sNameSpace(INT_24BIT*)  INT24_PTR;



#ifdef INT24_LITERAL_OPERATORS
// operators which declare numeric 24bit literals which shall be safe
// when assigning hardcoded values to int24 array data by [] operators
inline const UInt24 operator "" _u24( ulong value ) {
    return UInt24(uint(value & 0x0000000000ffffff));
}
inline const Int24 operator "" _s24( ulong value ) {
    return Int24(int(uint((value >> 63) << 23)
         | uint(value & 0x007fffff)));
}
#endif



#ifdef  INT24_TYPETRAIT_SUPPORT
// optionally declare numeric limits and type traits for
// extending std::numeric_limits and std::type_traits so
// 24bit types are recognized and handled correctly from
// within other cpp std library functions when passed to
#include <type_traits>
#if !defined(_MSC_VER) && !defined(__MINGW32__) && !defined(__MINGW64__)
#include <climits>
#endif
#include <limits>
#ifndef _THROW0
#define _THROW0() noexcept
#endif

#ifdef _MSC_VER
#define LIMITS_NAME_SPACE std::
#define IntegerTypeLimits
#define LIMITS_BASE_CLASS : public _Num_int_base
#else
namespace std {
#define LIMITS_NAME_SPACE
#define LIMITS_BASE_CLASS
#define IntegerTypeLimits \
    static constexpr bool is_specialized = true; \
    static constexpr bool is_integer = true; \
    static constexpr bool is_exact = true; \
    static constexpr int  radix = 2; \
    static constexpr int min_exponent = 0; \
    static constexpr int min_exponent10 = 0; \
    static constexpr int max_exponent = 0; \
    static constexpr int max_exponent10 = 0; \
    static constexpr bool has_infinity = false; \
    static constexpr bool has_quiet_NaN = false; \
    static constexpr bool has_signaling_NaN = false; \
    static constexpr bool has_denorm_loss = false; \
    static constexpr bool is_iec559 = false; \
    static constexpr bool is_bounded = true; \
    static constexpr bool traps = __glibcxx_integral_traps; \
    static constexpr bool tinyness_before = false; \
    static constexpr float_denorm_style has_denorm = denorm_absent; \
    static constexpr float_round_style round_style = round_toward_zero;
#endif


#define NotUseFloatLimits \
static constexpr _Ty::AritmeticType epsilon() _THROW0()\
{ /* return smallest effective increment from 1.0 */ return (0); }\
\
static constexpr _Ty::AritmeticType round_error() _THROW0()\
{ /* return largest rounding error */ return (0); }\
\
static constexpr _Ty::AritmeticType denorm_min() _THROW0()\
{ /* return minimum denormalized value */ return (0); }\
\
static constexpr _Ty::AritmeticType infinity() _THROW0()\
{ /* return positive infinity */ return (0); }\
\
static constexpr _Ty::AritmeticType quiet_NaN() _THROW0()\
{ /* return non-signaling NaN */ return (0); }\
\
static constexpr _Ty::AritmeticType signaling_NaN() _THROW0()\
{ /* return signaling NaN */ return (0); }


#define NoFloatingPointTypeLimits \
        IntegerTypeLimits \
        NotUseFloatLimits
        

template<>
struct LIMITS_NAME_SPACE is_floating_point<Int24>
    : false_type
{ /* determine whether _Ty is floating point */ };

template<>
struct LIMITS_NAME_SPACE is_pointer<INT24_PTR>
    : true_type
{ /* determine whether _Ty is a pointer type */ };

template<>
struct LIMITS_NAME_SPACE is_floating_point<UInt24>
    : false_type
{ /* determine whether _Ty is floating point */ };

template<>
struct LIMITS_NAME_SPACE is_pointer<UINT24_PTR>
    : true_type
{ /* determine whether _Ty is a pointer type */ };


template<> struct LIMITS_NAME_SPACE numeric_limits<Int24>
    LIMITS_BASE_CLASS
{  // limits for type Int24
public:
    typedef Int24 _Ty;

    static constexpr _Ty::AritmeticType(min)() _THROW0()
    { /* return minimum value */ return INT24_MIN; }

    static constexpr _Ty::AritmeticType(max)() _THROW0()
    { /* return maximum value */ return INT24_MAX; }

    static constexpr _Ty::AritmeticType(db0)() _THROW0()
    { /* return zerocross value */ return INT24_0DB; }

    static constexpr _Ty::AritmeticType lowest() _THROW0()
    { /* return most negative value */ return INT24_MIN; }

    // Use Non-floatingpoint implementation defaults
    NoFloatingPointTypeLimits

    // signed type speciffic implementation details
    static constexpr bool is_signed = true;
    static constexpr int digits = CHAR_BIT * sizeof(_Ty) - 1;
    static constexpr int digits10 = ( CHAR_BIT * sizeof(_Ty) - 1
                                     ) * 301L/1000;
#ifndef _MSC_VER
    static constexpr bool is_modulo = false;
#endif
};


template<> struct LIMITS_NAME_SPACE numeric_limits<UInt24>
    LIMITS_BASE_CLASS
{  // limits for type UInt24
public:
    typedef UInt24 _Ty;

    static constexpr _Ty::AritmeticType(min)() _THROW0()
    { /* return minimum value */ return UINT24_MIN; }

    static constexpr _Ty::AritmeticType(max)() _THROW0()
    { /* return maximum value */ return UINT24_MAX; }

    static constexpr _Ty::AritmeticType(db0)() _THROW0()
    { /* return zerocross value */ return UINT24_0DB; }

    static constexpr _Ty::AritmeticType lowest() _THROW0()
    { /* return most negative value */ return UINT24_MIN; }

    // Use Non-floatingpoint implementation defaults
    NoFloatingPointTypeLimits

    // unsigned type speciffic implementation details
    static constexpr bool is_signed = false;
    static constexpr int digits = CHAR_BIT * sizeof(_Ty);
    static constexpr int digits10 = ( CHAR_BIT * sizeof(_Ty)
                                     ) * 301L/1000;
#ifndef _MSC_VER
    static constexpr bool is_modulo = true;
}; }
#else
};
#endif

#if !defined(USE_HALFFLOAT)
#undef f16
#undef FLOAT_24BIT
#endif
#undef F16DEF
#undef SIZE24_MASK
#undef PADDINGMASK
#undef _24BIT_MASK
#undef HIGHESTBYTE
#undef LIMITS_BASE_CLASS
#undef LIMITS_NAME_SPACE
#undef IntegerTypeLimits
#undef NotUseFloatLimits
#undef NoFloatingPointTypeLimits
#endif //INT24_TYPETRAIT_SUPPORT

#undef longi
#endif
