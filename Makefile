
all: main
main: 
	g++ -g -Wall -fmessage-length=0 -c SupportClasses.cpp Shading.cpp Parser.cpp RayTracer.cpp main.cpp
	g++ -g -Wall -fmessage-length=0 -L./ SupportClasses.o Shading.o Parser.o RayTracer.o main.o -lfreeimage libfreeimage.a -o RayTracer
