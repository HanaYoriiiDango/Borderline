@echo off
echo Granting permissions...
icacls remove_bom.bat /grant:r "%username%:RX" >nul 2>&1
echo Running initial BOM cleanup...
call remove_bom.bat
echo Setup completed! Open the .sln file in Visual Studio.
pause