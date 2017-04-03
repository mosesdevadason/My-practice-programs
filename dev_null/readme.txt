Small program that tests the behavior of setting stdout to /dev/null.
When stdout is directed to /dev/null anything written to stdout will not appear
in the terminal.

To compile

gcc dev_null.c -o dev_null
