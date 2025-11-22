@echo off
chcp 65001 >nul
echo Removing BOM from source files...

REM Удаляем BOM из всех исходных файлов
for %%f in (*.cpp, *.h, *.hpp, *.json) do (
    powershell -Command "if (Test-Path '%%f') { $content = [System.IO.File]::ReadAllText('%%f'); if ($content.Length -gt 3 -and [int][char]$content[0] -eq 0xFEFF) { echo Fixing %%f; [System.IO.File]::WriteAllText('%%f', $content.Substring(3), [System.Text.Encoding]::UTF8) } }" >nul
)

echo BOM removal completed.