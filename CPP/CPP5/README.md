# Excepciones en C++98 (resumen práctico)

Este README explica de forma concisa cómo funcionan las excepciones en C++ adaptado al estándar C++98, con ejemplos y buenas prácticas útiles para los ejercicios de la carpeta `CPP5`.

## ¿Qué es una excepción?
Una excepción es un mecanismo para señalar y manejar errores o condiciones excepcionales en tiempo de ejecución. Se lanza con `throw` y se captura con `try` / `catch`.

## Sintaxis básica

```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // código que puede lanzar
        throw std::runtime_error("algo falló");
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) { // captura cualquier cosa
        std::cerr << "Error desconocido" << std::endl;
    }
}
```

- `throw expr;` lanza una excepción (expr puede ser cualquier objeto).
- `try { ... } catch(type &e) { ... }` captura la excepción; en C++98 se recomienda capturar por referencia constante (`const T&`) para evitar copias.
- `catch (...)` captura cualquier excepción no manejada por los `catch` anteriores.

## ¿Qué lanzar y cómo capturar?
- Lanza objetos; lo habitual es lanzar tipos derivados de `std::exception` (`std::runtime_error`, `std::logic_error`, etc.).
- Captura por referencia (`const T&`) para evitar copias y conservar la información de tipo.

Ejemplo de excepción personalizada (C++98):

```cpp
#include <exception>
#include <string>

class MyError : public std::exception {
    std::string _msg;
public:
    MyError(const std::string &m) : _msg(m) {}
    virtual const char* what() const throw() { return _msg.c_str(); }
};

// Uso:
// throw MyError("fallo específico");
```

> Nota: la especificación `throw()` en `what()` es la sintaxis de excepción de C++98 y debe mantenerse para compatibilidad con ese estándar (`noexcept` no existe en C++98).

## Orden de los `catch`
Los `catch` se prueban en el orden en que aparecen; el más específico debe ir antes que el genérico:

```cpp
try { /*...*/ }
catch (const std::out_of_range &e) { /* específico */ }
catch (const std::exception &e) { /* genérico */ }
```

Si colocas primero `catch (const std::exception&)`, los `catch` más específicos nunca se alcanzarán.

## Rethrow (volver a lanzar)
Dentro de un `catch` puedes volver a lanzar la misma excepción con `throw;` (sin expresión) para dejar que otro nivel la gestione:

```cpp
try {
    // ...
} catch (const std::exception &e) {
    // registrar
    throw; // re-lanza la misma excepción
}
```

## Stack unwinding y RAII
Cuando se lanza una excepción se ejecutan los destructores de todos los objetos locales construidos hasta ese punto (stack unwinding). Por eso **RAII** (recursos gestionados por objetos cuyo destructor libera el recurso) es la forma segura de gestionar memoria y recursos en presencia de excepciones.

En C++98 utiliza contenedores y clases RAII (por ejemplo, `std::vector`, `std::string`, o tus propias clases) para evitar fugas. `std::auto_ptr` existe en C++98 pero tiene problemas semánticos (transferencia de propiedad implícita); si puedes, evita `auto_ptr` y usa patrones RAII sencillos.

## Excepciones en constructores
Si un constructor lanza, el objeto no llega a crearse y su destructor no se invoca; sin embargo, los miembros ya construidos se destruyen automáticamente. Usa RAII para asegurar que los recursos se liberen correctamente si falla la construcción.

## Especificaciones de excepción (C++98)
C++98 permite especificaciones de excepción en las firmas de función, p. ej. `void f() throw();` o `void f() throw(std::exception);`. Estas especificaciones no son ampliamente usadas y tienen costes en tiempo de ejecución, por eso rara vez se recomiendan. La práctica común es no usar especificaciones excepto `throw()` (vacía) cuando necesites indicar que una función no lanza.

## Buenas prácticas (C++98)

- Lanza tipos derivados de `std::exception` cuando sea posible.
- Captura por `const T&`.
- No uses excepciones para control de flujo normal.
- Mantén una política clara sobre qué funciones pueden lanzar.
- Usa RAII para manejar recursos (contenedores STL, clases con destructores que liberen recursos).
- Evita `malloc`/`free` sin wrappers RAII.
- Evita `std::auto_ptr` salvo si no hay alternativa portable; documenta cuidadosamente su uso.

## Ejemplos rápidos (C++98 compatibles)

1) Lanzar y capturar un `std::runtime_error`:

```cpp
#include <iostream>
#include <stdexcept>

void f() {
    throw std::runtime_error("error en f");
}

int main() {
    try {
        f();
    } catch (const std::exception &e) {
        std::cerr << "capturado: " << e.what() << '\n';
    }
    return 0;
}
```

2) Excepción personalizada y rethrow:

```cpp
#include <iostream>

class MyError : public std::exception {
    std::string _msg;
public:
    MyError(const std::string &m) : _msg(m) {}
    virtual const char* what() const throw() { return _msg.c_str(); }
};

void g() {
    try {
        throw MyError("algo falló");
    } catch (const MyError &e) {
        // registrar
        throw; // re-lanza
    }
}

int main() {
    try { g(); } catch (const std::exception &e) { std::cout << e.what() << std::endl; }
    return 0;
}
```

## Recursos y referencias
- `std::exception`, `std::runtime_error`, `std::logic_error` (biblioteca estándar C++98)
- RAII: usar contenedores STL y clases con destructores para liberar recursos
- Evita confiar en características de C++11+ (no `noexcept`, no move semantics)

---

Si quieres, puedo añadir una carpeta `CPP5/examples` con pequeños programas compilables con `-std=c++98` y Makefile de ejemplo. Dime si lo quieres y creo 2-3 ejemplos listos para compilar y ejecutar.
