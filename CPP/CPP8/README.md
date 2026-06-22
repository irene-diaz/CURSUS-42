## Vector, List y Deque (STL)

Pequeña guía sobre las diferencias entre `std::vector`, `std::list` y `std::deque`.

Los tres son contenedores de la STL: clases para almacenar múltiples elementos. La diferencia está en cómo los almacenan internamente y qué operaciones son más eficientes.

---

### 1. `std::vector`

Es el más parecido a un array dinámico.

**Declaración:**

```cpp
std::vector<int> v;
```

**Memoria continua (ejemplo):**

```
+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |
+----+----+----+----+----+
```

**Ventajas:**
- Acceso muy rápido con `operator[]`.
- Muy eficiente para recorrer elementos.
- Muy usado y bien optimizado.

**Funciones típicas:**
- `v.push_back(x)` / `v.pop_back()`
- `v.front()` / `v.back()`
- `v.size()` / `v.empty()` / `v.clear()`
- `v[i]` (acceso por índice)

**Ejemplo:**

```cpp
std::vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);
std::cout << v[1] << std::endl; // 20
```

---

### 2. `std::list`

Lista doblemente enlazada.

**Declaración:**

```cpp
std::list<int> l;
```

**Estructura interna (conceptual):**

```
NULL <- [10] <-> [20] <-> [30] -> NULL
```

**Ventajas:**
- Insertar o borrar en cualquier posición es muy rápido (O(1) si tienes el iterador).
- `push_front()` y `push_back()` eficientes.

**Desventajas:**
- No existe `operator[]` (acceso aleatorio lento).

**Funciones típicas:**
- `l.push_back(x)` / `l.push_front(x)`
- `l.pop_back()` / `l.pop_front()`
- `l.front()` / `l.back()` / `l.size()`
- `l.remove(value)`

**Ejemplo:**

```cpp
std::list<int> l;
l.push_front(10);
l.push_back(20);
l.push_back(30);
// Resultado: 10 20 30
```

---

### 3. `std::deque`

(deque = double-ended queue)

**Declaración:**

```cpp
std::deque<int> d;
```

Es una mezcla entre `vector` y `list`.

**Ventajas:**
- Acceso por índice (`operator[]`) como en `vector`.
- Inserciones rápidas por delante y por detrás.

**Funciones típicas:**
- `d.push_back(x)` / `d.push_front(x)`
- `d.pop_back()` / `d.pop_front()`
- `d.front()` / `d.back()` / `d[i]` / `d.size()`

**Ejemplo:**

```cpp
std::deque<int> d;
d.push_front(10);
d.push_back(20);
d.push_back(30);
std::cout << d[0] << std::endl; // 10
```

---

### Comparación rápida

| Operación       | vector | list | deque |
|-----------------|:------:|:----:|:-----:|
| `[]`            | ✅     | ❌   | ✅    |
| `push_back()`   | ✅     | ✅   | ✅    |
| `push_front()`  | ❌ (lento) | ✅ | ✅    |
| `pop_back()`    | ✅     | ✅   | ✅    |
| `pop_front()`   | ❌ (lento) | ✅ | ✅    |
| Memoria contigua| ✅     | ❌   | ❌    |
| Recorrido rápido| ✅     | ❌   | ✅    |

---

### Recomendación (en 42)

- `vector` — Cuando quieres un array dinámico y acceso rápido por índice.
	- Ejemplo: `std::vector<int> numbers;`
- `list` — Cuando vas a insertar/borrar frecuentemente en posiciones intermedias.
	- Ejemplo: `std::list<int> numbers;`
- `deque` — Cuando necesitas trabajar por ambos extremos (insertar/eliminar por delante y detrás) y también quieres acceso por índice.
	- Ejemplo: `std::deque<int> numbers;`

---

Si quieres, puedo añadir más ejemplos o explicar complejidad (O-notation) para cada operación.

1. ¿Qué es un std::stack?

Imagina una pila de platos.

Solo puedes:

poner uno encima → push()
quitar el de arriba → pop()
mirar el de arriba → top()

std::stack<int> s;

s.push(10);
s.push(20);
s.push(30);

std::cout << s.top(); // 30
2. ¿Qué NO puedes hacer con un stack?

No puedes recorrerlo:

for (...)     // ❌

No existe:

s.begin();    // ❌
s.end();      // ❌

porque un stack no tiene iteradores.