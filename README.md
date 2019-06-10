# processes

This script is university task created to perform recursive cuts on strings and running the new process for each of them.

<b>To run this script please type:</b>

    make main
    
This command will compile main.c file. Then please run it by typing:

    ./main (your string)
    
This script needs an argument in form of string to work properly. The length of string needs to be a power of two, but
if you will not fulfill the requirement the program will cut given string to the proper length.

Example of a proper running command:

    ./main abcdefgh
    

This script is using unix processes so you can use it only on Linux or macOS.
