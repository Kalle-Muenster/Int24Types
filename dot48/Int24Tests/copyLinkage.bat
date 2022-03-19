@echo off
set _link_=%~dp0linkage
set _arch_=%~1
set _conf_=%~2

set CONSOLASTREMS=c:\WORKSPACE\PROJECTS\GITSPACE\Consola\bin\v4.8\%_arch_%\%_conf_%
cd %~dp0
cd..
cd..
set _self_=%CD%\bin\dot47\%_arch_%\%_conf_%

del /f /s /q "%_link_%\*.*"

echo "%_self_%\Int24Types.dll" "%_link_%"
echo "%_self_%\Int24Types.pdb" "%_link_%"

copy "%_self_%\Int24Types.dll" "%_link_%"
copy "%_self_%\Int24Types.pdb" "%_link_%"
copy "%CONSOLASTREMS%\*.dll" "%_link_%"
copy "%CONSOLASTREMS%\*.pdb" "%_link_%"

set _link_=
set _arch_=
set _conf_=
