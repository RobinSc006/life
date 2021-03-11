g++ -c main.cpp
g++ -Wl,-z,stack-size=8194304 main.o -o life -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio