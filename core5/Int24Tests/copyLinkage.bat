@echo off
set _link_=%~dp0linkage
set _arch_=%~1
set _conf_=%~2

set CONSOLASTREMS=c:\WORKSPACE\PROJECTS\GITSPACE\Consola\bin\core5\v142\%_arch_%\%_conf_%

cd %~dp0
cd..
cd..
set _self_=%CD%\bin\core5\%_arch_%\%_conf_%

del /f /s /q "%_link_%\*.*"
copy "%CONSOLASTREMS%\*.*" "%_link_%"
copy "%_self_%\*.dll" "%_link_%"
copy "%_self_%\*.json" "%_link_%"

set _link_=
set _arch_=
set _conf_=
