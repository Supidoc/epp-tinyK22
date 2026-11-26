@REM Windows batch file to set the environment, then starts VS Code in that environment
@echo off

set "SDK_ROOT=C:\Raspy\pico\sdk"

@REM Add required directories to PATH if not already present
call :add_path "%SDK_ROOT%\JLink"
call :add_path "%SDK_ROOT%\cmake\bin"
call :add_path "%SDK_ROOT%\ninja"
call :add_path "%SDK_ROOT%\toolchain\bin"
call :add_path "%SDK_ROOT%\doxygen"
call :add_path "%SDK_ROOT%\graphviz\bin"
call :add_path "%SDK_ROOT%\gcovr"

@REM Add more variables as needed
set "MCUXPRESSO_SDK_PATH=C:\repos\epp\Projects\vscode\tinyK22\sdk\"
set "USERPROFILE=C:\Users\erich"
set "TOOLCHAIN_PATH=%SDK_ROOT%\toolchain"
set "SEGGER_PATH=%SDK_ROOT%\JLink"
set "SEGGER_GDB_SERVER=%SEGGER_PATH%\JLinkGDBServerCL.exe"

@REM Launch VS Code in the current directory
REM code -n .

goto :eof

:add_path
set "NEW_PATH=%~1"
echo ;%PATH%; | find /I ";%NEW_PATH%;" >nul

if errorlevel 1 (
    echo Adding %NEW_PATH%
    set "PATH=%PATH%;%NEW_PATH%"
) else (
    echo %NEW_PATH% already exists
)
exit /b
