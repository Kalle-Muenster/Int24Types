using System.Collections.Generic;
using Consola;
using Int24Tests.Tests;

List<string> Args = new List<string>(args);

StdStream.Init(
    CreationFlags.CreateLog
  | CreationFlags.NoInputLog
);

TestCase test = new Int24Test(
    Args.Contains("-v") ||
    Args.Contains("--verbose")
).Run();

return test.wasErrors() ?
  -1 : test.hasPassed() ?
   0 : test.getFailures();
