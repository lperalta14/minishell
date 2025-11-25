#!/bin/bash

# Test 0: minishell devuelve el input cuando no es interactivo

MINISHELL=./minishell

# 1) Probar que el binario existe
if [ ! -f $MINISHELL ]; then
    echo "❌ minishell no existe"
    exit 1
fi

# 2) Ejecutar minishell con un input simple
OUTPUT=$(echo "hola" | $MINISHELL 2>/dev/null)

# 3) Limpiar output de espacios / saltos de línea
OUTPUT=$(echo "$OUTPUT" | tr -d '\r' | sed 's/[[:space:]]*$//')

# 4) Comprobar que el output contiene exactamente "hola"
if [ "$OUTPUT" = "minishell> hola" ]; then
    echo "✅ Test 0 OK"
    exit 0
else
    echo "❌ Test 0 FAIL"
    echo "Esperado : hola"
    echo "Recibido : '$OUTPUT'"
    exit 1
fi
