
all: main
main: 
	g++ -g -O2 -Wall -fmessage-length=0 -c -l./ RayTracer.cpp SupportClasses.cpp
	g++ -g -O2 -Wall -fmessage-length=0 -L./ RayTracer.o SupportClasses.o -lfreeimage libfreeimage.a -o RayTracer
