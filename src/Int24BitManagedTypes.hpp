/*------------------------------------------------------------/
This implements Managed CLR ValueTypes Int24 and UInt24 via
assimillating the int24bittypes.hpp (cpp implementation)

Both types, tried to made usable from within .Net assemblys
in a similar way like these integer type implementatations
defined in the .Net's System namespace.

Cast from/to int24 variables and arrays of (defined in
audio24bittypes.hpp) native 3byte counterpart structures
INT_24BIT and UINT_24BIT same like Int16, Int32 and Int64
do cast to their native integer value counterparts: short,
int and long (as either signed or unsigned variants). So
direct interop without using marshallers is possible between
assemblies which run in managed assemblies and such which
run in unmanaged images. There no need should come up doing
explicite type conversion when working with these 24bit types.
more then as like when working with regular 32bit ints or floats

It supports direct reinterpretation of pointed raw data as
typed arrays (when compiling with 'unsafe' enabled).
All assignment operators which these 24bit types supporting
will 'safe paste' assigned data within 3byte boundaries into
target arrays and so prevent data which follows after a third
byte from getting damaged by unwanted 4th 'ghost' bytes.
--------------------------------------------------------------*/
#include "int24bittypes.hpp"

using namespace System::Runtime::InteropServices;


namespace System {
    typedef  ::Int24 Int24;
    typedef ::UInt24 UInt24;
}


namespace Stepflow
{
    typedef stepflow::s8  s8;
    typedef stepflow::s16 s16;
    typedef stepflow::f32 f32;
    typedef stepflow::f64 f64;
    typedef stepflow::s24 s24;
    typedef stepflow::i24 i24;

    [StructLayoutAttribute(LayoutKind::Explicit, Size = 3, Pack = 1)]
    public value struct Int24 : public System::IConvertible
    {
    private:
        [FieldOffsetAttribute(0)]
        char byte0;
        [FieldOffsetAttribute(1)]
        char byte1;
        [FieldOffsetAttribute(2)]
        char byte2;

    public:
        Int24( const stepflow::s24& copy ) {
            byte0 = copy.bytes[0];
            byte1 = copy.bytes[1];
            byte2 = copy.bytes[2];
        }

        static explicit operator Int24(double abnormal) {
            return stepflow::s24(abnormal);
        }

        operator Stepflow::s24&() {
            pin_ptr<char> p = &byte0;
            return *(s24*)p;
        }

        static operator Int24& (s24& That) {
            return *(Int24*)&That.bytes[0];
        }

        static const Int24 MinValue = s24_MIN;
        static const Int24 MaxValue = s24_MAX;
        static const Int24 DB0Value = s24_0DB;

        Int24(int converted)
            : Int24(s24(converted)) {
        }
        static operator Int24( int rawcast ) {
            return Int24( rawcast );
        }
        static operator Int24( unsigned int rawcast ) {
            return Int24( (int)rawcast );
        }
        static operator int(Int24 cast) {
            return cast.operator s24&().arithmetic_cast();
        }
        virtual System::String^ ToString(void) override {
            return this->operator s24&().arithmetic_cast().ToString();
        }
        Int24 op_Assignment(int converted) {
            this->operator s24&() = converted;
            return *this;
        }
        Int24 operator +(Int24 other) {
            return this->operator s24&() + other.operator s24&();
        }
        Int24 operator -(Int24 other) {
            return this->operator s24&() - other.operator s24&();
        }
        Int24 operator *(Int24 other) {
            return s24(this->operator s24&() * other.operator s24&());
        }
        Int24 operator *(double other) {
            return s24(other * this->operator s24&().arithmetic_cast() );
        }
        Int24 operator /(Int24 other) {
            return s24(this->operator s24&() / other.operator s24&());
        }
        Int24 operator +=(Int24 other) {
            this->operator s24&() += other.operator s24&();
            return *this;
        }
        Int24 operator -=(Int24 other) {
            this->operator s24&() -= other.operator s24&();
            return *this;
        }
        Int24 operator *=(Int24 other) {
            this->operator s24&() *= other.operator s24&();
            return *this;
        }
        Int24 operator /=(Int24 other) {
            this->operator s24&() /= other.operator s24&();
            return *this;
        }

        static bool operator >(Int24 This, Int24 That) {
            return This.operator s24&() > That.operator s24&();
        }
        static bool operator <(Int24 This, Int24 That) {
            return This.operator s24&() < That.operator s24&();
        }
        static bool operator >=(Int24 This, Int24 That) {
            return This.operator s24&() >= That.operator s24&();
        }
        static bool operator <=(Int24 This, Int24 That) {
            return This.operator s24&() <= That.operator s24&();
        }
        static bool operator ==(Int24 This, Int24 That) {
            return This.operator s24&() == That.operator s24&();
        }
        static bool operator !=(Int24 This, Int24 That) {
            return This.operator s24&() != That.operator s24&();
        }

        inline virtual System::TypeCode GetTypeCode(void) {
            return System::TypeCode(-24);
        }

        // Implementations: IConvertible
        virtual bool ToBoolean(System::IFormatProvider^ provider) = System::IConvertible::ToBoolean;
        virtual unsigned char ToByte(System::IFormatProvider^ provider) = System::IConvertible::ToByte;
        virtual wchar_t ToChar(System::IFormatProvider^ provider) = System::IConvertible::ToChar;
        virtual System::DateTime ToDateTime(System::IFormatProvider^ provider) = System::IConvertible::ToDateTime;
        virtual System::Decimal ToDecimal(System::IFormatProvider^ provider) = System::IConvertible::ToDecimal;
        virtual double ToDouble(System::IFormatProvider^ provider) = System::IConvertible::ToDouble;
        virtual short ToInt16(System::IFormatProvider^ provider) = System::IConvertible::ToInt16;
        virtual int ToInt32(System::IFormatProvider^ provider) = System::IConvertible::ToInt32;
        virtual long long ToInt64(System::IFormatProvider^ provider) = System::IConvertible::ToInt64;
        virtual signed char ToSByte(System::IFormatProvider^ provider) = System::IConvertible::ToSByte;
        virtual float ToSingle(System::IFormatProvider^ provider) = System::IConvertible::ToSingle;
        virtual System::String^ ToString(System::IFormatProvider^ provider) = System::IConvertible::ToString;
        virtual System::Object^ ToType(System::Type^ conversionType, System::IFormatProvider^ provider) = System::IConvertible::ToType;
        virtual unsigned short ToUInt16(System::IFormatProvider^ provider) = System::IConvertible::ToUInt16;
        virtual unsigned int ToUInt32(System::IFormatProvider^ provider) = System::IConvertible::ToUInt32;
        virtual unsigned long long ToUInt64(System::IFormatProvider^ provider) = System::IConvertible::ToUInt64;
};


    [StructLayoutAttribute(LayoutKind::Explicit, Size = 3, Pack = 1)]
    public value struct UInt24 : public System::IConvertible
    {
    private:
        [FieldOffsetAttribute(0)]
        byte byte0;
        [FieldOffsetAttribute(1)]
        byte byte1;
        [FieldOffsetAttribute(2)]
        byte byte2;

    public:
        UInt24( const i24& copy ) {
            byte0 = copy.bytes[0];
            byte1 = copy.bytes[1];
            byte2 = copy.bytes[2];
        }

        static explicit operator UInt24(double abnormal) {
            return i24(abnormal);
        }
        operator Stepflow::i24&() {
            pin_ptr<byte> p = &byte0;
            return *(i24*)p;
        }
        static operator UInt24& ( i24& That ) {
            return *(UInt24*)&That.bytes[0];
        }

        static const UInt24 MinValue = i24_MIN;
        static const UInt24 MaxValue = i24_MAX;
        static const UInt24 DB0Value = i24_0DB;

        UInt24(uint converted)
            : UInt24(i24(converted)) {
        }
        static operator UInt24( uint rawcast ) {
            return UInt24( rawcast );
        }
        static operator UInt24( int rawcast) {
            return UInt24( (uint)rawcast );
        }
        static operator unsigned(UInt24 cast) {
            return cast.operator i24&().arithmetic_cast();
        }
        virtual System::String^ ToString(void) override {
            return this->operator i24&().arithmetic_cast().ToString();
        }
        UInt24 op_Assignment(uint converted) {
            this->operator i24&() = converted;
            return *this;
        }
        UInt24 operator +(UInt24 other) {
            return this->operator i24&() + other.operator i24&();
        }
        UInt24 operator -(UInt24 other) {
            return this->operator i24&() - other.operator i24&();
        }
        UInt24 operator *(UInt24 other) {
            return i24(this->operator i24&() * other.operator i24&());
        }
        UInt24 operator *(double other) {
            return (UInt24)( other * this->operator i24&().arithmetic_cast() );
        }
        UInt24 operator /(UInt24 other) {
            return i24(this->operator i24&() / other.operator i24&());
        }
        UInt24 operator +=(UInt24 other) {
            this->operator i24&() += other.operator i24&();
            return *this;
        }
        UInt24 operator -=(UInt24 other) {
            this->operator i24&() -= other.operator i24&();
            return *this;
        }
        UInt24 operator *=(UInt24 other) {
            this->operator i24&() *= other.operator i24&();
            return *this;
        }
        UInt24 operator /=(UInt24 other) {
            this->operator i24&() /= other.operator i24&();
            return *this;
        }

        static bool operator >(UInt24 This, UInt24 That) {
            return This.operator i24&() > That.operator i24&();
        }
        static bool operator <(UInt24 This, UInt24 That) {
            return This.operator i24&() < That.operator i24&();
        }
        static bool operator >=(UInt24 This, UInt24 That) {
            return This.operator i24&() >= That.operator i24&();
        }
        static bool operator <=(UInt24 This, UInt24 That) {
            return This.operator i24&() <= That.operator i24&();
        }
        static bool operator ==(UInt24 This, UInt24 That) {
            return This.operator i24&() == That.operator i24&();
        }
        static bool operator !=(UInt24 This, UInt24 That) {
            return This.operator i24&() != That.operator i24&();
        }

        virtual System::TypeCode GetTypeCode(void) { return System::TypeCode(24); }

        // IConvertible interface
        virtual bool ToBoolean(System::IFormatProvider^ provider) = System::IConvertible::ToBoolean;
        virtual unsigned char ToByte(System::IFormatProvider^ provider) = System::IConvertible::ToByte;
        virtual wchar_t ToChar(System::IFormatProvider^ provider) = System::IConvertible::ToChar;
        virtual System::DateTime ToDateTime(System::IFormatProvider^ provider) = System::IConvertible::ToDateTime;
        virtual System::Decimal ToDecimal(System::IFormatProvider^ provider) = System::IConvertible::ToDecimal;
        virtual double ToDouble(System::IFormatProvider^ provider) = System::IConvertible::ToDouble;
        virtual short ToInt16(System::IFormatProvider^ provider) = System::IConvertible::ToInt16;
        virtual int ToInt32(System::IFormatProvider^ provider) = System::IConvertible::ToInt32;
        virtual long long ToInt64(System::IFormatProvider^ provider) = System::IConvertible::ToInt64;
        virtual signed char ToSByte(System::IFormatProvider^ provider) = System::IConvertible::ToSByte;
        virtual float ToSingle(System::IFormatProvider^ provider) = System::IConvertible::ToSingle;
        virtual System::String^ ToString(System::IFormatProvider^ provider) = System::IConvertible::ToString;
        virtual System::Object^ ToType(System::Type^ conversionType, System::IFormatProvider^ provider) = System::IConvertible::ToType;
        virtual unsigned short ToUInt16(System::IFormatProvider^ provider) = System::IConvertible::ToUInt16;
        virtual unsigned int ToUInt32(System::IFormatProvider^ provider) = System::IConvertible::ToUInt32;
        virtual unsigned long long ToUInt64(System::IFormatProvider^ provider) = System::IConvertible::ToUInt64;
};
}
