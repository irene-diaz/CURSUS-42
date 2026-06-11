#include "bigint.hpp"

// constrctor por defecto
bigint::bigint() : _value("0")
{
}

// constructor a partir de un entero sin signo
bigint::bigint(unsigned int n)
{
    // creamos un stringstream que va a guardar el número como una cadena de dígitos
    std::stringstream ss;
    // insertamos el número en el stringstream, lo que lo convierte a una cadena de dígitos
    ss << n;
    // asignamos el valor del stringstream a la representación interna del número
    _value = ss.str();
}

// constructor de copia
bigint::bigint(const bigint &other) : _value(other._value)
{
}

// operador de asignación
bigint &bigint::operator=(const bigint &other)
{
    if (this != &other)
        _value = other._value;
    return *this;
}

// función para eliminar ceros a la izquierda y mantener la representación canónica
void bigint::normalize()
{
    // Busca el primer carácter que NO sea '0'
    size_t non_zero_pos = _value.find_first_not_of('0');

    // si son todos ceros, entonces el número es 0
    if (non_zero_pos == std::string::npos)
        _value = "0";
    // sino son todos ceros, entonces eliminamos los ceros a la izquierda
    else
        _value = _value.substr(non_zero_pos);
}

// operador de suma
bigint bigint::operator+(const bigint &other) const
{
    // guardamos las posiciones finales de las cadenas de dígitos de ambos números
    int i = _value.size() - 1;
    int j = other._value.size() - 1;

    // variable para llevar el acarreo(cuantas te llevas) de la suma
    int carry = 0;
    // resultado de la suma, que se construirá de derecha a izquierda
    std::string result;

    // mientras haya dígitos por sumar en cualquiera de los números o haya un acarreo pendiente
    while (i >= 0 || j >= 0 || carry)
    {
        // sumamos los dígitos correspondientes de ambos números y el acarreo
        int sum = carry;

        // si aún hay dígitos en el primer número, los sumamos y avanzamos a la izquierda
        if (i >= 0)
            sum += _value[i--] - '0';

        // si aún hay dígitos en el segundo número, los sumamos y avanzamos a la izquierda
        if (j >= 0)
            sum += other._value[j--] - '0';

        // el dígito resultante de la suma es el residuo de dividir la suma entre 10
        result.insert(result.begin(), (sum % 10) + '0');

        // el nuevo acarreo es el cociente de dividir la suma entre 10
        carry = sum / 10;
    }

    // construimos un nuevo bigint con el resultado de la suma y lo devolvemos
    bigint tmp;
    tmp._value = result;
    return tmp;
}

// operador de suma y asignación
bigint &bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return *this;
}

// operador de pre-incremento
bigint &bigint::operator++()
{
    *this += 1;
    return *this;
}

// operador de post-incremento
bigint bigint::operator++(int)
{
    bigint temp(*this);
    ++(*this);
    return temp;
}

// operador de desplazamiento a la izquierda(añadir ceros)
bigint bigint::operator<<(const bigint &shift) const
{
    // creamos un nuevo bigint con el mismo valor que el actual
    bigint result(*this);

    // convertimos el valor del desplazamiento a un número entero sin signo para saber cuántos ceros añadir
    // std::strtoul convierte una cadena de caracteres a un número entero sin signo, tomando como base el número 10
    unsigned long n =
        std::strtoul(shift._value.c_str(), NULL, 10);

    //añade tantos 0 al final del número como indique n(el desplazamiento)
    result._value.append(n, '0');

    return result;
}

// operador de desplazamiento a la derecha
bigint bigint::operator>>(const bigint &shift) const
{
    bigint result(*this);

    unsigned long n =
        std::strtoul(shift._value.c_str(), NULL, 10);

    if (n >= result._value.size())
    {
        result._value = "0";
        return result;
    }

    result._value.erase(result._value.size() - n);

    result.normalize();
    return result;
}

// operador de desplazamiento a la izquierda y asignación
bigint &bigint::operator<<=(const bigint &shift)
{
    *this = *this << shift;
    return *this;
}

// operador de desplazamiento a la derecha y asignación
bigint &bigint::operator>>=(const bigint &shift)
{
    *this = *this >> shift;
    return *this;
}

// operador de comparación menor que
bool bigint::operator<(const bigint &other) const
{
    if (_value.size() != other._value.size())
        return _value.size() < other._value.size();

    return _value < other._value;
}

// operador de comparación menor o igual que
bool bigint::operator<=(const bigint &other) const
{
    return *this < other || *this == other;
}

// operador de comparación mayor que
bool bigint::operator>(const bigint &other) const
{
    return other < *this;
}

// operador de comparación mayor o igual que
bool bigint::operator>=(const bigint &other) const
{
    return !(*this < other);
}

// operador de comparación de igualdad
bool bigint::operator==(const bigint &other) const
{
    return _value == other._value;
}

// operador de comparación de desigualdad
bool bigint::operator!=(const bigint &other) const
{
    return !(*this == other);
}

// operador de inserción para imprimir el número
std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    os << n._value;
    return os;
}