CPP_FILES := $(wildcard *.cpp)
O_FILES := $(subst .cpp,.o,$(CPP_FILES))
COMPILED_FLAGS := -pedantic -W -Wall
LINKED_FLAGS := -s

INCLUDE_DIRECTORIES := -ISFML-2.6.1\include -Iheaders

LIB_DIRECTORIES := -L\SFML-2.6.1\lib

LIB_FILES :=  -lopenal32 -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

app: $(O_FILES)
	g++ $^ -o $@ $(LIB_DIRECTORIES) $(LIB_FILES) $(LINKED_FLAGS)

%.o: %.cpp
	g++ -c $^ -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)

clean: 
	del *.o *.exe /s
