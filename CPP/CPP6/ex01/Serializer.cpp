#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::Serializer(const Serializer &) {}

Serializer &Serializer::operator=(const Serializer &)
{
    return *this;
}

Serializer::~Serializer() {}

/*this function takes a pointer to a Data structure and converts it into an integer
representation (uintptr_t). The reinterpret_cast operator is used to perform this
conversion, allowing us to treat the pointer as an integer value. This is essential
for serialization, as it allows us to represent the pointer in a format that can be
easily stored or transmitted.*/
uintptr_t Serializer::serialize(Data *ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

/*this function takes an integer (uintptr_t) that represents a pointer and converts
it back to a pointer of type Data*. The reinterpret_cast operator is used to perform
this conversion, allowing us to retrieve the original pointer value from the integer
representation. This is essential for deserialization, as it allows us to reconstruct
the original pointer from its serialized form.*/
Data *Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data *>(raw);
}