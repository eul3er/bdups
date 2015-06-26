# bdups

contact: eu3ler@achernar.uberspace.de

License: GPLv2

bdupes:
Fast Duplicates finding programm using parallism

NOTE: This is a early beta. Tested on FreeBSD, Linux and Windows

Dependencies
-------------
* Boost 1.55 
* Cryptopp

Compiler
--------
* GCC 4.9 
* Clang 3.4 
* MingW4.9



Build Guide
-----------
execute
```
cmake $folder // $folder is the path to the Folder where CMakeLists.txt resides
```
then run
```
make -jX      //X is number of cores to utilize for building
```


Options
--------

1. With two arguments (core count, path):
Look at the given path and execute the basic algorithm

Example: 
```
./bdupes 12 /home/myUsername/stuff > /home/myUsername/out.file
```

2. With three arguments (core count, path1, path2)
Look at path1 for the given files in path2 and execute basic algorithm

Example: 
```
./bdupes 0 /home/myUsername/myStuff /home/myUsername/LookForDupsOfThoseFiles > /home/myUsername/out.file
```
=> using a zero for core count will result in logical core count.
