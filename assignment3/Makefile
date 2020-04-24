TARGET = a.out
SOURCE = $(wildcard *.cpp)
OBJECT = $(patsubst %.cpp,%.o, ${SOURCE})

$(TARGET):$(OBJECT)
	g++ -o $@ $^

%.o:%.cpp
	g++ -c -o $@ $< -std=c++17 -Wall -O0

clean:
	rm $(TARGET)
	rm $(OBJECT)