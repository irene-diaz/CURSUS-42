#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
    _stack = other._stack;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

void RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (isValidToken(token))
        {
            if (token == "+" || token == "-" || token == "*" || token == "/")
            {
                if (_stack.size() < 2)
                {
                    throw std::runtime_error("Error: Not enough operands for operation.");
                }

                int b = _stack.top();
                _stack.pop();
                int a = _stack.top();
                _stack.pop();

                if (token == "+")
                    _stack.push(a + b);
                else if (token == "-")
                    _stack.push(a - b);
                else if (token == "*")
                    _stack.push(a * b);
                else if (token == "/")
                {
                    if (b == 0)
                        throw std::runtime_error("Error: Division by zero.");
                    _stack.push(a / b);
                }
            }
            else
            {
                _stack.push(std::atoi(token.c_str()));
            }
        }
        else
        {
            throw std::runtime_error("Error: Invalid token '" + token + "'.");
        }
    }

    if (_stack.size() != 1)
    {
        throw std::runtime_error("Error: Invalid expression.");
    }

    std::cout << "Result: " << _stack.top() << std::endl;
}