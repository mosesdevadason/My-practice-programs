Programs demonstrating C socket program. These programs use TCP sockets to
implement simple echo server and echo client programs.

echo_server.c - Server programs that prints what the client has sent and echoes
it back to the client

echo_client.c - Client program that gets user input and sends it to the server
and receives the server's reply and displays it in the terminal

To compile

gcc echo_server.c -o server
gcc echo_client.c -o client
