
CC=g++

read_expdb: Mmap.cc read_expdb.cc
	$(CC) -o $@ Mmap.cc read_expdb.cc
