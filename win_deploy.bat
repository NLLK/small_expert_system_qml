FOR /F %%I IN ('cd') DO @SET "main_dir=%%I"

:: cmd /A /Q /K C:/Qt/6.2.4/mingw_64/bin/qtenv2.bat

call C:/Qt/6.2.4/mingw_64/bin/qtenv2.bat

cd /d %main_dir%
cd

windeployqt.exe --release --no-translations --no-virtualkeyboard --quick --qmldir %main_dir%\ui --dir %main_dir%\release\deploy\ %main_dir%\release\small_expert_system_qml.exe
xcopy /y %main_dir%\release\small_expert_system_qml.exe %main_dir%\release\deploy\
pause