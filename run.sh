#!/usr/bin/bash

TEST_PATH=./e3_tests

source output2dot.sh < teste.txt > $TEST_PATH/saida.dot
dot -Tpng $TEST_PATH/saida.dot -o $TEST_PATH/saida.png