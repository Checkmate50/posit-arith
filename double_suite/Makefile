%: %.cpp ../src/posit*.cpp ../src/frac.cpp ../src/util*.cpp
	g++ -std=c++17 $^ -o $*.exe -Wall -Wextra
	.\$*.exe

all:
	@for f in $(shell ls *.cpp); do make $${f%.cpp}; done

clean:
	rm -f *.exe*
	rm -rf ../test_suite