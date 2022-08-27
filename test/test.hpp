#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>

class Test{
private:
    unsigned int success_count;
    unsigned int total_test;

public:
    Test(const char *p_title)
    : success_count(0), total_test(0)
    { std::cout << p_title << "\n----------" << std::endl; }

    Test& operator()(const char *p_desc, bool is_success){
        total_test++;
        if(is_success){
            success_count++;
            std::cout << "[*] ";
        } else std::cout << "[ ] ";
        std::cout << p_desc << std::endl;
        return *this;
    }

    ~Test(){ std::cout << 
            "Test result: " << 
            success_count << " succeed, " << 
            total_test - success_count << " failed." << std::endl;}
};

#endif //_TEST_H_
