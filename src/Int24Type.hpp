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



using namespace System::Runtime::InteropServices;
namespace System { typedef stepflow::INT_24BIT Int24; }


namespace Stepflow
{

    [StructLayoutAttribute(LayoutKind::Explicit, Size = 3, Pack = 1)]
    public value struct Int24
        : public System::IConvertible
    {
    private:

        stepflow::INT_24BIT& native() {
            return reinterpret_cast<stepflow::INT_24BIT&>( *this );
        }

    public:

        static operator Int24( stepflow::INT_24BIT n ) {
            return reinterpret_cast<Int24&>( n );
        }

        Int24( const stepflow::s24& copy ) {
            native() = copy;
        }

        static explicit operator Int24( double abnormal ) {
            return stepflow::s24( abnormal );
        }

        static const Int24 MinValue = s24_MIN;
        static const Int24 MaxValue = s24_MAX;
        static const Int24 DB0Value = s24_0DB;

        Int24( int converted )
            : Int24( stepflow::s24(converted) ) {
        }
        static operator Int24( int rawcast ) {
            return Int24( rawcast );
        }
        static operator Int24( unsigned int rawcast ) {
            return Int24( (int)rawcast );
        }
        static operator int( Int24 cast ) {
            return cast.native().arithmetic_cast();
        }
        virtual System::String^ ToString(void) override {
            return System::String::Format( "{0}", native().arithmetic_cast() );
        }
        Int24 op_Assignment( int converted ) {
            return native() = stepflow::INT_24BIT( converted );
        }

        Int24 operator +( Int24 other ) {
            return (native() + other.native());
        }
        Int24 operator -( Int24 other ) {
            return (native() - other.native());
        }
        Int24 operator *( Int24 other ) {
            return (native() * other.native());
        }
        Int24 operator *( double other ) {
            return Int24( other * native().arithmetic_cast() );
        }
        Int24 operator /( Int24 other ) {
            return (native() / other.native());
        }

        Int24 operator +=( Int24 other ) {
            return (native() += other.native());
        }
        Int24 operator -=(Int24 other) {
            return (native() -= other.native());
        }
        Int24 operator *=(Int24 other) {
            return (native() *= other.native());
        }
        Int24 operator /=(Int24 other) {
            return (native() /= other.native());
        }

        static bool operator >(Int24 This, Int24 That) {
            return This.native() > That.native();
        }
        static bool operator <(Int24 This, Int24 That) {
            return This.native() < That.native();
        }
        static bool operator >=(Int24 This, Int24 That) {
            return This.native() >= That.native();
        }
        static bool operator <=(Int24 This, Int24 That) {
            return This.native() <= That.native();
        }
        static bool operator ==(Int24 This, Int24 That) {
            return This.native() == That.native();
        }
        static bool operator !=(Int24 This, Int24 That) {
            return This.native() != That.native();
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
}
