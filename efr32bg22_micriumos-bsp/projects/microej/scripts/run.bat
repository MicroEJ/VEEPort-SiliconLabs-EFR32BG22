@echo off

REM Copyright 2019-2021 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'run.bat' implementation for IAR Embedded Workbench.

REM 'run.bat' is responsible for flashing the executable file on the target device 
REM then resetting target device

REM This file has concatenated and made portable options from 'settings/lpcxpresso.Debug.driver.xcl' and 'lpcxpresso.Debug.general.xcl'
REM Any changes in the IAR settings must be reported to the command line above.

CALL "%~dp0\set_project_env.bat"
IF %ERRORLEVEL% NEQ 0 (
	exit /B %ERRORLEVEL%
)

@echo on 

"%IAREW_INSTALLATION_DIR%\common\bin\cspybat" --download_only "%IAREW_INSTALLATION_DIR%\arm\bin\armproc.dll" "%IAREW_INSTALLATION_DIR%\arm\bin\armjlink2.dll" "%IAREW_BUILD_DIR%\microej.out" --plugin="%IAREW_INSTALLATION_DIR%\arm\bin\armbat.dll" --device_macro="%IAREW_INSTALLATION_DIR%\arm\config\debugger\SiliconLaboratories\Gecko_SE.dmac" --backend "--endian=little" "--cpu=Cortex-M33" "--fpu=VFPv5_SP" "-p" "%IAREW_INSTALLATION_DIR%\arm\CONFIG\debugger\SiliconLaboratories\EFR32BG22C224F512IM40.ddf" "--semihosting" "--device=EFR32BG22C224F512IM40" "--drv_communication=USB0" "--drv_interface_speed=auto" "--jlink_initial_speed=1000" "--jlink_reset_strategy=0,0" "--drv_interface=SWD" "--drv_catch_exceptions=0x000" "--jlink_device_name=EFR32BG22CxxxF512"