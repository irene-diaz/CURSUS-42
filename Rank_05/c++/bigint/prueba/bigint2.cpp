#include "bigint2.hpp"

bigint::bigint() : _value("0")
{
}

bigint::bigint(unsigned int n)
{
    std::stringstream ss;
    ss << n;
    _value = ss.str();
}

bigint::bigint(const bigint &other) : _value(other._value)
{
}

void bigint::normalize()
{
    size_t non_zero_pos = _value.find_first_not_of('0');
    if (non_zero_pos == std::string::npos)
        _value = "0";
    else
        _value = _value.substr(non_zero_pos);
}

bigint &bigint::operator=(const bigint &other)
{
    if (this != &other)
        _value = other._value;
    return *this;
}

bigint bigint ::operator+(const bigint &other) const
{
    int i = _value.size() - 1;
    int j = other._value.size() - 1;

    int carry = 0;
    std::string result;

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;

        if (i >= 0)
            sum += _value[i--] - '0';
        if (j >= 0)
            sum += other._value[j--] - '0';

        result.insert(result.begin(), (sum % 10) + '0');
        carry = sum / 10;
    }

    bigint tmp;
    tmp._value = result;
    return tmp;
}

bigint &bigint ::operator+=(const bigint &other)
{
    *this = *this + other;
    return *this;
}

bigint &bigint ::operator++()
{
    *this += 1;
    return *this;
}

bigint bigint ::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return tmp;
}

bigint bigint::operator<<(const bigint &shift) const
{
    bigint result(*this);

    unsigned long n = std::strtoul(shift._value.c_str(), NULL, 10);

    result._value.append(n, '0');

    return result;
}