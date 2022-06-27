@echo off

:: Prepare locations
set _name_=Int24Types
set _call_=%CD%
cd %~dp0
set _here_=%CD%
cd..
set _root_=%CD%

:: Set Version
set Int24VersionNumber=00000003
set Int24VersionString=0.0.0.3
set DotNetVersionString=core5

:: Set Dependency locations
if "%ConsolaBinRoot%"=="" (
set ConsolaBinRoot=%_root_%\..\Consola\bin\%DotNetVersionString%
)

:: Set parameters and solution files
call %_root_%\Args "%~1" "%~2" "%~3" "%~4" Int24Types.sln

:: Do the build
cd %_here_%
call MsBuild %_target_% %_args_%
cd %_call_%

:: Cleanup Environment
call %_root_%\Args ParameterCleanUp
