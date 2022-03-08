@echo off
set _link_=%~dp0linkage
set _arch_=%~1
set _conf_=%~2

set CONSOLASTREMS=c:\WORKSPACE\PROJECTS\ConsolaStreams\bin\core5\v143\%_arch_%\%_conf_%
:: del /f /s /q "%_link_%\*.*"
:: copy "%CONSOLASTREMS%\*.*" "%_link_%"

set _link_=
set _arch_=
set _conf_=
