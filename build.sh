
echo "Compiling minishell..."
echo "-------------------"
cc -Wall -Wextra -Werror src/main.c src/build_cmds.c src/*/*.c libft.a -Iinclude -lreadline
echo "Files being compiled"
echo "-------------------"
# gcc -g obj/*/*.o obj/*.o libft.a -lreadline -o app
# ./app
