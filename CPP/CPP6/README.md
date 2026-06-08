# CPP06 - Conceptos clave

Este modulo se centra en conversiones de tipos en C++ y en RTTI (Run-Time Type Information).

## 1) Los 4 casts de C++

### `static_cast`
- Conversiones conocidas en tiempo de compilacion.
- Ejemplos: `int -> float`, `double -> int`, `Base* -> Derived*` (solo si estas seguro).
- No comprueba en runtime si el downcast es valido.

### `dynamic_cast`
- Cast seguro en jerarquias polimorficas (clase base con al menos un metodo `virtual`).
- Con punteros: devuelve `NULL` si falla.
- Con referencias: lanza excepcion si falla (normalmente `std::bad_cast`).

### `reinterpret_cast`
- Reinterpreta bits entre tipos no relacionados.
- Muy bajo nivel, usar solo cuando sea necesario.
- Caso tipico del modulo: convertir puntero <-> entero para serializacion.

### `const_cast`
- Anade o quita `const` / `volatile`.
- No cambia el objeto real; solo la "vista" del tipo.
- Peligroso si se modifica un objeto originalmente constante.

## 2) Ex00 - Scalar Converter

Objetivo: recibir un literal y mostrarlo como `char`, `int`, `float` y `double`.

Puntos importantes:
- Detectar pseudoliterales: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`.
- Comprobar rangos antes de castear (`INT_MIN`, `INT_MAX`, rango ASCII para `char`).
- Diferenciar:
	- `impossible` (no se puede representar)
	- `Non displayable` (char no imprimible)
- Usar formato fijo para salida decimal (`std::fixed`, `std::setprecision(1)`).

## 3) Ex01 - Serialization

Idea: guardar y recuperar una direccion de memoria sin perder informacion.

Conceptos clave:
- `uintptr_t` (de `<cstdint>` o `<stdint.h>`) es un entero capaz de almacenar una direccion.
- `serialize(Data*)`:
	- Convierte puntero a entero con `reinterpret_cast<uintptr_t>(ptr)`.
- `deserialize(uintptr_t)`:
	- Convierte entero a puntero con `reinterpret_cast<Data*>(raw)`.
- No hay copia profunda de datos: solo se convierte la direccion.

## 4) Ex02 - Identify real type (RTTI)

Objetivo: identificar en runtime si un `Base` es `A`, `B` o `C`.

Puntos clave:
- La clase base debe ser polimorfica (`virtual ~Base()`).
- `identify(Base*)`:
	- `dynamic_cast<A*>(p)` / `B*` / `C*` y comprobar `NULL`.
- `identify(Base&)`:
	- Puede hacerse con casts a referencia y excepciones.
	- Si el subject restringe `typeinfo`, una alternativa valida es trabajar con puntero (`&p`) y evitar `bad_cast`.

## 5) Buenas practicas del modulo

- Preferir cast explicito de C++ frente a cast estilo C.
- Validar entradas antes de convertir.
- Mantener funciones pequenas y con una sola responsabilidad.
- Evitar UB (undefined behavior) en conversiones peligrosas.
- En ejercicios de 42, seguir siempre las restricciones exactas del subject.