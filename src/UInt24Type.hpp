/*///////////////////////////////////////////////////////////*\
||                                                           ||
||     File:      UInt24Type.hpp                             ||
||     Author:    autogenerated                              ||
||     Generated: by Command Generator v.0.1                 ||
||                                                           ||
\*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
#ifndef _UInt24Type_hpp_
#define _UInt24Type_hpp_


using namespace System::Runtime::InteropServices;
namespace System { typedef stepflow::UINT_24BIT UInt24; }


namespace Stepflow
{
    [StructLayoutAttribute(LayoutKind::Explicit, Size = 3, Pack = 1)]
    public value struct UInt24 
        : public System::IConvertible
    {
    private:

        stepflow::UINT_24BIT& native() {
            return reinterpret_cast<stepflow::UINT_24BIT&>( *this );
        }

    public:
        
        UInt24( const stepflow::UINT_24BIT& copy ) {
            native() = copy;
        }
        
        static explicit operator UInt24( double abnormal ) {
            return stepflow::UINT_24BIT( abnormal );
        }

        static operator UInt24( stepflow::UINT_24BIT& That ) {
            return reinterpret_cast<UInt24&>( That );
        }

        static const UInt24 MinValue = i24_MIN;
        static const UInt24 MaxValue = i24_MAX;
        static const UInt24 DB0Value = i24_0DB;
        
        UInt24( uint converted )
            : UInt24( stepflow::i24(converted) ) {
        }
        static operator UInt24( uint rawcast ) {
            return UInt24( rawcast );
        }
        static operator UInt24( int rawcast ) {
            return UInt24( (uint)rawcast );
        }
        static operator unsigned( UInt24 cast ) {
            return cast.native().arithmetic_cast();
        }
        virtual System::String^ ToString( void ) override {
            return System::String::Format( "{0}", native().arithmetic_cast() );
        }

        UInt24 op_Assignment( uint converted ) {
            return UInt24( converted );
        }
        static UInt24 operator +(UInt24 This, UInt24 That) {
            return (This.native() + That.native());
        }
        static UInt24 operator -(UInt24 This, UInt24 That) {
            return (This.native() - That.native());
        }
        static UInt24 operator *(UInt24 This, UInt24 That) {
            return (This.native() * That.native());
        }
        static UInt24 operator *(UInt24 This, double That) {
            return stepflow::i24( That * This.native().arithmetic_cast() );
        }
        static UInt24 operator /(UInt24 This, UInt24 That) {
            return (This.native() / That.native());
        }

        UInt24 operator +=( UInt24 That ) {
            return ( native() += That.native() );
        }
        UInt24 operator -=(UInt24 other) {
            return ( native() -= other.native() );
        }
        UInt24 operator *=(UInt24 other) {
            return ( native() *= other.native() );
        }
        UInt24 operator /=(UInt24 other) {
            return ( native() /= other.native() );
        }

        static bool operator >(UInt24 This, UInt24 That) {
            return This.native() > That.native();
        }
        static bool operator <(UInt24 This, UInt24 That) {
            return This.native() < That.native();
        }
        static bool operator >=(UInt24 This, UInt24 That) {
            return This.native() >= That.native();
        }
        static bool operator <=(UInt24 This, UInt24 That) {
            return This.native() <= That.native();
        }
        static bool operator ==(UInt24 This, UInt24 That) {
            return This.native() == That.native();
        }
        static bool operator !=(UInt24 This, UInt24 That) {
            return This.native() != That.native();
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
} //end of Stepflow

#endif
