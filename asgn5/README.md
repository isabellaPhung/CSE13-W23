Isabella Phung 1702285
Winter 2023
Lab 5: Encryption: a Key Aspect of Electronic Communication
____________
Description:
Program contains keygen.c, decryptor.c, encryptor.c, numtheory.c, numtheory.h, ss.c, ss.h, and a Makefile. 
Without some form of encryption there's no privacy on the internet. With increasing services that people's livelihoods rely on, reliable and safe encryption is critical. The following library implements Schmidt-Samoa encryption.
This library contains 3 executable programs, keygen, encryptor, and decryptor, which can all be tested by compiling the corresponding c files using the provided makefile. 
Further details regarding design and pseudocode can be found in the DESIGN.pdf file and further a description of the learning process can be found in WRITEUP.pdf.
_____________
Files:
keygen.c - main program. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -b bits       Minimum bits for mod n (Default: 256)
           -i iters      Number of iterations for primality testing (Default: 50).
           -n pubkey     Name of public key (Default: ss.pub) 
           -d privkey    Name of private key (Default: ss.priv)
           -s seed       Sets randomized seed to given int. Default: time
           -v            Verbose output. Prints all number elements of keys. Default: off
           -h          description/help
encryptor.c - main program. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -i inputfile  Name of file with contents to encrypt (Default: stdin) 
           -o outputfile Name of file to print encrypted message (Default: stdout)
           -n pubkey     Name of public key. (Default: ss.pub)
           -v            Verbose output. Prints number elements of public key. Default: off
           -h          description/help 
decryptor.c - main program. Can be opened in any C editor or compiled using clang with the provided Makefile. Accepts the following arguments:
           -i inputfile  Name of file with encrypted contents (Default: stdin) 
           -o outputfile Name of file to print dencrypted message (Default: stdout)
           -n privkey    Name of private key. (Default: ss.priv)
           -v            Verbose output. Prints number elements of public key. Default: off
           -h          description/help
ss.c - contains functions to perform encryption, and decryption of messages or files, as well as generating and writing private and public keys.
numtheory.c - contains functions utilized by ss.c that focus on the necessary mathematics, such as power mod, greatest common denominator, and mod inverse.
makefile - compiles keygen.c, encryptor.c, and decryptor.c with the additional c files. Use via "make" command. The individual programs can also be compiled using "make keygen", "make encryptor", and "make decryptor". Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to CSE13S programming spec.
Run code by entering directory and typing "make" command. This will compile all three encryption files which can be run with ./[keygen/encryptor/decryptor] [options].
DESIGN.pdf - describes design process of program
WRITEUP.pdf - contains graphs, programming process, and resources used while creating this library of files.
