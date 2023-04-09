CFLAGS=-g -O0 -I include -I ../Resources/C/Unity/

all: build/library_es1.o bin/test_es1 bin/app_es1

clean: 
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/library_es1.o: src/library_es1.c include/header_es1.h
	$(CC) $(CFLAGS) -c src/library_es1.c -o build/library_es1.o

bin/app_es1: include/header_es1.h build/library_es1.o app/app_es1.c
	$(CC) $(CFLAGS) -o bin/app_es1 build/library_es1.o app/app_es1.c

bin/test_es1: test/test_es1.c build/library_es1.o include/header_es1.h    
	$(CC) $(CFLAGS) test/test_es1.c build/library_es1.o ../Resources/C/Unity/unity.c -o bin/test_es1
