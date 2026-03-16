# CPP0 - Introducción a C++

Este proyecto tiene como objetivo introducir los conceptos básicos de C++ para aquellos que vienen de un trasfondo en C. Aquí aprenderás las diferencias clave entre ambos lenguajes y cómo aprovechar las características de C++.

## Conceptos básicos de C++

1. **Entrada y salida estándar**:
   - En C usamos `printf` y `scanf`.
   - En C++ usamos `std::cout` y `std::cin`.
     ```cpp
     #include <iostream>

     int main() {
         std::cout << "Introduce tu nombre: ";
         std::string nombre;
         std::cin >> nombre;
         std::cout << "Hola, " << nombre << "!" << std::endl;
         return 0;
     }
     ```

2. **Clases y objetos**:
   - C++ es un lenguaje orientado a objetos.
     ```cpp
     #include <iostream>
     #include <string>

     class Persona {
     public:
         std::string nombre;
         int edad;

         Persona(std::string n, int e) : nombre(n), edad(e) {}

         void saludar() {
             std::cout << "Hola, soy " << nombre << " y tengo " << edad << " años." << std::endl;
         }
     };

     int main() {
         Persona p("Irene", 25);
         p.saludar();
         return 0;
     }
     ```

3. **Constructores y destructores**:
   - C++ permite inicializar objetos con constructores y liberar recursos con destructores.
     ```cpp
     #include <iostream>

     class Recurso {
     public:
         Recurso() {
             std::cout << "Recurso creado." << std::endl;
         }

         ~Recurso() {
             std::cout << "Recurso destruido." << std::endl;
         }
     };

     int main() {
         {
             Recurso r;
         } // Destructor llamado automáticamente aquí
         return 0;
     }
     ```

4. **Sobrecarga de funciones**:
   - Puedes definir múltiples funciones con el mismo nombre pero diferentes parámetros.
     ```cpp
     #include <iostream>

     void imprimir(int x) {
         std::cout << "Número entero: " << x << std::endl;
     }

     void imprimir(double x) {
         std::cout << "Número decimal: " << x << std::endl;
     }

     void imprimir(std::string x) {
         std::cout << "Texto: " << x << std::endl;
     }

     int main() {
         imprimir(42);
         imprimir(3.14);
         imprimir("Hola, mundo!");
         return 0;
     }
     ```

5. **Manejo de memoria**:
   - En C usamos `malloc` y `free`.
   - En C++ usamos `new` y `delete`.
     ```cpp
     #include <iostream>

     int main() {
         int* ptr = new int(10);
         std::cout << "Valor: " << *ptr << std::endl;
         delete ptr;
         return 0;
     }
     ```

6. **Vectores (std::vector)**:
   - Usa `std::vector` en lugar de arreglos dinámicos.
     ```cpp
     #include <iostream>
     #include <vector>

     int main() {
         std::vector<int> numeros = {1, 2, 3, 4, 5};
         numeros.push_back(6);

         for (size_t i = 0; i < numeros.size(); ++i) {
             std::cout << numeros[i] << " ";
         }
         std::cout << std::endl;
         return 0;
     }
     ```

## Estructura del proyecto

- **ex00/**: Ejercicios básicos para practicar los conceptos iniciales de C++.

## Recomendaciones

- Usa `std::string` en lugar de `char*` para manejar cadenas de texto.
- Aprovecha las bibliotecas estándar de C++ como `<vector>`, `<map>`, y `<algorithm>`.
- Practica el uso de clases y objetos para entender la programación orientada a objetos.

**Nota:** No se permite el uso de `namespace`. Por lo tanto, siempre utiliza el prefijo `std::` para las funciones y clases de la biblioteca estándar.

¡Buena suerte en tu aprendizaje de C++!
