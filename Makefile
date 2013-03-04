
all: main
main: 
	g++ -g -Wall -fmessage-length=0 -c -l./ RayTracer.cpp SupportClasses.cpp
	g++ -g -Wall -fmessage-length=0 -L./ RayTracer.o SupportClasses.o -lfreeimage libfreeimage.a -o RayTracer
