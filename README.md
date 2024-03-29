INTRODUCTION
------------

Thanks for downloading Encrypter.
Encrypter works on C++17 and greater.

CONFIGURATION
-------------

Open terminal and type the following: 
make

Makefile will then exucute the following commands:
g++ cipher.o -o cipher
g++ -c cipher.cpp

ARGUMENTS
---------
To run the program:
./cipher argument-1 argument-2 argument-3 argument-4 argument-5

argument-1 {
    1) 'B' for Block 
    2) 'S' for Stream 
} 

argument-2 {
    input-file(*.txt)
}

argument-3 {
    output-file(*.txt)
}

argument-4 {
    key-file(*.txt)
}

argument-5 {
    1) 'E' for Encryption
    2) 'D' for Decryption
} 

EXAMPLES
--------
./cipher B input1.txt out5.txt key1.txt E
./cipher S input1.txt out5.txt key1.txt E
./cipher B input1.txt out5.txt key1.txt D
./cipher S input1.txt out5.txt key1.txt D

FAQ
---
Q: What is input-file?
A: A file created by the user with a .txt extension.

Q: What is output-file?
A: A file created by the program in the current directory or user specified.

Q: What is key-file?
A: The file created by the user containing a 16-byte key for encryption/provided for decryption.

© Spencer Beer ~ Colorado State University ~ 2022
