@echo off
chcp 65001 >nul
echo Removing BOM from source files...

for %%f in (*.cpp, *.h, *.hpp, *.json) do (
    echo Processing %%f
    powershell -Command "$content = [System.IO.File]::ReadAllText('%%f', [System.Text.Encoding]::UTF8); $utf8NoBom = New-Object System.Text.UTF8Encoding($false); [System.IO.File]::WriteAllText('%%f', $content, $utf8NoBom)"
)

echo BOM removal completed!
echo Rebuild your project.