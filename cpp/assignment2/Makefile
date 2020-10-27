target=a.out

all:$(target) input run
	@echo "\033[0;31m使用 make a.out 来仅调用编译\033[0m"

$(target):Main.o Library.o
	g++ -o $@ $^

%.o:%.cpp
	g++ -c -o $@ $< -std=c++17 -Wall -O0

input:
	@echo '3' >input
	@echo 'N123;Object-Oriented Programming;Dave Smith;2009;3' >>input
	@echo 'A251;UML Modelling and Design;Barry Arthur;2005;1' >>input
	@echo 'Z001;Practical Guide to STL;John Johnson;2000;5' >>input
	@echo '3' >>input
	@echo '12345;Joe Bloggs;3;N123;A251;Z001' >>input
	@echo '20498;Ales Alexis;1;Z001' >>input
	@echo '19090;Mike Mike;2;N123;Z001' >>input

run:input $(target)
	./$(target) <input

clean:
	rm Main.o Library.o
	rm $(target)
	rm input