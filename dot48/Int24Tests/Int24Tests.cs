using System;
using System.Collections.Generic;
using Stepflow;
using Consola.Test;

namespace Stepflow {
    namespace Tests {

        public class Int24BitTypes : Consola.Test.Test
        {
            private Version assemblyversion;

            public Int24BitTypes(TestResults testflags) 
                : base( testflags.HasFlag(TestResults.Verbose), testflags.HasFlag(TestResults.XmlOutput) )
            {
                assemblyversion = System.Reflection.Assembly.GetAssembly(typeof(UInt24)).GetName().Version;
            }

            protected override void OnStartUp()
            {
                Consola.StdStream.Out.WriteLine("version: {0}", assemblyversion.ToString());
                NextCase("Int24Arithmetic");
                    arithmeticS24();
                CloseCase();
                NextCase("Int24ArrayAccesings");
                    nativeArraysS24();
                CloseCase();
                NextCase("UInt24Arithmetic");
                    arithmeticI24();
                CloseCase();
                NextCase("UInt24ArrayAccessings");
                    nativeArraysI24();
                CloseCase();
            }

            private void arithmeticI24()
            {
                CheckStep((UInt24.DB0Value == 8388608u),
                           "UInt24.DB0Value is 8388608");
                UInt24 sample = UInt24.DB0Value + 1000;
                CheckStep(sample == 8389608, "sample 0db + 1000,... expected: {0}", 8389608);
                CheckStep(sample > UInt24.DB0Value, string.Format("sample {0} is MORE then 0db", sample));
                sample -= 2000;
                CheckStep(sample == 8387608, "sample -= 2000,... expected: {0}", 8387608);
                CheckStep(sample < UInt24.DB0Value, string.Format("sample {0} is LESS then 0db", sample));

                sample = sample / 2;
                CheckStep(sample == 4193804, "sample = sample / 2,... expected: {0}", 4193804);
                sample *= 2;
                CheckStep(sample == 8387608, "sample *= 2,... expected: {0}", 8387608);
                sample -= -1000;
                CheckStep(sample == UInt24.DB0Value, "sample -= -1000,... expected:  UInt24.DB0Value");
                sample = UInt24.MaxValue;
                sample++;
                CheckStep(sample == UInt24.MinValue, string.Format("sample at 1 over type maximum: {0}", sample));

                sample = -1;
                CheckStep(sample == UInt24.MaxValue, string.Format("assign -1 to UInt24 varable: {0}", sample));
            }

            private void arithmeticS24()
            {
                CheckStep((Int24.DB0Value == 0),
                           "Int24.DB0Value is 0");
                Int24 sample = Int24.DB0Value + 1000;
                CheckStep(sample == 1000, "sample = 0db + 1000,... expected: {0}", 1000);
                CheckStep(sample > Int24.DB0Value, string.Format("sample {0} is MORE then 0db", sample));
                sample -= 2000;
                CheckStep(sample == -1000, "sample -= 2000,... expected: {0}", -1000);
                CheckStep(sample < Int24.DB0Value, string.Format("sample {0} is LESS then 0db", sample));

                sample = sample / 2;
                CheckStep(sample == -500, "sample = sample / 2,... expected: {0}", -500);
                sample *= 2;
                CheckStep(sample == -1000, "sample *= 2,... expected: {0}", -1000);
                sample = -sample;
                CheckStep(sample == 1000, "sample = -sample,... expected: {0}", 1000);
                sample += -1000;
                CheckStep(sample == Int24.DB0Value, "sample += -1000,.. expected: Int24.DB0Value");
                sample = Int24.MaxValue;
                sample++;
                CheckStep(sample == Int24.MinValue, string.Format("sample at 1 over type maximum: {0}", sample));

                unsafe
                {
                    sample = -1;
                    UInt24 maxval = *(UInt24*)&sample;
                    bool equal = maxval == UInt24.MaxValue;
                    CheckStep(equal, "reinterprete cast Int24 variable of value -1 as UInt24 variable: {0}", maxval);
                }

            }

            public void nativeArraysS24()
            {

                Int32[] proof = new Int32[10] {
                    8388605,8388606,8388607,-8388608,-8388607,
                    -8388606,-8388605,-8388604,-8388603,-8388602
                };
                Int24[] array = new Int24[10] {
                    8388605,8388606,8388607,-8388608,-8388607,
                    -8388606,-8388605,-8388604,-8388603,-8388602
                };
                for (int i = 0; i < 10; ++i)
                {
                    CheckStep(array[i] == proof[i], "sample at index {0} is {1},.. expected: {2}", i, array[i], proof[i]);
                }
                unsafe
                {
                    fixed (Int24* ptInt24 = &array[0])
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
                    CheckStep(array[i] == 8388123, "array at index {0} is {1},.. expected: {2}", i, array[i], 8388123);
                }
            }

            public void nativeArraysI24()
            {
                UInt32[] proof = new UInt32[10] {
                    8388000,8388001,8388002,8388003,8388004,
                    8388005,8388006,8388007,8388008,8388009
                };
                UInt24[] array = new UInt24[10] {
                    8388000,8388001,8388002,8388003,8388004,
                    8388005,8388006,8388007,8388008,8388009
                };
                for (int i = 0; i < 10; ++i)
                {
                    CheckStep(array[i] == proof[i], "sample at index {0} is {1},.. expected: {2}", i, array[i], proof[i]);
                }
                unsafe
                {
                    fixed (UInt24* ptUInt24 = &array[0])
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
                    CheckStep(array[i] == 8388123, "array at index {0} is {1},.. expected: {2}", i, array[i], 8388123);
                }
            }
        }

        public class Int24Tests
        {
            public static int Main( string[] args )
            {
                Consola.StdStream.Init(
                     Consola.CreationFlags.OutputLog
                );

                int failures = 0;
                TestResults outputoptions = TestResults.TextOutput;
                foreach (string arg in args)
                {
                    if (arg.StartsWith("--"))
                    {
                        if (arg == "--verbose")
                        {
                            outputoptions |= TestResults.Verbose;
                        } else if (arg == "--xmllogs") {
                            outputoptions |= TestResults.XmlOutput;
                        }
                    }
                    else if (arg.Length > 1)
                    {
                        if (arg[0] == '-' && arg.Length == 2)
                        {
                            if ( arg[1] == 'v' ) outputoptions |= TestResults.Verbose;
                            if ( arg[1] == 'x' ) outputoptions |= TestResults.XmlOutput;
                        } 
                    }
                }

                Test result = new Int24BitTypes( outputoptions ).Run();
                failures += result.getFailures();

                if ( result.hasCrashed() ) {
                    string[] errs = result.getErrors();
                    Consola.StdStream.Err.Stream.Put("\n...FATAL ").Put(errs.Length).Put(" Error happend:\n");
                    for( int i=0; i<errs.Length; ++i ) {
                        Consola.StdStream.Err.Stream.Put("ERROR[").Put(i).Put("]: ").Put( errs[i] ).Put("\n");
                    } Consola.StdStream.Err.Stream.End();
                } else
                if ( result.hasPassed() )
                {
                    Consola.StdStream.Out.WriteLine("\n...All PASS");
                } else
                {
                    Consola.StdStream.Err.WriteLine("\n...{0} FAIL", failures);
                }
                return failures;
            }
        }
    }
}
