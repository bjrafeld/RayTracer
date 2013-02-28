
all: main
main: 
	g++ -g -Wall -O2 -fmessage-length=0 -c -l./ RayTracer.cpp SupportClasses.cpp
	g++ -g -Wall -O2 -fmessage-length=0 -L./ -lfreeimage RayTracer.o SupportClasses.o libfreeimage.a -o RayTracer
