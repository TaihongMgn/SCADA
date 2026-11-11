@echo off
setlocal
rem --- Run the SCADA debug build from a console so qDebug output is visible ---
set "PATH=D:\Qt\6.12.0\mingw_64\bin;D:\Qt\Tools\mingw1310_64\bin;%PATH%"
set "APPDIR=%~dp0build\Desktop_Qt_6_12_0_MinGW_64_bit_Debug"
if not exist "%APPDIR%\SCADA.exe" (
  echo [ERROR] SCADA.exe not found in %APPDIR%
  echo Build the project in Qt Creator first.
  pause
  exit /b 1
)
cd /d "%APPDIR%"
echo [info] starting SCADA.exe  (close this window to stop the app)
echo.
SCADA.exe
echo.
echo [app exited] press any key to close
pause >nul
