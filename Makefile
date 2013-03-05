
all: main
main: 
	g++ -g -Wall -fmessage-length=0 -c -l./ RayTracer.cpp SupportClasses.cpp Shading.cpp Parser.cpp
	g++ -g -Wall -fmessage-length=0 -L./ RayTracer.o SupportClasses.o Shading.o Parser.o -lfreeimage libfreeimage.a -o RayTracer
