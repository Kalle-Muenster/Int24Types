//////////////////////////////////////////////////////////
// IConvertible interface implementation for Int24Types //
//////////////////////////////////////////////////////////
#include "Int24BitManagedTypes.hpp"



// Int24 Conversions

bool Stepflow::Int24::ToBoolean(System::IFormatProvider^ provider)
{
	return *this != DB0Value;
}

unsigned char Stepflow::Int24::ToByte(System::IFormatProvider^ provider)
{
	return static_cast<unsigned char>(Int24::operator int(*this));
}

wchar_t Stepflow::Int24::ToChar(System::IFormatProvider^ provider)
{
	return static_cast<wchar_t>(Int24::operator int(*this));
}

System::DateTime Stepflow::Int24::ToDateTime(System::IFormatProvider^ provider)
{
	return System::DateTime( Int24::operator int(*this) );
}

System::Decimal Stepflow::Int24::ToDecimal(System::IFormatProvider^ provider)
{
	return System::Decimal( Int24::operator int(*this) );
}

double Stepflow::Int24::ToDouble(System::IFormatProvider^ provider)
{
	return *this;
}

short Stepflow::Int24::ToInt16(System::IFormatProvider^ provider)
{
	return *this;
}

int Stepflow::Int24::ToInt32(System::IFormatProvider^ provider)
{
	return Int24::operator int(*this);
}

long long Stepflow::Int24::ToInt64(System::IFormatProvider^ provider)
{
	return Int24::operator int(*this);
}

System::SByte Stepflow::Int24::ToSByte(System::IFormatProvider^ provider)
{
	return static_cast<System::SByte>(Int24::operator int(*this));
}

float Stepflow::Int24::ToSingle(System::IFormatProvider^ provider)
{
	return static_cast<float>(Int24::operator int(*this));
}

System::String^ Stepflow::Int24::ToString(System::IFormatProvider^ provider)
{
	return Int24::operator int(*this).ToString();
}

System::Object^ Stepflow::Int24::ToType( System::Type^ conversionType, System::IFormatProvider^ provider )
{
	return System::Convert::ChangeType( Int24::operator int( *this ), conversionType, provider );
}

unsigned short Stepflow::Int24::ToUInt16(System::IFormatProvider^ provider)
{
	return static_cast<unsigned short>( Int24::operator int(*this) );
}

unsigned int Stepflow::Int24::ToUInt32(System::IFormatProvider^ provider)
{
	return static_cast<unsigned>(Int24::operator int(*this));
}

unsigned long long Stepflow::Int24::ToUInt64(System::IFormatProvider^ provider)
{
	return Int24::operator int(*this);
}


// UInt24 Conversions

bool Stepflow::UInt24::ToBoolean( System::IFormatProvider^ provider )
{
	return UInt24::operator unsigned int(*this) > 0;
}

unsigned char Stepflow::UInt24::ToByte(System::IFormatProvider^ provider)
{
	return static_cast<byte>( UInt24::operator unsigned int(*this) );
}

wchar_t Stepflow::UInt24::ToChar(System::IFormatProvider^ provider)
{
	return  static_cast<wchar_t>( UInt24::operator unsigned int(*this) );
}

System::DateTime Stepflow::UInt24::ToDateTime(System::IFormatProvider^ provider)
{
	return System::DateTime( UInt24::operator unsigned int(*this) );
}

System::Decimal Stepflow::UInt24::ToDecimal( System::IFormatProvider^ provider )
{
	return System::Decimal( UInt24::operator unsigned int(*this) );
}

double Stepflow::UInt24::ToDouble(System::IFormatProvider^ provider)
{
	return  (double)UInt24::operator unsigned int(*this);
}

short Stepflow::UInt24::ToInt16(System::IFormatProvider^ provider)
{
	return static_cast<short>(UInt24::operator unsigned int(*this));
}

int Stepflow::UInt24::ToInt32(System::IFormatProvider^ provider)
{
	return static_cast<int>(UInt24::operator unsigned int(*this));
}

long long Stepflow::UInt24::ToInt64(System::IFormatProvider^ provider)
{
	return  (long long)UInt24::operator unsigned int(*this);
}

System::SByte Stepflow::UInt24::ToSByte(System::IFormatProvider^ provider)
{
	return static_cast<System::SByte>(UInt24::operator unsigned int(*this));
}

float Stepflow::UInt24::ToSingle(System::IFormatProvider^ provider)
{
	return static_cast<float>(UInt24::operator unsigned int(*this));
}

System::String^ Stepflow::UInt24::ToString(System::IFormatProvider^ provider)
{
	return UInt24::operator unsigned int(*this).ToString();
}

System::Object^ Stepflow::UInt24::ToType(System::Type^ conversionType, System::IFormatProvider^ provider)
{
	return System::Convert::ChangeType( UInt24::operator uint(*this), conversionType, provider );
}

unsigned short Stepflow::UInt24::ToUInt16(System::IFormatProvider^ provider)
{
	return static_cast<word>(UInt24::operator unsigned int(*this));
}

unsigned int Stepflow::UInt24::ToUInt32(System::IFormatProvider^ provider)
{
	return UInt24::operator unsigned int(*this);
}

unsigned long long Stepflow::UInt24::ToUInt64(System::IFormatProvider^ provider)
{
	return UInt24::operator unsigned int(*this);
}
