#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Posit p1(4, 6, 2); // 1/256 + 1/256 = 1/128
    Posit p2(4, 6, 2);
    Posit t(5, 6, 2);
    Posit res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(16, 6, 2); // 1 + 2 = 3
    p2 = Posit(18, 6, 2);
    t  = Posit(19, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(11, 6, 2); // 3/16 + 1/4 = 3/8 <-- note the round down
    p2 = Posit(12, 6, 2);
    t  = Posit(13, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(14, 6, 2); // 1/2 + 1 = 3/2
    p2 = Posit(16, 6, 2);
    t  = Posit(17, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(48, 6, 2); // -1 + -1 = -2
    p2 = Posit(48, 6, 2);
    t  = Posit(46, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(42, 6, 2); // -8 + -6 = -12 <-- note the round down
    p2 = Posit(43, 6, 2);
    t  = Posit(41, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(62, 6, 2); // -1/4096 + -1/1024 = -1/1024 <-- note the round down
    p2 = Posit(61, 6, 2);
    t  = Posit(61, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(1, 6, 2); // 1/65536 + 0 = 1/65536
    p2 = Posit(0, 6, 2);
    t  = Posit(1, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(15, 6, 2); // 3/4 + 3/4 = 3/2
    p2 = Posit(15, 6, 2);
    t  = Posit(17, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(31, 6, 2); // 65536 + 65536 = inf
    p2 = Posit(31, 6, 2); 
    t  = Posit(32, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(19, 6, 2); // 3 + -2 = 1
    p2 = Posit(46, 6, 2); 
    t  = Posit(16, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(0, 6, 2); // 0 + -65536 = -65536
    p2 = Posit(33, 6, 2); 
    t  = Posit(33, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(16, 6, 2); // 1 + -1/2 = 1/2
    p2 = Posit(50, 6, 2);
    t  = Posit(14, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(48, 6, 2); // -1 + 1/2 = -1/2
    p2 = Posit(14, 6, 2);
    t  = Posit(50, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(40, 6, 2); // -16 + 1/8 = -16
    p2 = Posit(10, 6, 2);
    t  = Posit(40, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(10, 6, 2); // 1/8 + -1/16 = 1/8
    p2 = Posit(56, 6, 2);
    t  = Posit(8, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(10, 6, 2); // 1/8 + -1/024 = 1/8
    p2 = Posit(61, 6, 2);
    t  = Posit(10, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(5, 6, 2); // ... + inf = inf
    p2 = Posit(32, 6, 2);
    t  = Posit(32, 6, 2);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(0b01000000, 8, 1); // 1 + -1 1/16 = -1/16
    p2 = Posit(0b10111111, 8, 1);
    t  = Posit(0b11110000, 8, 1);
    res = p1 + p2;
    std::cout << (res == t) << ' ' << res.to_string() << std::endl;

    p1 = Posit(0b01110111, 16, 1);
    p2 = Posit(0b00111100, 16, 1);
    t  = Posit(0b10000101, 16, 1);
    //res = p1 + p2;
    // std::cout << (res == t) << ' ' << res.to_string() << std::endl;
}