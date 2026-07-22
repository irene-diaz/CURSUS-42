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

bool RPN::isValidToken(const std::string &token) const
{
    // Valid operators
    if (token == "+" || token == "-" || token == "*" || token == "/")
        return true;

    // Valid numbers (0 - 9)
    if (token.length() == 1 && std::isdigit(token[0]))
        return true;

    return false;
}

void RPN::evaluate(const std::string &expression)
{
    // Clear the stack in case evaluate() is called more than once
    while (!_stack.empty())
        _stack.pop();

    // Use a stringstream to parse the expression into tokens
    std::stringstream ss(expression);
    // Token to hold each parsed token
    std::string token;

    // Process each token in the expression
    while (ss >> token)
    {
        // Check if the token is valid
        if (!isValidToken(token))
            throw std::runtime_error("Error");

        // Number
        if (std::isdigit(token[0]))
        {
            _stack.push(std::atoi(token.c_str()));
        }
        // Operator
        else
        {
            // Ensure there are at least two numbers on the stack for the operation
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            // Pop the top two numbers from the stack
            int b = _stack.top();
            _stack.pop();

            int a = _stack.top();
            _stack.pop();

            // Perform the operation based on the operator and push the result back onto the stack
            if (token == "+")
                _stack.push(a + b);
            else if (token == "-")
                _stack.push(a - b);
            else if (token == "*")
                _stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Error");

                _stack.push(a / b);
            }
        }
    }

    // After processing all tokens, there should be exactly one number left on the stack
    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << std::endl;
}
