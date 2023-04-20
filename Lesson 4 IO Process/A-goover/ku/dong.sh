cd ./dong
gcc -fPIC -c add.c -o add.o
gcc -shared -o libmyadd.so add.o
cd ..
gcc main.c -L lmyadd -I ./include/

