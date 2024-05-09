cls

@echo off

g++ -o Main.exe Main.cpp -lws2_32

if %ERRORLEVEL% neq 0 (
    echo Error: Fallo la compilacion.
    exit /b 1
)

echo Programa compilado con exito

Main.exe

if %ERRORLEVEL% neq 0 (
    echo Error: Fallo la ejecucion.
    exit /b 1
)

echo Programa Ejecutado con exito

exit /b 0