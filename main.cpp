#include <iostream>
#include <string>

/* Structs */

// Structs de datos
struct Usuario
{
    std::string nombre;
    std::string apellido;
    int id;
    std::string usuario;
    std::string contraseña;
};

struct Producto
{
    std::string descripcion;
    int id;
    std::string marca;
    double precio;
    int cantidad;
    std::string categoria;
};

// Stucts de estructuras de datos
struct Nodolista
{
    std::string dato;
    Nodolista *siguiente;
};

struct Nodoarbol
{
    Usuario dato;
    Nodoarbol *izquierda;
    Nodoarbol *derecha;
};

/* Funciones */

// Funciones para arbol de busqueda

// Crear un nuevo nodo
Nodoarbol *crearNodo(Usuario valor)
{
    Nodoarbol *nuevo = new Nodoarbol;
    nuevo->dato = valor;
    nuevo->izquierda = nullptr;
    nuevo->derecha = nullptr;

    return nuevo;
}

// Insertar un nuevo nodo
Nodoarbol *insertar(Nodoarbol *raiz, Usuario valor)
{
    // caso base
    if (raiz == nullptr)
    {
        return crearNodo(valor);
    }

    // caso recursivo
    if (valor.id < raiz->dato.id)
    {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    }
    else if (valor.id > raiz->dato.id)
    {
        raiz->derecha = insertar(raiz->derecha, valor);
    }

    return raiz;
}

// Buscar un nodo
Nodoarbol *buscar(Nodoarbol *raiz, int id)
{
    // caso base
    if (raiz == nullptr || raiz->dato.id == id)
    {
        return raiz;
    }

    // caso recursivo
    if (id < raiz->dato.id)
    {
        return buscar(raiz->izquierda, id);
    }
    else
    {
        return buscar(raiz->derecha, id);
    }
}

// Recorrer arbol
void inorden(Nodoarbol *raiz)
{
    if (raiz != nullptr)
    {
        inorden(raiz->izquierda);
        std::cout << "Id: " << raiz->dato.id << std::endl;
        std::cout << "Usuario: " << raiz->dato.usuario << std::endl;
        inorden(raiz->derecha);
    }
}

// liberar memoria
void LimpiarArbol(Nodoarbol *raiz)
{
    if (raiz != nullptr)
    {
        LimpiarArbol(raiz->izquierda);
        LimpiarArbol(raiz->derecha);
        delete raiz;
    }
}

int main()
{
    Nodoarbol *usuarios = nullptr;

    // Crear usuarios
    usuarios = insertar(usuarios, {"Luis", "Rojas", 30931891, "BlackWolf", "Lu30931891"});
    usuarios = insertar(usuarios, {"Daniel", "Reyna", 29989066, "IWinterI", "Da29989066"});
    usuarios = insertar(usuarios, {"Nicole", "Sereno", 31275411, "Niko", "Ni31275411"});

    // Buscar un usuario
    int id = 30931891;
    Nodoarbol *encontrado = buscar(usuarios, id);
    std::cout << "El id '" << id << "' pertenece al usuario: " << encontrado->dato.usuario << std::endl;

    id = 49218;
    encontrado = buscar(usuarios, id);
    if (encontrado == nullptr)
    {
        std::cout << "id no encontrada" << std::endl;
    }

    // Mostrar usuarios
    std::cout << "Usuarios registrados (ordenados por id): " << std::endl;
    inorden(usuarios);

    // Limpiar arbol
    LimpiarArbol(usuarios);

    inorden(usuarios);
    return 0;
}
