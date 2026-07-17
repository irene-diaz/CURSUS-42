#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>

class RPN
{
private:
    std::stack<int> _stack;
    bool isValidToken(const std::string &token) const;

public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
    void evaluate(const std::string &expression);
};

#endif