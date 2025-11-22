@echo off
chcp 65001
echo ========================================
echo    AUTOMATIC BOM REMOVAL
echo ========================================
echo.

setlocal enabledelayedexpansion
set file_count=0

echo Scanning files for BOM...
for %%f in (*.cpp, *.h, *.hpp, *.json) do (
    powershell -Command "if (Test-Path '%%f') { $content = [System.IO.File]::ReadAllText('%%f'); if ($content.Length -gt 3 -and [int][char]$content[0] -eq 0xFEFF) { echo [FIXED] %%f; [System.IO.File]::WriteAllText('%%f', $content.Substring(3), [System.Text.Encoding]::UTF8); exit 0 } else { echo [OK] %%f } }"
    if !errorlevel! equ 0 (
        set /a file_count+=1
    )
)

echo.
if %file_count% equ 0 (
    echo No files with BOM found.
) else (
    echo Fixed %file_count% files with BOM.
)

echo ========================================
echo    BOM REMOVAL COMPLETED
echo ========================================
echo.