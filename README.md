# Diagrama de funciónes

```mermaid
flowchart TD
    A[Inicio] --> B[Menu Principal]
    B --> C{Opción}
    C -->|Registro| D[registrar_usuario]
    C -->|Login| E[iniciar_sesion]
    D --> F[Agregar al árbol de usuarios]
    E --> G{Validación}
    G -->|Falló| B
    G -->|Éxito| H[Menu Usuario]
    H --> I{Opción}
    I -->|Buscar productos| J[buscar_productos]
    I -->|Ver recomendaciones| K[generar_recomendaciones]
    I -->|Gestionar preferencias| L[agregar_preferencia_marca/categoria]
    I -->|Salir| M[liberar_memoria]
    J --> N{Submenú Búsqueda}
    N -->|Categoría| O[buscar_por_categoria]
    N -->|Precio| P[buscar_por_precio]
    N -->|Marca| Q[buscar_por_marca]
    N -->|Descripción| R[buscar_por_descripcion]
    K --> S[recomendar_por_marcas]
    K --> T[recomendar_por_historial]
    S --> U[mostrar_recomendaciones]
    T --> U
    U --> H
    M --> B
```

---

# Diagrama de relación de funciónes

```mermaid
graph TD
    %% Núcleo del Sistema
    menu_principal --> registrar_usuario
    menu_principal --> iniciar_sesion
    iniciar_sesion --> menu_usuario
    
    %% Gestión de Usuario
    menu_usuario --> agregar_preferencia_categoria
    menu_usuario --> agregar_preferencia_marca
    menu_usuario --> agregar_historial_visto
    menu_usuario --> agregar_historial_comprado
    
    %% Gestión de Productos
    menu_usuario --> buscar_productos
    buscar_productos --> buscar_por_categoria
    buscar_productos --> buscar_por_marca
    buscar_productos --> buscar_por_precio
    buscar_productos --> buscar_por_descripcion
    
    %% Sistema de Recomendación
    menu_usuario --> generar_recomendaciones
    generar_recomendaciones --> recomendar_por_marcas
    generar_recomendaciones --> recomendar_por_historial
    
    %% Funciones Base
    registrar_usuario --> arbol_insertar
    iniciar_sesion --> arbol_buscar
    agregar_preferencia_categoria --> lista_agregar
    agregar_historial_visto --> cola_encolar
    agregar_producto_catalogo --> arbol_insertar
    buscar_por_categoria --> arbol_buscar
    recomendar_por_marcas --> lista_agregar
    
    %% Utilidades
    buscar_por_descripcion --> comparar_strings
    buscar_por_precio --> string_a_float
    liberar_memoria --> liberar_arbol
    liberar_memoria --> liberar_lista
```

---

# Listado de funciones

## Funciones Principales

|Nombre de la función       |Funcionalidad                                 |
|---------------------------|----------------------------------------------|
|**main()**                 |Punto de entrada, llama a **menu_principal()**|
|**menu_principal()**       |Muestra opciones iniciales (login/registro)   |
|**menu_usuario(Usuario*)** |Menú post-login con todas las funcionalidades |

## Gestión de Usuarios

|Nombre de la función                                |Funcionalidad                    |
|----------------------------------------------------|---------------------------------|
|**registrar_usuario()**                             |Crea nuevo usuario con input     |
|**iniciar_sesion()**                                |Valida credenciales contra árbol |
|**agregar_preferencia_categoria(Usuario*, char*)**  |Añade categoría a lista          |
|**agregar_preferencia_marca(Usuario*, char*)**      |Añade marca a lista              |
|**agregar_historial_visto(Usuario*, Producto*)**    |Agrega a cola FIFO               |
|**agregar_historial_comprado(Usuario*, Producto*)** |Agrega a lista                   |

## Gestión de Productos

|Nombre de la función                                |Funcionalidad                      |
|----------------------------------------------------|-----------------------------------|
|**crear_producto()**                                |Asigna memoria para nuevo producto |
|**agregar_producto_catalogo(Catalogo*, Producto*)** |Inserta en 4 árboles               |
|**buscar_por_categoria(Catalogo*, char*)**          |Devuelve lista de productos        |
|**buscar_por_marca(Catalogo*, char*)**              |Lista productos por marca          |
|**buscar_por_precio(Catalogo*, float, float)**      |Productos en rango                 |
|**buscar_por_descripcion(Catalogo*, char*)**        |Búsqueda textual recursiva         |

## Recomendaciones

|Nombre de la función                              |Funcionalidad                  |
|--------------------------------------------------|-------------------------------|
|**generar_recomendaciones(Usuario*, Catalogo*)**  |Coordina recomendaciones       |
|**recomendar_por_marcas(Usuario*, Catalogo*)**    |Filtra por marcas preferidas   |
|**recomendar_por_historial(Usuario*, Catalogo*)** |Sugiere similares al historial |

## Estructuras de Datos

|Nombre de la función                                      |Funcionalidad           |
|----------------------------------------------------------|------------------------|
|**arbol_insertar(NodoArbol**, void*, int (*comparar)())** |Inserción recursiva     |
|**arbol_buscar(NodoArbol*, void*, int (*comparar)())**    |Búsqueda recursiva      |
|**lista_agregar(Lista**, void*)**                         |Añade nodo a lista      |
|**cola_encolar(Cola*, void*)**                            |Añade elemento a cola   |
|**cola_desencolar(Cola*)**                                |Remueve primer elemento |

## Utilidades

|Nombre de la función               |Funcionalidad                     |
|-----------------------------------|----------------------------------|
|**comparar_strings(char*, char*)** |Comparación de cadenas            |
|**string_a_float(char*)**          |Conversión cadena a flotante      |
|**liberar_arbol(NodoArbol*)**      |Libera memoria de árbol recursivo |
|**liberar_lista(Lista*)**          |Libera lista enlazada             |
|**mostrar_productos(Lista*)**      |Imprime lista de productos        |
