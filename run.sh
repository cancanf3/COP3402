make clean
make
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes  ./pcc -lav