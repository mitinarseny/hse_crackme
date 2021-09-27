CC = clang++

crackme: main.cpp
	$(CC) -static -o $@ $<
