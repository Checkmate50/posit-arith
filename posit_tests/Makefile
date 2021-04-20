%: %.cpp ../src/posit.cpp ../src/frac.cpp
	g++ -std=c++17 $^ -o $*.exe -Wall -Wextra
	.\$*.exe

clean:
	rm *.exe*