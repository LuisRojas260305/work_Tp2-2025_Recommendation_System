# Quantum Store - Sistema de Recomendación de Comercio Electrónico.

## Descripcion del Proyecto

Quantum Store es un sistema de comercio electrónico avanzado que implementa un motor de recomendaciones personalizadas basado en el comportamiento del usuario. El sistema permite:

1. Registro e inicio de sesión de usuarios
2. Exploración de productos por categorías
3. Gestión de carrito de compras y lista de deseos
4. Seguimiento de historial de productos visualizados
5. Generación de recomendaciones personalizadas basadas en:
    - Preferencias explícitas del usuario
    - Historial de visualización
    - Marcas y categorías frecuentes
    - Calidad de productos preferidos
    
El sistema utiliza estructuras de datos personalizadas como listas enlazadas, árboles binarios de búsqueda, sets y mapas para gestionar eficientemente los datos.

## Diagrama de Funciones y Relaciones


``` mermaid
  graph TD
    A[main.cpp] -->|inicializa| B[catalogo.cpp]
    A -->|ejecuta| C[interfaz.cpp]
    
    C -->|llama| D[usuario.cpp]
    D -->|registra| E[utilidades.cpp]
    D -->|gestiona| F[estructuras.h]
    
    C -->|genera| G[recomendacion.cpp]
    G -->|utiliza| H[catalogo.cpp]
    G -->|analiza| I[usuario.cpp]
    
    B -->|provee datos| J[interfaz.cpp]
    J -->|muestra| K[Productos]
    J -->|gestiona| L[Carrito]
    J -->|gestiona| M[Lista Deseos]
    J -->|muestra| N[Recomendaciones]
    
    G -->|actualiza| O[Preferencias Usuario]
```

## Modulos principales.

<details>
<summary>1. main.cpp - Punto de entrada del programa.</summary>

- `main():` Inicializa el catálogo y ejecuta el menú principal.
  
</details>

<details>
<summary>2. interfaz.cpp - Gestión de la interfaz de usuario.</summary>
    
- `Mainmenu()`: Menú principal (registro/inicio sesión).
- `mostrarMenuUsuario()`: Menú post-login con todas las opciones.
- `verDetallesProducto()`: Muestra detalles de producto y actualiza historial.
- `verCarrito()`, `verListaDeseos()`, `verHistorial()`: Gestión de componentes.
  
</details>

<details>
<summary>3. usuario.cpp - Gestión de usuarios</summary>
    
- `ComandoRegistrarUsuario()`: Proceso de registro
- `ComandoIngresarUsuario()`: Proceso de inicio de sesión
- `seleccionarPreferencias()`: Selección de marcas/categorías preferidas

</details>

<details>
<summary>4. catalogo.cpp - Gestión de productos</summary>
    
- `inicializarCatalogo()`: Carga productos iniciales
- Funciones de búsqueda (`buscarPorCategoria`, `buscarPorMarca`, etc.)
- `obtenerCategoriasUnicas()`, `obtenerMarcasUnicas()`: Listados para UI

</details>

<details>
<summary>5. recomendacion.cpp - Motor de recomendaciones</summary>

- `generarRecomendaciones()`: Genera todas las recomendaciones
- `obtenerEstadisticasUsuario()`: Analiza comportamiento del usuario
- `actualizarPreferenciasDinamicas()`: Ajusta preferencias basadas en historial
- `obtenerTopN()`: Selecciona elementos más frecuentes

</details>

<details>
<summary>6. utilidades.cpp - Funciones auxiliares</summary>
    
- Generación de IDs, manipulación de strings
- Funciones de listas, sets y mapas
- Utilidades de UI (`clearScreen`, `pausarConsola`, etc.)

</details>


## Flujo principal del programa.

``` mermaid
  sequenceDiagram
    participant Usuario
    participant Mainmenu
    participant ComandoRegistrarUsuario
    participant ComandoIngresarUsuario
    participant mostrarMenuUsuario
    participant generarRecomendaciones
    
    Usuario->>Mainmenu: Accede al sistema
    alt Registro nuevo
        Mainmenu->>ComandoRegistrarUsuario: Registrar usuario
        ComandoRegistrarUsuario->>seleccionarPreferencias: Preferencias iniciales
    else Inicio sesión
        Mainmenu->>ComandoIngresarUsuario: Validar credenciales
    end
    
    ComandoIngresarUsuario-->>mostrarMenuUsuario: Usuario válido
    loop Interacción usuario
        mostrarMenuUsuario->>generarRecomendaciones: Solicita recomendaciones
        generarRecomendaciones->>obtenerEstadisticasUsuario: Analiza comportamiento
        generarRecomendaciones->>actualizarPreferenciasDinamicas: Actualiza preferencias
        generarRecomendaciones-->>mostrarMenuUsuario: Devuelve recomendaciones
        mostrarMenuUsuario->>Usuario: Muestra opciones
    end
```

## Funcionamiento del sistema de recomendacion.

<details>
<summary>1. Análisis del comoportamiento del usuario</summary>

``` mermaid
  graph LR
    A[Historial Usuario] --> B[Conteo Categorías]
    A --> C[Conteo Marcas]
    A --> D[Conteo Calidades]
    B --> E[Top 2 Categorías]
    C --> F[Top 2 Marcas]
    D --> G[Calidad Más Frecuente]
```

</details>

<details>
<summary>2. Actualización Dinámica de Preferencias</summary>
    
- Ajusta preferencias según productos visualizados
- Actualiza marcas y categorías preferidas

</details>

<details>
<summary>3. Generación de Candidatos</summary>

- Productos de marcas preferidas
- Productos de categorías preferidas
- Productos de calidad similar
- Productos de marcas frecuentes no preferidas

</details>

<details>
<summary>4. Filtrado y Presentación</summary>
    
- Excluye productos ya vistos/compras anteriores
- Mezcla aleatoria de resultados
- Presentación categorizada en la interfaz

</details>


## Listado completo de estructuras de datos.

<details>
<summary>Producto (estructuras.h)</summary>

- *Descripción*: Almacena información fundamental sobre los productos disponibles en la tienda.

    |Atributo  	    |Tipo	        |Descripción                      |
    |---------------|-------------|---------------------------------|
    |`descripcion`	|std::string	|Nombre/descripción del producto  |
    |`id`	          |int	        |Identificador único del producto |
    |`marca`	      |std::string	|Marca o fabricante del producto  |
    |`precio`	      |double	      |Precio del producto en dólares   |
    |`calidad`	    |int	        |Nivel de calidad (1-5 estrellas) |
    |`categoria`	  |std::string	|Categoría principal del producto |

</details>

<details>
<summary>NodoProducto (estructuras.h)</summary>

- *Descripción*: Nodo para lista enlazada de productos. Forma la base del catálogo global.

    |Atributo	    |Tipo	          |Descripción
    |-------------|---------------|--------------------------------------|
    |`dato`	      |Producto	      |Producto almacenado en el nodo        |
    |`siguiente`	|NodoProducto*	|Puntero al siguiente nodo en la lista |

</details>

<details>
<summary>Nodolista (estructuras.h)</summary>

- *Descripción*: Nodo genérico para listas enlazadas de strings. Se usa para múltiples propósitos.

    |Atributo	    |Tipo	        |Descripción                           |
    |-------------|-------------|--------------------------------------|
    |`dato`	      |std::string	|Valor de cadena almacenado            |
    |`siguiente`  |Nodolista*	  |Puntero al siguiente nodo en la lista |

</details>

<details>
<summary>NodoSetInt (estructuras.h)</summary>

- *Descripción*: Nodo para implementar conjuntos (sets) de enteros. Usado para exclusiones en recomendaciones.

    |Atributo	    |Tipo	        |Descripción                              |
    |-------------|-------------|-----------------------------------------|
    |`dato`	      |int	        |Valor entero almacenado                  |
    |`siguiente`	|NodoSetInt*	|Puntero al siguiente nodo en el conjunto |

</details>

<details>
<summary>NodoMapaStringInt (estructuras.h)</summary>

- *Descripción*: Nodo para mapas clave-valor donde la clave es string y el valor es entero. Usado para conteo de frecuencias.

    |Atributo	  |Tipo	              |Descripción                          |
    |-----------|-------------------|-------------------------------------|
    |clave	    |std::string	      |Clave del mapa                       |
    |valor	    |int	              |Valor entero asociado                |
    |siguiente	|NodoMapaStringInt*	|Puntero al siguiente nodo en el mapa |

</details>

<details>
<summary>NodoMapaIntInt (estructuras.h)</summary>

- *Descripción*: Nodo para mapas clave-valor donde ambos son enteros. Usado para conteo de calidades.

    |Atributo	    |Tipo	            |Descripción                          |
    |-------------|-----------------|-------------------------------------|
    |`clave`	    |int	            |Clave entera del mapa                |
    |`valor`	    |int	            |Valor entero asociado                |
    |`siguiente`  |NodoMapaIntInt*	|Puntero al siguiente nodo en el mapa |

</details>

<details>
<summary>Usuario (estructuras.h)</summary>

- *Descripción*: Almacena toda la información de un usuario registrado, incluyendo sus preferencias y actividad.

    |Atributo  	            |Tipo	        |Descripción                         |
    |-----------------------|-------------|------------------------------------|
    |`nombre`	              |std::string	|Nombre real del usuario             |
    |`apellido`	            |std::string	|Apellido del usuario                |
    |`id`	                  |std::string	|ID único del usuario                |
    |`usuario`	            |std::string	|Nombre de usuario (login)           |
    |`password`	            |std::string	|Contraseña del usuario              |
    |`preferencias`	        |ListaString	|Lista de marcas preferidas          |
    |`categoriasPreferidas`	|ListaString	|Lista de categorías preferidas      |
    |`historial`	          |ListaString	|IDs de productos vistos (historial) |
    |`carrito`	            |ListaString	|IDs de productos en el carrito      |
    |`listaDeseos`	        |ListaString	|IDs de productos en lista de deseos |

</details>

<details>
<summary>Nodoarbol (estructuras.h)</summary>

- *Descripción*: Nodo para árbol binario de búsqueda de usuarios. Permite almacenamiento y búsqueda eficiente.

    |Atributo	    |Tipo	        |Descripción                   |
    |-------------|-------------|------------------------------|
    |`dato`	      |Usuario	    |Usuario almacenado en el nodo |
    |`izquierda`	|Nodoarbol*	  |Puntero al hijo izquierdo     | 
    |`derecha`	  |Nodoarbol*	  |Puntero al hijo derecho       |

</details>

<details>
<summary>Recomendaciones (estructuras.h)</summary>

- *Descripción*: Contenedor para los resultados del sistema de recomendaciones, organizado por categorías.

    |Atributo	                  |Tipo	          |Descripción                                   |
    |---------------------------|---------------|----------------------------------------------|
    |`porMarcasPreferidas`	    |ListaProducto	|Productos de marcas explícitamente preferidas |
    |`porOtrasMarcasFrecuentes`	|ListaProducto	|Productos de marcas frecuentes no preferidas  |
    |`porCategoriaPreferida`	  |ListaProducto	|Productos de categorías preferidas            |
    |`porCategoriaFrecuente`	  |ListaProducto	|Productos de categorías más visitadas         |
    |`porCalidad`	              |ListaProducto	|Productos con calidad similar a lo habitual   |

</details>

<details>
<summary>EstadisticasUsuario (recomendacion.h)</summary>

- *Descripción*: Almacena estadísticas de comportamiento del usuario derivadas de su historial.

    |Atributo	              |Tipo	        |Descripción                           |
    |-----------------------|-------------|--------------------------------------|
    |`categoriasFrecuentes`	|ListaString	|Top 2 categorías más visitadas        |
    |`marcasFrecuentes`	    |ListaString	|Top 2 marcas más visitadas            |
    |`calidadFrecuente`	    |int	        |Calidad más común en productos vistos |

</details>

## Relación entre Estructuras

``` mermaid
  graph LR
    A[Usuario] --> B[Nodoarbol]
    C[Producto] --> D[NodoProducto]
    E[Recomendaciones] --> D
    F[EstadisticasUsuario] --> G[ListaString]
    A --> H[ListaString] --> I[Nodolista]
    J[SetInt] --> K[NodoSetInt]
    L[MapaStringInt] --> M[NodoMapaStringInt]
    N[MapaIntInt] --> O[NodoMapaIntInt]
```

## Listado completo de funciones y agrupaciones.

<details>
<summary>Módulo Principal (main.cpp)</summary>                                                       

|Función	|Descripción	                |Relaciones/Dependencias               |
|-----------|-------------------------------|--------------------------------------|
|`main()`	|Punto de entrada del programa	|`inicializarCatalogo()`, `Mainmenu()` |

</details>

<details>
<summary>Gestión de Usuarios (usuario.h/cpp)</summary>

|Función	                        |Descripción	                                |Relaciones/Dependencias                                                                    |    
|-----------------------------------|-----------------------------------------------|-------------------------------------------------------------------------------------------|
|`crearNodo(Usuario valor)`	        |Crea nuevo nodo de árbol para usuarios	        |-                                                                                          |
|`buscar(Nodoarbol*, string)`	    |Busca usuario en el árbol	                    |-                                                                                          |
|`insertar(Nodoarbol*&, Usuario&)`	|Inserta usuario en árbol binario de búsqueda	|`crearNodo()`                                                                              |
|`verificarPassword()`	            |Valida contraseña de usuario	                |-                                                                                          |
|`imprimirUsuario()`	            |Muestra detalles de usuario registrado	        |`encabezado()`, `pausarConsola()`                                                          |
|`seleccionarPreferencias()`	    |Selección de marcas/categorías preferidas	    |`obtenerMarcasUnicas()`, `obtenerCategoriasUnicas()`, `insertarLista()`, `existeEnLista()` |
|`ComandoRegistrarUsuario()`	    |Proceso completo de registro de usuario	    |`buscar()`, `generarID()`, `seleccionarPreferencias()`, `insertar()`, `imprimirUsuario()`  |
|`ComandoIngresarUsuario()`	        |Proceso de autenticación de usuario	        |`buscar()`, `verificarPassword()`                                                          |

</details>

<details>
<summary>Interfaz de Usuario (interfaz.h/cpp)</summary>

| Función                               | Descripción                                 | Relaciones/Dependencias                                                                                  |
|----------------------------------------|---------------------------------------------|----------------------------------------------------------------------------------------------------------|
| `mostrarMenuUsuario(Usuario*)`         | Menú principal después de login             | `verCarrito()`, `verListaDeseos()`, `verHistorial()`, `verDetallesProducto()`, `generarRecomendaciones()`, `buscarPorCategoria()`, etc. |
| `verCarrito(Usuario*)`                 | Muestra y gestiona carrito de compras       | Accede a `catalogoGlobal`                                                                               |
| `verListaDeseos(Usuario*)`             | Muestra y gestiona lista de deseos          | Accede a `catalogoGlobal`                                                                               |
| `verHistorial(Usuario*)`               | Muestra historial de productos vistos       | Accede a `catalogoGlobal`                                                                               |
| `verDetallesProducto(int, Usuario*)`   | Muestra detalles completos de un producto   | `insertarLista()` (para historial)                                                                      |
| `mostrarProductosPorCategoria()`       | Muestra productos por categoría específica  | `buscarPorCategoria()`                                                                                  |
| `Mainmenu()`                          | Menú principal del sistema                  | `ComandoRegistrarUsuario()`, `ComandoIngresarUsuario()`                                                 |

</details>

<details>
<summary>Catálogo de Productos (catalogo.h/cpp)</summary>

|Función	                |Descripción	                                    |Relaciones/Dependencias          |
|---------------------------|---------------------------------------------------|---------------------------------|
|`inicializarCatalogo()`	    |Carga productos iniciales en memoria	            |`insertarEnLista()`                |
|`buscarPorCategoria()`	    |Filtra productos por categoría	                    |`aMinusculas()`                    |
|`buscarPorRangoPrecios()`	|Filtra productos por rango de precios	            |-                                |
|`buscarPorMarca()`	        |Filtra productos por marca	                        |`aMinusculas()`                    |
|`buscarPorDescripcion()`	    |Busca productos por palabra clave en descripción	|`aMinusculas()`                    |
|`obtenerCategoriasUnicas()`	|Obtiene lista de categorías únicas	                |`existeEnLista()`, `insertarLista()` |
|`obtenerMarcasUnicas()`	    |Obtiene lista de marcas únicas	                    |`existeEnLista()`, `insertarLista()` |

</details>

<details>
<summary>Sistema de Recomendaciones (recomendacion.h/cpp)</summary>

| Función                           | Descripción                                         | Relaciones/Dependencias                                                                                   |
|------------------------------------|-----------------------------------------------------|-----------------------------------------------------------------------------------------------------------|
| `generarRecomendaciones(Usuario*)` | Genera todas las recomendaciones personalizadas      | `actualizarPreferenciasDinamicas()`, `obtenerEstadisticasUsuario()`, `insertarEnSet()`, `buscarEnSet()`, `insertarEnLista()`, `barajarLista()` |
| `obtenerEstadisticasUsuario()`     | Analiza comportamiento del usuario                  | `incrementarEnMapa()`, `obtenerTopN()`                                                                    |
| `actualizarPreferenciasDinamicas()`| Actualiza preferencias basadas en historial         | `incrementarEnMapa()`, `obtenerTopN()`                                                                    |
| `obtenerTopN()`                    | Obtiene elementos más frecuentes en un mapa         | `existeEnLista()`, `insertarLista()`                                                                      |

</details>

<details>
<summary>Utilidades (utilidades.h/cpp)</summary>

| Función                | Descripción                                   | Relaciones/Dependencias                   |
|------------------------|-----------------------------------------------|-------------------------------------------|
| `generarID()`          | Genera identificador único aleatorio          | -                                         |
| `aMinusculas()`        | Convierte texto a minúsculas                  | -                                         |
| `leertexto()`          | Lee entrada de usuario con validación         | -                                         |
| `clearScreen()`        | Limpia la pantalla de la consola              | -                                         |
| `pausarConsola()`      | Pausa la ejecución hasta presionar Enter      | -                                         |
| `opcioninvalida()`     | Muestra mensaje de opción inválida            | -                                         |
| `printCentered()`      | Imprime texto centrado                        | -                                         |
| `encabezado()`         | Imprime encabezado formateado                 | `printCentered()`                         |
| `seccion()`            | Imprime sección formateada                    | `printCentered()`                         |
| `insertarLista()`      | Inserta elemento en lista enlazada            | -                                         |
| `existeEnLista()`      | Verifica si elemento existe en lista          | -                                         |
| `insertarEnLista()`    | Inserta producto en lista de productos        | -                                         |
| `longitudLista()`      | Calcula longitud de lista de productos        | -                                         |
| `obtenerElementoEn()`  | Obtiene elemento en posición específica       | -                                         |
| `barajarLista()`       | Mezcla aleatoriamente lista de productos      | `longitudLista()`, `obtenerElementoEn()`  |
| `buscarEnSet()`        | Busca elemento en conjunto                    | -                                         |
| `insertarEnSet()`      | Inserta elemento en conjunto                  | `buscarEnSet()`                           |
| `incrementarEnMapa()`  | Incrementa contador en mapa                   | -                                         |
| `mapaEstaVacio()`      | Verifica si mapa está vacío                   | -                                         |

</details>

<details>
<summary>Estructuras de Datos (estructuras.h)</summary>

| Estructura             | Descripción                                 | Funciones Relacionadas                |
|------------------------|---------------------------------------------|---------------------------------------|
| Producto               | Almacena datos de productos                 | `mostrar()` (método)                  |
| NodoProducto           | Nodo para lista enlazada de productos       | Todas funciones de catálogo           |
| Nodolista              | Nodo para listas de strings                 | Funciones de listas en `utilidades`   |
| NodoSetInt             | Nodo para conjunto de enteros               | Funciones de `sets`                   |
| NodoMapaStringInt      | Nodo para mapa string→int                   | Funciones de `mapas`                  |
| NodoMapaIntInt         | Nodo para mapa int→int                      | Funciones de `mapas`                  |
| Usuario                | Almacena datos de usuario                   | Todas funciones de `usuario`          |
| Nodoarbol              | Nodo para árbol binario de usuarios         | Funciones de gestión de `usuarios`    |
| Recomendaciones        | Contenedor para resultados de recomendación | `generarRecomendaciones()`            |
| EstadisticasUsuario    | Almacena estadísticas de comportamiento     | `obtenerEstadisticasUsuario()`        |

</details>

## Agrupaciones funcionales

<details>
<summary>1. Gestión de Usuarios</summary>

- **Funciones**:
    - `crearNodo()`
    - `insertar()`
    - `buscar()`
    - `verificarPassword()`
    - `ComandoRegistrarUsuario()`
    - `ComandoIngresarUsuario()`

- **Estructuras**:
    - `Usuario`
    - `Nodoarbol`

- **Relaciones**:
    - Árbol binario de búsqueda para almacenamiento eficiente de usuarios

</details>

<details>
<summary>2. Interfaz de Usuario</summary>

- **Funciones**:
    - `mostrarMenuUsuario()`
    - `verCarrito()`
    - `verListaDeseos()`
    - `verHistorial()`
    - `verDetallesProducto()`
    - `Mainmenu()`

- **Estructuras**:
    - Utiliza estructuras de usuario y catálogo (`Usuario`, `Producto`, `NodoProducto`)

- **Relaciones**:
    - Menús jerárquicos con navegación entre diferentes secciones del sistema

</details>

<details>
<summary>3. Gestión de Catálogo</summary>

- **Funciones**:
    - `inicializarCatalogo()`
    - `buscarPorCategoria()`
    - `buscarPorRangoPrecios()`
    - `buscarPorMarca()`
    - `buscarPorDescripcion()`
    - `obtenerCategoriasUnicas()`
    - `obtenerMarcasUnicas()`

- **Estructuras**:
    - `Producto`
    - `NodoProducto`

- **Relaciones**:
    - Lista enlazada global `catalogoGlobal` almacena todos los productos

</details>

<details>
<summary>4. Sistema de Recomendaciones</summary>

- **Funciones**:
    - `generarRecomendaciones()`
    - `obtenerEstadisticasUsuario()`
    - `actualizarPreferenciasDinamicas()`
    - `obtenerTopN()`

- **Estructuras**:
    - `Recomendaciones`
    - `EstadisticasUsuario`

- **Relaciones**:
    - Algoritmo basado en 5 estrategias combinadas con actualización dinámica de preferencias

</details>

<details>
<summary>5. Utilidades y Estructuras de Datos</summary>

- **Funciones**:
    - Todas las funciones en `utilidades.h/cpp`

- **Estructuras**:
    - Todas las estructuras en `estructuras.h`

- **Relaciones**:
    - Tipos: Listas enlazadas, conjuntos, mapas, árboles binarios

</details>

<details>
<summary>6. Gestión de Estado</summary>

- **Variables Globales**:
    - `Nodoarbol* Usuarios`: Árbol de usuarios registrados
    - `ListaProducto catalogoGlobal`: Lista de todos los productos

- **Persistencia**:
    - Todos los datos se mantienen en memoria durante la ejecución

</details>

## Relaciones cruzadas

```mermaid
    graph LR
    A[Mainmenu] --> B[ComandoRegistrarUsuario]
    A --> C[ComandoIngresarUsuario]
    C --> D[mostrarMenuUsuario]
    D --> E[generarRecomendaciones]
    E --> F[actualizarPreferenciasDinamicas]
    E --> G[obtenerEstadisticasUsuario]
    F --> H[incrementarEnMapa]
    G --> I[obtenerTopN]
    D --> J[verDetallesProducto]
    J --> K[insertarLista]
    K --> L[Historial Usuario]
```

## Flujo principal del programa

```mermaid
    graph TD
    A[Inicio] --> B[Inicializar Catálogo]
    B --> C[Mostrar Menú Principal]
    C --> D{Opción}
    D -->|1| E[Registrar Usuario]
    D -->|2| F[Iniciar Sesión]
    D -->|3| G[Salir]
    E --> H[Proceso Registro]
    H --> C
    F --> I[Proceso Inicio Sesión]
    I -->|Éxito| J[Menú Usuario]
    I -->|Falló| C
    J -->|Cerrar Sesión| C
    G --> K[Fin]
```

## Registro de usuario (ComandoRegistrarUsuario)

```mermaid
    graph TD
    A[Inicio] --> B[Limpiar pantalla]
    B --> C[Mostrar encabezado Registro]
    C --> D[Solicitar Nombre]
    D --> E{Validar nombre no vacío?}
    E -->|No| D
    E -->|Sí| F[Registrar nombre]
    F --> G[Solicitar Apellido]
    G --> H{Validar apellido no vacío?}
    H -->|No| G
    H -->|Sí| I[Registrar apellido]
    I --> J[Solicitar Usuario]
    J --> K{Validar usuario?}
    K -->|Vacío| L[Mostrar error]
    L --> J
    K -->|Con espacios| M[Mostrar error]
    M --> J
    K -->|Válido| N{Existe usuario?}
    N -->|Sí| O[Mostrar usuario existente]
    O --> P[¿Intentar otro?]
    P -->|Sí| J
    P -->|No| Q[Cancelar registro]
    Q --> R[Fin]
    N -->|No| S[Registrar usuario]
    S --> T[Solicitar Contraseña]
    T --> U{Longitud >= 6?}
    U -->|No| V[Mostrar error]
    V --> T
    U -->|Sí| W[Registrar contraseña]
    W --> X[Generar ID único]
    X --> Y[Seleccionar Marcas Preferidas]
    Y --> Z[Mostrar marcas disponibles]
    Z --> AA[Leer selección]
    AA --> AB{Validar selección?}
    AB -->|Inválida| AC[Mostrar error]
    AC --> AA
    AB -->|Válida| AD[Registrar marcas]
    AD --> AE[Seleccionar Categorías Preferidas]
    AE --> AF[Mostrar categorías disponibles]
    AF --> AG[Leer selección]
    AG --> AH{Validar selección?}
    AH -->|Inválida| AI[Mostrar error]
    AI --> AG
    AH -->|Válida| AJ[Registrar categorías]
    AJ --> AK[Crear objeto Usuario]
    AK --> AL[Inicializar listas: null]
    AL --> AM[Insertar usuario en árbol]
    AM --> AN[Limpiar pantalla]
    AN --> AO[Mostrar datos usuario]
    AO --> AP[Pausar consola]
    AP --> R[Fin]
```

## Inicio de Sesión (ComandoIngresarUsuario)

```mermaid
    graph TD
    A[Inicio] --> B[Solicitar Usuario]
    B --> C{Existe usuario?}
    C -->|No| D[¿Intentar otro?]
    D -->|Sí| B
    D -->|No| Z[Fin - Retorna nulo]
    C -->|Sí| E[Solicitar Contraseña]
    E --> F{Contraseña correcta?}
    F -->|Sí| G[Retorna Usuario]
    F -->|No| H[Incrementar Intentos]
    H --> I{Intentos < 3?}
    I -->|Sí| J[¿Reintentar?]
    J -->|Sí| E
    J -->|No| Z
    I -->|No| K[Superados intentos]
    K --> Z
```
## Menú de Usuario (mostrarMenuUsuario)

```mermaid
    graph TD
    A[Inicio] --> B[Mostrar Menú]
    B --> C{Opción}
    C -->|1| D[Ver Catálogo]
    C -->|2| E[Ver Recomendaciones]
    C -->|3| F[Buscar Productos]
    C -->|4| G[Ver Carrito]
    C -->|5| H[Ver Lista Deseos]
    C -->|6| I[Ver Historial]
    C -->|7| J[Cerrar Sesión]
    
    D --> K[Mostrar todas las categorías]
    K --> L{Solicitar ID producto?}
    L -->|Sí| M[verDetallesProducto]
    L -->|No| B
    
    E --> N[generarRecomendaciones]
    N --> O[Mostrar recomendaciones]
    O --> P{Solicitar ID producto?}
    P -->|Sí| Q[verDetallesProducto]
    P -->|No| B
    
    F --> R[Mostrar opciones búsqueda]
    R --> S{Sub-opción}
    S -->|1| T[Buscar por categoría]
    S -->|2| U[Buscar por precio]
    S -->|3| V[Buscar por marca]
    S -->|4| W[Buscar por descripción]
    S -->|5| B
    T --> X[Solicitar categoría, mostrar resultados]
    U --> Y[Solicitar rango precios, mostrar resultados]
    V --> Z[Solicitar marca, mostrar resultados]
    W --> AA[Solicitar palabra clave, mostrar resultados]
    X --> AB{Solicitar ID producto?}
    Y --> AB
    Z --> AB
    AA --> AB
    AB -->|Sí| AC[verDetallesProducto]
    AB -->|No| R
    
    G --> AD[verCarrito]
    AD --> AE{Opciones}
    AE -->|Comprar| AF[Vaciar carrito, mostrar gracias]
    AE -->|Vaciar| AG[Vaciar carrito]
    AE -->|Volver| B
    
    H --> AH[verListaDeseos]
    AH --> AI{Opciones}
    AI -->|Vaciar| AJ[Vaciar lista]
    AI -->|Volver| B
    
    I --> AK[verHistorial]
    AK --> B
    
    J --> AL[Fin - Volver a menú principal]
```

## Ver Detalles de Producto (verDetallesProducto)

```mermaid
    graph TD
    A[Inicio] --> B[Mostrar detalles producto]
    B --> C[Agregar a historial usuario]
    C --> D[Mostrar opciones]
    D -->|1| E[Agregar al carrito]
    D -->|2| F[Agregar a lista deseos]
    D -->|3| G[Volver]
    E --> H[Actualizar carrito]
    H --> I[Mostrar confirmación]
    I --> Z[Fin]
    F --> J[Actualizar lista deseos]
    J --> K[Mostrar confirmación]
    K --> Z
    G --> Z
```

## Generación de Recomendaciones (generarRecomendaciones)

```mermaid
    graph TD
    A[Inicio] --> B[Actualizar preferencias dinámicas]
    B --> C[Obtener estadísticas usuario]
    C --> D[Crear conjunto de productos excluidos]
    D --> E[Agregar historial, carrito y lista deseos a excluidos]
    
    E --> F{Usuario tiene preferencias?}
    F -->|Sí| G[Obtener productos de marcas preferidas no excluidos]
    F -->|No| H
    
    H --> I{Estadísticas tienen marcas frecuentes?}
    I -->|Sí| J[Obtener productos de marcas frecuentes no preferidas]
    I -->|No| K
    
    K --> L{Estadísticas tienen categorías frecuentes?}
    L -->|Sí| M[Obtener productos de categorías frecuentes]
    L -->|No| N
    
    N --> O{Usuario tiene categorías preferidas?}
    O -->|Sí| P[Obtener productos de categorías preferidas]
    O -->|No| Q
    
    Q --> R{Estadísticas tienen calidad frecuente?}
    R -->|Sí| S[Obtener productos de calidad similar]
    R -->|No| T
    
    T --> U[Barajar listas resultantes]
    U --> V[Construir estructura de recomendaciones]
    V --> W[Retornar recomendaciones]
```

## Flujo de Actualización de Preferencias Dinámicas

```mermaid
    graph TD
    A[Inicio] --> B[Limpiar preferencias anteriores]
    B --> C[Recorrer historial usuario]
    C --> D[Contar categorías y marcas]
    D --> E{Existen categorías?}
    E -->|Sí| F[Obtener top 2 categorías]
    F --> G[Asignar como categorías preferidas]
    E -->|No| H
    
    H --> I{Existen marcas?}
    I -->|Sí| J[Obtener top 2 marcas]
    J --> K[Agregar a preferencias si no existen]
    I -->|No| L[Fin]
```

## Sistema de recomendacion

```mermaid
    graph LR
    A[Preferencias Usuario] --> B[Marcas Preferidas]
    C[Historial Visualización] --> D[Categorías Frecuentes]
    C --> E[Marcas Frecuentes]
    C --> F[Calidad Frecuente]
    
    B --> G[Productos Marcas Pref]
    D --> H[Productos Categorías Frec]
    E --> I[Productos Otras Marcas Frec]
    F --> J[Productos Calidad Similar]
    
    G --> K[Recomendaciones]
    H --> K
    I --> K
    J --> K
```
