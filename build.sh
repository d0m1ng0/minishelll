#!/bin/bash

# echo "Compiling minishell..."
# echo "-------------------"
# cc -Wall -Wextra -Werror src/main.c src/build_cmds.c src/*/*.c libft.a -Iinclude -lreadline
# echo "Files being compiled"
# echo "-------------------"
# gcc -g obj/*/*.o obj/*.o libft.a -lreadline -o app
# ./app

GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

echo "===================="
echo "Norminette (MY files)"
echo "===================="

FILES="
src/builtin
src/env
src/expander
src/lexer
src/parser
src/main.c
src/build_cmds.c
include
"

for f in $FILES
do
    echo -e "\nChecking: $f"

    OUTPUT=$(norminette $f)

    echo "$OUTPUT" | while read -r line
    do
        if echo "$line" | grep -q "Error"; then
            echo -e "${RED}$line${RESET}"
        elif echo "$line" | grep -q "Warning"; then
            echo -e "${YELLOW}$line${RESET}"
        else
            echo -e "${GREEN}$line${RESET}"
        fi
    done
done

echo -e "\nDone."
make