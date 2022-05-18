@echo off
set _proj_=%~dp0
set _link_=%~dp0linkage
set _arch_=%~1
set _conf_=%~2

set CONSOLADLL=c:\WORKSPACE\PROJECTS\GITSPACE\Consola\bin\dot48\%_arch_%\%_conf_%
cd %~dp0
cd..
cd..
set _self_=%CD%\bin\dot48\%_arch_%\%_conf_%

del /f /s /q "%_link_%\*.*"

echo "%_self_%\Int24Types.dll" "%_link_%"
echo "%_self_%\Int24Types.pdb" "%_link_%"

copy "%_self_%\Int24Types.dll" "%_link_%"
copy "%_self_%\Int24Types.pdb" "%_link_%"
copy "%CONSOLADLL%\*.dll" "%_link_%"
copy "%CONSOLADLL%\*.pdb" "%_link_%"

set _link_=
set _arch_=
set _conf_=
set _proj_=
