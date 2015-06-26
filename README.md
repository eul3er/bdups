# bdups

contact: eu3ler@achernar.uberspace.de
License: GPLv2

bdupes:
Fast Duplicates finding programm using parallism

NOTE: This is a early beta. Tested on FreeBSD, Linux and Windows

Buildsystem: CMAKE

Dependencies: Boost 1.55 Cryptopp

Compiler: GCC 4.9 or Clang 3.4 or MingW4.9



Build Guide:

cmake $folder //in the Folder of CMakeLists.txt file

make -jX      //X = number of cores to utilize


Options:

I With two arguments (core count, path):
Look at the given path and execute the basic algorithm

II With three arguments (core count, path1, path2)
Look at path1 for the given files in path2 and execute basic algorithm

