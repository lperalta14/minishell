#!/bin/bash

# Test 0: minishell devuelve el input correctamente
# Compatible con banners y prompt "minishell>"

MINISHELL=./minishell
EXPECTED="hola"

# 1) Comprobar que el binario existe
if [ ! -f $MINISHELL ]; then
    echo "❌ minishell no existe"
    exit 1
fi

# 2) Ejecutar minishell con un input simple
#    redirige stdin con echo y descarta errores
OUTPUT=$(echo "$EXPECTED" | $MINISHELL 2>/dev/null)

# 3) Limpiar output de banners y espacios
CLEAN_OUTPUT=$(echo "$OUTPUT" | \
    grep -v "o__ __o" | \      # ignorar banner gigante
    grep -v "^$" | \           # ignorar líneas vacías
    tr -d '\r' | \             # eliminar retornos de carro
    sed 's/[[:space:]]*$//')   # eliminar espacios finales

# 4) Filtrar prompts "minishell>" y capturar la última línea (la que contiene el input)
INPUT_LINE=$(echo "$CLEAN_OUTPUT" | grep -v "^minishell>" | tail -n 1)

# 5) Comparar con el esperado
if [ "$INPUT_LINE" = "$EXPECTED" ]; then
    echo "✅ Test 0 OK"
    exit 0
else
    echo "❌ Test 0 FAIL"
    echo "Esperado : '$EXPECTED'"
    echo "Recibido : '$INPUT_LINE'"
    exit 1
fi
