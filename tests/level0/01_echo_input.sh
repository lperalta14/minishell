#!/bin/bash

MINISHELL=./minishell

# 1) Verificar que el binario existe
if [ ! -f "$MINISHELL" ]; then
    echo "❌ minishell no existe"
    exit 1
fi

# 2) Ejecutar minishell en modo no interactivo con un input
INPUT="hola"
OUTPUT=$(echo "$INPUT" | $MINISHELL 2>/dev/null)

# 3) Limpiar la salida:
#    - Eliminar separadores y líneas de debug
#    - Quedarnos SOLO con las líneas VALUE:
FIRST_VALUE=$(echo "$OUTPUT" \
    | grep 'VALUE:' \
    | head -n 1 \
    | sed -E 's/.*VALUE: "(.*)"/\1/')

EXPECTED="hola"

if [ "$FIRST_VALUE" = "$EXPECTED" ]; then
    echo "✅ Test 0 OK"
    exit 0
else
    echo "❌ Test 0 FAIL"
    echo "Esperado: '$EXPECTED'"
    echo "Recibido: '$FIRST_VALUE'"
    exit 1
fi
