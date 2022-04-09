using System;
using Stepflow;

namespace Int24Tests {
    namespace Tests
    {

        public class Int24Types : Consola.Tests.TestSuite
        {
            private Version  assemblyversion;
            private UInt32[] proofUint24;
            private UInt24[] arrayUInt24;
            private Int32[]  proofInt24;
            private Int24[]  arrayInt24;

            public Int24Types(bool verbose) : base(verbose)
            {
                assemblyversion = System.Reflection.Assembly.GetAssembly(typeof(UInt24)).GetName().Version;

                proofUint24 = new UInt32[10] {
                    8388000,8388001,8388002,8388003,8388004,
                    8388005,8388006,8388007,8388008,8388009
                };
                arrayUInt24 = new UInt24[10] {
                    8388000,8388001,8388002,8388003,8388004,
                    8388005,8388006,8388007,8388008,8388009
                };

                proofInt24 = new Int32[10] {
                    8388605,8388606,8388607,-8388608,-8388607,
                    -8388606,-8388605,-8388604,-8388603,-8388602
                };
                arrayInt24 = new Int24[10] {
                    8388605,8388606,8388607,-8388608,-8388607,
                    -8388606,-8388605,-8388604,-8388603,-8388602
                };
            }

            protected override void Test()
            {
                Consola.StdStream.Out.WriteLine("version: {0}", assemblyversion);

                NextCase("Int24 - Arithmetic");
                arithmeticS24();
                CloseCase(CurrentCase);

                NextCase("Int24 - Array Acces");
                nativeArraysS24();
                CloseCase(hasPassed());

                NextCase("UInt24 - Arithmetic");
                arithmeticI24();
                CloseCase(hasPassed());
                
                NextCase("UInt24 - Array Access");
                nativeArraysI24();
                CloseCase(hasPassed());
            }

            private void arithmeticI24()
            {
                CheckStep( (UInt24.DB0Value == 8388608u),
                           "UInt24.DB0Value is 8388608" );

                UInt24 sample = UInt24.DB0Value + 1000;
                CheckStep( sample == 8389608, "sample 0db + 1000,... expected: {0}", 8389608);
                CheckStep( sample > UInt24.DB0Value, string.Format( "sample {0} is MORE then 0db", sample ) );
                sample -= 2000;
                CheckStep( sample == 8387608, "sample -= 2000,... expected: {0}", 8387608);
                CheckStep( sample < UInt24.DB0Value, string.Format( "sample {0} is LESS then 0db", sample ) );

                sample = sample / 2;
                CheckStep( sample == 4193804, "sample = sample / 2,... expected: {0}", 4193804 );
                sample *= 2;
                CheckStep( sample == 8387608, "sample *= 2,... expected: {0}", 8387608 );
                sample -= -1000;
                CheckStep( sample == UInt24.DB0Value, "sample -= -1000,... expected:  UInt24.DB0Value" );
                sample = UInt24.MaxValue;
                sample++;
                CheckStep( sample == UInt24.MinValue, string.Format( "sample at 1 over type maximum: {0}", sample ) );

                sample = -1;
                CheckStep( sample == UInt24.MaxValue, string.Format( "assign -1 to UInt24 varable: {0}", sample ) );
            }

            private void arithmeticS24()
            {
                CheckStep( (Int24.DB0Value == 0),
                           "Int24.DB0Value is 0" );

                Int24 sample = Int24.DB0Value + 1000;
                CheckStep( sample == 1000, "sample = 0db + 1000,... expected: {0}", 1000 );
                CheckStep( sample > Int24.DB0Value, string.Format( "sample {0} is MORE then 0db", sample ) );
                sample -= 2000;
                CheckStep( sample == -1000, "sample -= 2000,... expected: {0}", -1000 );
                CheckStep( sample < Int24.DB0Value, string.Format( "sample {0} is LESS then 0db", sample ) );

                sample = sample / 2;
                CheckStep( sample == -500, "sample = sample / 2,... expected: {0}", -500 );
                sample *= 2;
                CheckStep( sample == -1000, "sample *= 2,... expected: {0}", -1000 );
                sample = -sample;
                CheckStep( sample == 1000, "sample = -sample,... expected: {0}", 1000 );
                sample += -1000;
                CheckStep( sample == Int24.DB0Value, "sample += -1000,.. expected: Int24.DB0Value" );
                sample = Int24.MaxValue;
                sample++;
                CheckStep( sample == Int24.MinValue, string.Format( "sample at 1 over type maximum: {0}", sample ) );

                unsafe {
                    sample = -1;
                    UInt24 maxval = *(UInt24*)&sample;
                    bool equal = maxval == UInt24.MaxValue;
                    CheckStep(equal, "reinterprete cast Int24 variable of value -1 as UInt24 variable: {0}", maxval);
                }
            }

            public void nativeArraysS24()
            {


                for (int i = 0; i < 10; ++i)
                {
                    CheckStep( arrayInt24[i] == proofInt24[i], "sample at index {0} is {1},.. expected: {2}", i, arrayInt24[i], proofInt24[i]);
                }
                unsafe
                {
                    fixed (Int24* ptInt24 = &arrayInt24[0])
                    {
                        Int24* end = ptInt24 - 1;
                        for (Int24* dst = ptInt24 + 9; dst != end; --dst)
                        {
                            *dst = 8388123;
                        };
                        end = ptInt24 + 10;
                        for (Int24* dst = ptInt24; dst != end; ++dst)
                        {
                            CheckStep(*dst == 8388123, "sample is {0},.. expected: {1}", *dst, 8388123);
                        };
                    }
                }
                for (int i = 0; i < 10; ++i)
                {
                    CheckStep( arrayInt24[i] == 8388123, "array at index {0} is {1},.. expected: {2}", i, arrayInt24[i], 8388123);
                }
            }

            public void nativeArraysI24()
            {

                for (int i = 0; i < 10; ++i)
                {
                    CheckStep( arrayUInt24[i] == proofUint24[i], "sample at index {0} is {1},.. expected: {2}", i, arrayUInt24[i], proofUint24[i]);
                }
                unsafe
                {
                    fixed (UInt24* ptUInt24 = &arrayUInt24[0])
                    {
                        UInt24* end = ptUInt24 - 1;
                        for (UInt24* dst = ptUInt24 + 9; dst != end; --dst)
                        {
                            *dst = 8388123;
                        };
                        end = ptUInt24 + 10;
                        for (UInt24* dst = ptUInt24; dst != end; ++dst)
                        {
                            CheckStep(*dst == 8388123, "sample is {0},.. expected: {1}", *dst, 8388123);
                        };
                    }
                }
                for (int i = 0; i < 10; ++i)
                {
                    CheckStep( arrayUInt24[i] == 8388123, "array at index {0} is {1},.. expected: {2}", i, arrayUInt24[i], 8388123);
                }
            }
        }
    }
}
