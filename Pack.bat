@if not "ECHO_STATE"=="" (@echo %ECHO_STATE%) else (@echo off)
set _here_=%CD%
cd /d %~dp0
cd %DotnetVersionString%
cd Int24Tests
dotnet restore Int24Tests.csproj
cd /d %_here_%
set _here_=

