#/bin/bash
cd static
gcc -c -o add.o add.c
ar crs libmyadd.a add.o
cd ..
gcc main.c -L./static -lmyadd -I ./include


