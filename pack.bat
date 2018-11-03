@echo off
echo Packaging Dave's Tanks
IF EXIST out\pack rmdir /S /Q out\pack
mkdir out\pack
xcopy res out\pack\res\ /e
copy out\dave-tanks.exe out\pack\dave-tanks.exe
copy out\openal32.dll out\pack\openal32.dll
rmdir /S /Q out\pack\res\afdesign