#!/bin/bash

MINISHELL=./minishell

run_test() {
    CMD="$1"
    shift
    EXPECTED_LINES=("$@")

    OUTPUT=$(echo "$CMD" | $MINISHELL | grep "TYPE")

    for expected in "${EXPECTED_LINES[@]}"; do
        echo "$OUTPUT" | grep -q "$expected"
        if [ $? -ne 0 ]; then
            echo "❌ FAIL: $CMD"
            echo "Esperado: $expected"
            echo "Recibido:"
            echo "$OUTPUT"
            exit 1
        fi
    done

    echo "✔️ OK: $CMD"
}

# --------------------------
# TEST 1
# --------------------------

run_test 'echo hola' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "echo"' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "hola"'

# --------------------------
# TEST 2
# --------------------------

run_test 'e"cho" caca "" h"ol\"a"' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "echo"' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "caca"' \
    'TYPE: 0 | QUOTE: 1 | VALUE: ""' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "hol"a"'

# --------------------------
# TEST 3
# --------------------------

run_test 'palabra pal\abra' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "palabra"' \
    'TYPE: 0 | QUOTE: 0 | VALUE: "pal\\abra"' \

echo "🎉 Todos los tests OK"
exit 0
