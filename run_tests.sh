#!/bin/bash

MINISHELL=./minishell
BASH=/bin/bash

OUT_DIR=tests/results

mkdir -p "$OUT_DIR"

TOTAL=0
PASSED=0
FAILED=0

echo "==============================="
echo "      MINISHELL TESTER"
echo "==============================="
echo

for file in tests/*.txt
do
    name=$(basename "$file" .txt)

    echo "Running: $name"

    bash_out="$OUT_DIR/${name}_bash.out"
    mine_out="$OUT_DIR/${name}_mine.out"
    diff_out="$OUT_DIR/${name}.diff"

    # bash
    $BASH --noprofile --norc < "$file" > "$bash_out" 2>&1

    # minishell
    $MINISHELL < "$file" > "$mine_out" 2>&1

    # compare
    diff -u "$bash_out" "$mine_out" > "$diff_out"

    if [ $? -eq 0 ]
    then
        echo "OK"
        rm -f "$diff_out"
        PASSED=$((PASSED + 1))
    else
        echo "DIFF ❌"
        echo "saved: $diff_out"
        FAILED=$((FAILED + 1))
    fi

    TOTAL=$((TOTAL + 1))

    echo
done

echo "==============================="
echo "RESULTS"
echo "==============================="

echo "Passed: $PASSED"
echo "Failed: $FAILED"
echo "Total: $TOTAL"

echo
echo "Outputs saved in:"
echo "$OUT_DIR/"