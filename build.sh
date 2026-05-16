
echo "Compiling minishell..."
echo "-------------------"
cc -Wall -Wextra -Werror main.c lexer/*.c parser/*.c libft.a -Iinclude -lreadline
echo "Files being compiled"
echo "-------------------"
./a.out
