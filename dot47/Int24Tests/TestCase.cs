using System;
using System.Collections.Generic;
using Consola;

namespace Consola.Tests
{
    abstract public class TestCase
    {
        private uint step = 0;
        private int  count = -1;
        private int failures = -1;
        protected bool verbose = false;
        private List<string> errors;
        private string current;
        public bool hasFailed()
        {
            return failures != 0;
        }
        public bool hasPassed()
        {
            return !( hasFailed() || wasErrors() );
        }
        public bool wasErrors()
        {
            return errors.Count > 0;
        }
        public int getFailures()
        {
            return failures;
        }
        public string[] getErrors()
        {
            return errors.ToArray();
        }
        public int setPass( string description )
        {
            if (failures < 0)
                return failures;
            if (count > 0)
            {
                StdStream.Out.WriteLine("PASS [{0}.{1}]: {2}", step, count, description);
            }
            else
            {
                StdStream.Out.WriteLine("STEP[{0}]: {1} Tests PASSED", step, description);
            }
            return (int)(step + count - failures);
        }
        public int setFail( string description )
        {
            if (failures < 0)
                return failures;
            if (count > 0)
            {
                StdStream.Err.WriteLine("FAIL [{0}.{1}]: {2}", step, count, description);
            }
            else
            {
                StdStream.Err.WriteLine("STEP[{0}]: {1} FAILED Tests", step, description);
            }
            return ++failures;
        }
        public int setFatal( string description, bool continueAnyway )
        {
            if( failures > 0 ) {
                failures = 0;
            }
            if ( count > 0 ) {
                description = string.Format("FATAL [{0}.{1}]: {2}", step, count, description );
            } else {
                description = string.Format("STEP[{0}]: {1} test crashed", step, description );
            }
            StdStream.Err.WriteLine( description );
            errors.Add( description );
            if( !continueAnyway )
                throw new Exception("FATAL");
            return --failures;
        }
        public void StepCheck( bool check, string description )
        {
            if( failures < 0 ) {
                return;
            } ++count;
            if( check ) {
                setPass( description );
            } else {
                setFail( description );
            }
        }
        public void StepFailed( string fmt, params object[] args )
        {
            StepCheck( false, string.Format(fmt,args) );
        }
        public void StepPassed( string fmt, params object[] args )
        {
            StepCheck( true, string.Format(fmt,args) );
        }
        public void CountStep( bool pass, string description, params object[] args )
        {
            if ( pass ) {
                if( verbose ) {
                    StepPassed(description, args);
                } else ++count;
            } else {
                 StepFailed(description, args);
            }
        }
        public bool NextStep( string stepname )
        {
            if( failures < 0 )
                return false;
            StdStream.Out.Stream.Put("\n------------------ Next Step: ")
                                .Put(stepname)
                                .Put(" ------------------\n").End();
            current = stepname;
            count = 0;
            ++step;
            return true;
        }
        public int StepDone( bool successive )
        {
            int total = count;
            count = 0;
            if( successive ) {
                return setPass( string.Format("{0}: {1}", current, total) );
            } else return setFail( string.Format("{0}: {1}", current, failures) );
        }

        public TestCase( bool logall )
        {
            errors = new List<string>();
            verbose = logall;
            failures = 0;
            count = 0;
        }

        public TestCase Run()
        {
            StdStream.Out.WriteLine("\n#####################################################################");
            StdStream.Out.WriteLine("# TEST: {0}", this.GetType().Name);
            StdStream.Out.WriteLine("#####################################################################");
            try { StartRun();
            } catch( Exception exception ) {
                setFatal( string.Format("{0}: {1} {2}", current, errors.Count, exception.Message ), true );
            } return this;
        }

        protected abstract void StartRun();
    }
}
