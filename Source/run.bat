@echo off
REM Compilar el programa
g++ -o Main.exe Main.cpp -lws2_32

REM Verificar si la compilación fue exitosa
if %ERRORLEVEL% neq 0 (
    echo Error: Fallo la compilacion.
    exit /b 1
)

REM Ejecutar el programa compilado
Main.exe

REM Verificar si la ejecución fue exitosa
if %ERRORLEVEL% neq 0 (
    echo Error: Fallo la ejecucion.
    exit /b 1
)

REM Salir con éxito
exit /b 0