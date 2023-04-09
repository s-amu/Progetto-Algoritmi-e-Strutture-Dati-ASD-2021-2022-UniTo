CFLAGS=-g -O0 -I include -I ../Resources/C/Unity/

all: build/library_es2.o bin/test_es2 bin/app_es2 

clean: 
	$(RM) -rf bin/*
	$(RM) -rf build/*
	
tests: bin/test_es2

build/library_es2.o: src/library_es2.c include/header_es2.h
	$(CC) $(CFLAGS) -c src/library_es2.c -o build/library_es2.o

bin/app_es2: include/header_es2.h build/library_es2.o app/app_es2.c
	$(CC) $(CFLAGS) -o bin/app_es2 build/library_es2.o app/app_es2.c

bin/test_es2: test/test_es2.c build/library_es2.o include/header_es2.h    
	$(CC) $(CFLAGS) test/test_es2.c build/library_es2.o ../Resources/C/Unity/unity.c -o bin/test_es2
