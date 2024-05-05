#!/usr/bin/bash

if [ $# -ne 1 ]; then
    echo "Uso: $0 <arquivo_de_entrada>"
    exit 1
fi

TEST_PATH=./e3_tests

ARQUIVO_ENTRADA=$1

source output2dot.sh < "$ARQUIVO_ENTRADA" > "$TEST_PATH/saida.dot"
dot -Tpng "$TEST_PATH/saida.dot" -o "$TEST_PATH/saida.png"
