# CPP Module 01 - Conceptos importantes

Este resumen recoge los conceptos clave trabajados en ex00 a ex06 de CPP1.

## Vision global del modulo

- Diferencia entre stack y heap.
- Gestion manual de memoria con new, delete y delete[].
- Construccion y destruccion de objetos (lifecycle).
- Uso de referencias y punteros segun el tipo de relacion entre objetos.
- Trabajo con std::string y manejo de texto.
- Entrada y salida con streams de C++ (ifstream, ofstream, cout).
- Punteros a funciones miembro para despachar comportamiento.
- Seleccion de flujo con switch y fallthrough.
- Compatibilidad con C++98 y flags estrictas: -Wall -Wextra -Werror.

## ex00 - BraiiiiiiinnnzzzZ

- Crear objetos dinamicos con new y liberarlos con delete.
- Crear objetos automaticos en stack y observar destruccion al salir de scope.
- Separar responsabilidades con funciones helper:
  - newZombie: reserva en heap y devuelve puntero.
  - randomChump: crea en stack y ejecuta accion inmediata.
- Entender cuando una funcion debe devolver puntero y cuando no.

## ex01 - Moar brainz

- Reservar arreglos de objetos con new[].
- Liberar correctamente con delete[].
- Necesidad de constructor por defecto al crear arrays de objetos.
- Inicializacion posterior de cada elemento mediante setter.
- Patron de fabrica para crear una horda de objetos.

## ex02 - HI THIS IS BRAIN

- Diferencia practica entre:
  - puntero a std::string.
  - referencia a std::string.
- Mostrar direcciones y valores para entender aliasing.
- Regla mental:
  - referencia: alias obligatorio y no nulo.
  - puntero: puede ser nulo y reasignable.

## ex03 - Unnecessary violence

- Modelado de relaciones entre clases:
  - HumanA mantiene una referencia a Weapon (debe existir desde construccion).
  - HumanB mantiene un puntero a Weapon (puede no tener arma al inicio).
- Encapsulacion con getter por referencia constante:
  - evitar copias y proteger modificacion externa.
- Cambio de estado compartido en Weapon y su impacto en varias clases.
- Elegir referencia o puntero segun si la dependencia es obligatoria u opcional.

## ex04 - Sed is for losers

- Apertura de archivos con ifstream y ofstream.
- Validacion de argumentos y errores de apertura.
- Reemplazo de substrings con find, erase e insert.
- Control del indice de busqueda para evitar bucles infinitos tras reemplazar.
- Manejo de fin de archivo para no introducir saltos de linea extra.
- Detalle C++98: para nombres de archivo en ofstream usar c_str() cuando se parte de std::string.

### Lo importante en tu implementacion de ex04

- Ya validas argc == 4, apertura de archivo de entrada y salida.
- Ya corregiste el punto clave de C++98: (std::string(argv[1]) + ".replace").c_str().
- El bucle de reemplazo esta bien planteado:
  - line.find(s1, pos)
  - line.erase(pos, s1.length())
  - line.insert(pos, s2)
  - pos += s2.length()
- Evitas salto de linea extra al final con if (!infile.eof()).
- Punto fino: en este ejercicio, normalmente se permite que s2 sea vacio para "eliminar" ocurrencias de s1.

## ex05 - Harl 2.0

- Despacho de metodos usando arreglo de punteros a funciones miembro.
- Mapear strings de entrada a acciones concretas.
- Evitar cadenas de if largas con una tabla nivel -> metodo.
- Caso por defecto para entradas no validas.

### Lo importante en tu implementacion de ex05

- Implementacion correcta de tabla doble:
  - levels[] con strings.
  - functions[] con void (Harl::*)(void).
- Recorres de 0 a 3 y llamas el metodo cuando hay match:
  - (this->*functions[i])();
- Tienes mensaje por defecto cuando el nivel no existe.
- Este ejercicio evalua sobre todo saber despachar metodos sin if-else gigante.

## ex06 - Harl filter

- Reutilizar el sistema de niveles de log del ejercicio anterior.
- Localizar nivel solicitado y usar switch por indice.
- Uso intencional de fallthrough para imprimir desde un nivel hacia los mas graves.
- Patron util para filtros por severidad (DEBUG < INFO < WARNING < ERROR).

### Lo importante en tu implementacion de ex06

- Buscas el indice del nivel con while (i < 4 && levels[i] != level).
- Usas switch(i) con fallthrough intencional de case 0 a case 3.
- El comportamiento es el esperado para filtro por severidad:
  - DEBUG imprime DEBUG, INFO, WARNING, ERROR.
  - INFO imprime INFO, WARNING, ERROR.
  - WARNING imprime WARNING, ERROR.
  - ERROR imprime ERROR.
- Tienes default para niveles invalidos.

## Errores frecuentes en CPP1

- Olvidar delete o delete[] y provocar fugas.
- Usar delete en memoria reservada con new[].
- Devolver referencias o punteros a variables locales.
- Elegir puntero cuando en realidad la relacion deberia ser referencia (o al reves).
- No validar que el string buscado en reemplazo no sea vacio.
- En C++98, pasar std::string directo a ofstream sin convertir a c_str().

## Checklist rapido antes de entregar

- Compila con -Wall -Wextra -Werror -std=c++98.
- No hay leaks en rutas principales.
- Se usa delete o delete[] segun corresponda.
- Los casos invalidos muestran mensaje y retornan error.
- El comportamiento coincide con lo pedido en cada enunciado.
