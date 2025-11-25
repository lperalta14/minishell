#!/bin/bash

# Test 0: minishell devuelve el input, adaptado al prompt y banners

MINISHELL=./minishell

# 1) Probar que el binario existe
if [ ! -f $MINISHELL ]; then
    echo "❌ minishell no existe"
    exit 1
fi

# 2) Ejecutar minishell con un input simple
OUTPUT=$(echo "hola" | $MINISHELL 2>/dev/null)

# 3) Limpiar output de banners y espacios
#    - Ignora líneas con "o__ __o" (banner gigante)
#    - Ignora líneas vacías
#    - Quita retornos de carro y espacios finales
CLEAN_OUTPUT=$(echo "$OUTPUT" | grep -v "o__ __o" | grep -v "^$" | tr -d '\r' | sed 's/[[:space:]]*$//')

# 4) Capturar la última línea (el input procesado)
LAST_LINE=$(echo "$CLEAN_OUTPUT" | tail -n 1)

# 5) Comparar con el esperado
EXPECTED="hola"

if [ "$LAST_LINE" = "$EXPECTED" ]; then
    echo "✅ Test 0 OK"
    exit 0
else
    echo "❌ Test 0 FAIL"
    echo "Esperado : '$EXPECTED'"
    echo "Recibido : '$LAST_LINE'"
    exit 1
fi
