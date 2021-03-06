using System.Collections.Generic;
using Int24Tests.Tests;
using Consola.Test;
using Consola;

List<string> Args = new List<string>(args);

Consola.StdStream.Init(
    Consola.CreationFlags.CreateLog
  | Consola.CreationFlags.NoInputLog
);

Test test = new Int24Types(
    Args.Contains("-v") ||
    Args.Contains("--verbose"),
    Args.Contains("--xml")
).Run();

return test.wasErrors() ?
  -1 : test.hasPassed() ?
   0 : test.getFailures();
