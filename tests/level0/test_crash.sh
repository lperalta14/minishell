#!/bin/bash

# Comando que procesa sin ejecutar nada real
echo '"""""' | ./minishell > /dev/null 2>&1
STATUS=$?

if [ $STATUS -eq 139 ]; then # 139 = SIGSEGV
    echo "❌ Segmentation Fault detectado"
    exit 1
fi

echo "✔️ No crash (sin segfault)"
exit 0