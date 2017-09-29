rem @echo off
pushd .\build

cl -FC -Zi ..\src\main.cpp user32.lib gdi32.lib

popd