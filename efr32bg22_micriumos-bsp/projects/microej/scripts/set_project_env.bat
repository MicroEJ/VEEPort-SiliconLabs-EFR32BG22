@echo off

REM Copyright 2019-2021 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'set_project_env.bat' implementation for IAR Embedded Workbench.

REM 'set_project_env' is responsible for
REM - checking the availability of required environment variables 
REM - setting project local variables for 'build.bat' and 'run.bat' 

REM Required Environment Variable
REM IAREW_INSTALLATION_DIR

IF "%IAREW_INSTALLATION_DIR%" == "" (
    ECHO Please set the environment variable 'IAREW_INSTALLATION_DIR'
    exit /B -1
)

REM Set the project variables required by the external build script for IAR Embedded Workbench
SET IAREW_PROJECT_CONFIGURATION=Default
SET IAREW_PROJECT_DIR=%~dp0\..\SimplicityStudio
SET IAREW_BUILD_DIR=%IAREW_PROJECT_DIR%\ewarm-iar\exe
SET IAREW_PROJECT_NAME=microej

ECHO IAREW_INSTALLATION_DIR=%IAREW_INSTALLATION_DIR%
ECHO IAREW_PROJECT_DIR=%IAREW_PROJECT_DIR%
ECHO IAREW_BUILD_DIR=%IAREW_BUILD_DIR%
ECHO IAREW_PROJECT_NAME=%IAREW_PROJECT_NAME%
ECHO IAREW_PROJECT_CONFIGURATION=%IAREW_PROJECT_CONFIGURATION%
exit /B 0