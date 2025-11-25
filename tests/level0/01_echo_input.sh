#!/bin/bash

# Test mínimo nivel 0
OUTPUT=$(./minishell <<< "hola")
EXPECTED="hola"

if [[ "$OUTPUT" == "$EXPECTED" ]]; then
  echo "✅ Level 0 Test 01 OK"
  exit 0
else
  echo "❌ Level 0 Test 01 FAIL"
  echo "Salida obtenida: $OUTPUT"
  exit 1
fi