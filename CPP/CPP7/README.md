# CPP07 - Conceptos clave

Templates: 
Un template no es una función ni una clase concreta.

Es una receta para que el compilador genere funciones o clases para cualquier tipo que necesites.

Por eso los templates son una de las herramientas más potentes de C++, y toda la STL (vector, list, map, etc.) está construida con ellos.

Le dices al compilador:

"No sé qué tipo usaré, llámalo T, y ya me generarás la función correspondiente."

¿Por qué haces sizeof(arr)/sizeof(arr[0])?

y la respuesta es:

Porque el tamaño total del array dividido por el tamaño de un elemento me da el número de elementos del array.