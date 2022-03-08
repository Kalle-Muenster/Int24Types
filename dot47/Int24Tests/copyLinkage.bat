@echo off
set _link_=%~dp0linkage
set _arch_=%~1
set _conf_=%~2

set CONSOLASTREMS=c:\WORKSPACE\PROJECTS\Consola\bin\v4.7\%_arch_%\%_conf_%

copy "%CONSOLASTREMS%\*.dll" "%_link_%"
copy "%CONSOLASTREMS%\*.pdb" "%_link_%"

set _link_=
set _arch_=
set _conf_=
