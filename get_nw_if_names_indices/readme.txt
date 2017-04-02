This small program uses Linux APIs to get and list the interface names and if_index of interfaces currently in the system (shown under ifconfig cmd)

uses APIs:
if_nameindex() - Gets a list of pointers to the type struct if_nameindex containing interface information
if_freenameindex() - frees the list of pointers

To compile use

gcc if_name_index.c -o list_interfaces
