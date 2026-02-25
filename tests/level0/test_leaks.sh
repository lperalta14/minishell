#!/bin/bash

LOG=valgrind_output.txt
FILTERED=valgrind_filtered.txt

echo "echo hola" | valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --errors-to-exitcode=yes \
    --suppressions=readline.supp \
    ./minishell > /dev/null 2> $LOG

STATUS=$?

# Filtramos errores que no son tuyos
grep -v -E "readline|history|rl_|malloc_trim|_int_free|realloc" $LOG > $FILTERED

# ¿Quedan errores después del filtrado?
if grep -q "definitely lost" $FILTERED || grep -q "invalid" $FILTERED; then
    echo "❌ Leaks o errores detectados:"
    cat $FILTERED
    exit 1
fi

echo "✔️ No leaks (ignorando leaks de readline)"
rm -f $LOG $FILTERED
exit 0
