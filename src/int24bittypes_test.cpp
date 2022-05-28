#include <stdlib.h>
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#include <conio.h>
#endif
#include <string.h>
#include <stdio.h>
#include "int24bittypes.hpp"

USING_INT24SPACE

enum TEST_RESULT : uint {
    PASS = ('P' | ('A' << 8) | ('S' << 16) | ('S' << 24)),
    FAIL = ('F' | ('A' << 8) | ('I' << 16) | ('L' << 24))
};
#define IS_EQUAL(probe,proof) check = bool(probe.arithmetic_cast()==proof)?"PASS":"FAIL"
#define IS_LESS(probe,then) check = (probe < then)?"PASS":"FAIL", probe.arithmetic_cast(), then
#define IS_MORE(probe,then) check = (probe > then)?"PASS":"FAIL", probe.arithmetic_cast(), then
#define WAS_FAIL (*(uint*)check == FAIL)


uint s24_arythmetics(const char* name)
{
    printf("\nVerifying arithmetic operators of INT_24BIT type\n");
    int failures = 0;
    s24 sample( DataTypeLimmit(s24,0DB) );
    const char* check;
    printf( "%s: %s 24 bit integer: assign '0db': %i\n", IS_EQUAL(sample, 0), name, sample.arithmetic_cast() );
    failures += WAS_FAIL;

    s24 result = sample + 1000;
    printf( "%s: assign '0db + 1000': %i\n", IS_EQUAL(result, 1000),result.arithmetic_cast());
    failures += WAS_FAIL;

    result = sample - 1000;
    printf( "%s: assign '0db - 1000': %i\n", IS_EQUAL(result, -1000), result.arithmetic_cast());
    failures += WAS_FAIL;

    result += 3000;
    printf( "%s: add '3000': %i\n", IS_EQUAL(result,2000), result.arithmetic_cast());
    failures += WAS_FAIL;

    result = sample - 500;
    printf("%s: subtract '500' from 0db: %i\n", IS_EQUAL(result, -500), result.arithmetic_cast());
    failures += WAS_FAIL;

    result *= 2;
    printf( "%s: multiply by '2': %i\n", IS_EQUAL(result, -1000), result.arithmetic_cast());
    failures += WAS_FAIL;

    result = (result / 1.5f);
    printf( "%s: devision by '1.5': %i\n", IS_EQUAL(result, -666), result.arithmetic_cast());
    failures += WAS_FAIL;

    return failures;
}

uint i24_arythmetics(const char* name)
{
    printf("\nVerifying arithmetic operators of UINT_24BIT type\n");
    uint failures = 0;
    i24 sample( DataTypeLimmit(i24,0DB) );
    const char* check;
    printf("%s: %s 24 bit integer: assign '0db': %i\n", IS_EQUAL(sample, 8388608), name, sample.arithmetic_cast());
    failures += WAS_FAIL;

    i24 result = sample + 1000;
    printf("%s: assign '0db + 1000': %i\n", IS_EQUAL(result, 8389608), result.arithmetic_cast());
    failures += WAS_FAIL;

    result = sample - 1000;
    printf("%s: assign '0db - 1000': %i\n", IS_EQUAL(result, 8387608), result.arithmetic_cast());
    failures += WAS_FAIL;

    result += 3000;
    printf("%s: add '3000': %i\n", IS_EQUAL(result, 8390608), result.arithmetic_cast());
    failures += WAS_FAIL;

    result = sample - 500;
    printf("%s: subtract '500' from 0db: %i\n", IS_EQUAL(result, 8388108), result.arithmetic_cast());
    failures += WAS_FAIL;

    result *= 2u;
    printf("%s: multiply by '2': %i\n", IS_EQUAL(result, 16776216), result.arithmetic_cast());
    failures += WAS_FAIL;

    result = (result / 1.5f);
    printf("%s: devision by '1.5': %i\n", IS_EQUAL(result, 11184144), result.arithmetic_cast());
    failures += WAS_FAIL;

    return failures;
}


template<typename TwentyFourBitType> int comparision(const char* check, const char* name)
{
    printf( "\nVerifying comparison operators of %s type\n", name );
    int failures = 0;
    TwentyFourBitType sample;

    sample = 10;
    printf("%s: sample: %i is LESS then int %i\n", IS_LESS(sample, 100));
    failures += WAS_FAIL;

    printf("%s: sample: %i is LESS then float %f\n", IS_LESS(sample, 100.0f));
    failures += WAS_FAIL;

    printf("%s: sample: %i is LESS then uint %u\n", IS_LESS(sample, 100u));
    failures += WAS_FAIL;

    sample = 1000;
    printf("%s: sample: %i is MORE then int %i\n", IS_MORE(sample, 100));
    failures += WAS_FAIL;

    printf("%s: sample: %i is MORE then float %f\n", IS_MORE(sample, 100.0f));
    failures += WAS_FAIL;

    printf("%s: sample: %i is MORE then uint %u\n", IS_MORE(sample, 100u));
    failures += WAS_FAIL;

    return failures;
}

template<typename TwentyFourBitType,typename AssignmentType>
int arrayAssignment( AssignmentType max, const char* nam )
{
    int failures = 0;
    TwentyFourBitType array[10];
    typedef typename TwentyFourBitType::AritmeticType Type32bit;
    AssignmentType sample = max;
    for( int i = 9; i >= 0; --i ) {
        array[i] = sample;
        sample -= 1000;
    }
    printf( "\nVerifying values which have been (from index 9 downward) "
             "assigned to a %s array\n", nam );
    sample += 1000;
    if( ( AssignmentType)array[0] != sample ) {
        printf( "\nFAIL: Sample %u at index 0 was expected to be: %u",
                 AssignmentType( array[0] ), sample );
        failures += 1;
    } else {
        printf( "[%i",  AssignmentType( array[0] ) );
    }
    for( int i = 1; i < 10; ++i ) {
        sample += 1000;
        if( ( AssignmentType)array[i] != sample ) {
            printf( "\nFAIL: Sample %u at index %i was expected to be: %u",
                     AssignmentType( array[i] ), i, sample );
            failures += 1;
        } else {
            printf( ",%u",  AssignmentType( array[i] ) );
        }
    } if ( failures == 0 )
        printf( "] : PASS\n" );
    return failures;
}

int main(int argc,char** argv)
{
    printf( "int24 types test\n");
    int failures = 0;
    const char* check = 0;

    failures += s24_arythmetics("Signed");
    failures += comparision<s24>( check, "Int24" );
    failures += arrayAssignment<s24,int>(s24_MAX,"Int24");
    failures += i24_arythmetics("Unsigned");
    failures += comparision<i24>(check,"UInt24");
    failures += arrayAssignment<i24,uint>(i24_MAX,"UInt24");

    INT_24BIT sample = 5000;
    sample = -sample;
    IS_EQUAL( sample, -5000 );
    printf( "\nVerifying negation operator of signed INT_24BIT type\n"
            "%s: sample = 5000; result = -sample; => result is %i\n",
            check, (int)sample );
    failures += WAS_FAIL;

    if ( failures > 0 ) {
        printf("\n%i tests: FAILED", failures);
    } else {
        printf("\nall tests: PASS\n");
    }
    return failures;
}
