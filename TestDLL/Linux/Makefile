UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
TARGET = -ldl
else
TARGET = 
endif

default: TestDll myclass.so

TestDll: class_user.o testStatic.o
	g++ -o TestDll class_user.o testStatic.o $(TARGET)

class_user.o: class_user.cpp testStatic.hpp
	g++ -Wall -c class_user.cpp -export-dynamic

testStatic.o: testStatic.cpp testStatic.hpp
	g++ -Wall -c testStatic.cpp -export-dynamic

myclass.so:
	g++ -fPIC -shared myclass.cpp allEngineFonction.cpp -o myclass.so -export-dynamic


run:
	./TestDll

clean: cleanCUo myClassSo testStaticO exe

cleanCUo : 
	rm class_user.o

myClassSo : 
	rm myclass.so

testStaticO : 
	rm testStatic.o

exe:
	rm TestDll