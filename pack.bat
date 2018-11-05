@echo off
@explorer out\pack
echo Packaging Dave's Tanks
IF EXIST out\pack rmdir /S /Q out\pack
mkdir out\pack >nul
xcopy res out\pack\res\ /e >nul
xcopy out\pack\res\licenses out\pack\licenses\ /e
copy out\dave-tanks.exe out\pack\dave-tanks.exe >nul
copy out\openal32.dll out\pack\openal32.dll >nul
copy license.txt out\pack\license.txt >nul
rmdir /S /Q out\pack\res\afdesign
rmdir /S /Q out\pack\res\licenses