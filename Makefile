majs : main.o stringology.o
	c++ -o majs main.o stringology.o -L./lib -lboost_fs
main.o : main.cc
	c++ -c main.cc
stringology.o : stringology.cc
	c++ -c stringology.cc
