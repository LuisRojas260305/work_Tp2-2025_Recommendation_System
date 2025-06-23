#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <limits>
#include <algorithm>
#include <random>

/* Structs */

struct Nodolista
{
    std::string dato;
    Nodolista *siguiente;
};

struct Usuario
{
    std::string nombre;
    std::string apellido;
    std::string id;
    std::string usuario;
    std::string password;
    Nodolista *preferencias;
    Nodolista *historial;
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

struct Nodoarbol
{
    Usuario dato;
    Nodoarbol *izquierda;
    Nodoarbol *derecha;
};

/* Declaraciones globales */

// Registros de usuarios
Nodoarbol *Usuarios;

// Caracteres para ids
const std::string CARACTERES_VALIDOS =
    "1234567890"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&/()=?¡',.-;:_";

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
Nodoarbol *insertar(Nodoarbol *&raiz, Usuario &usuario)
{
    // caso base
    if (raiz == nullptr)
    {
        raiz = crearNodo(usuario);
        return raiz;
    }

    // caso recursivo
    if (usuario.usuario < raiz->dato.usuario)
    {
        raiz->izquierda = insertar(raiz->izquierda, usuario);
    }
    else if (usuario.usuario > raiz->dato.usuario)
    {
        raiz->derecha = insertar(raiz->derecha, usuario);
    }

    return raiz; // Esto es para ignorar a usuarios duplicados
}

// Buscar un nodo
Nodoarbol *buscar(Nodoarbol *raiz, const std::string &usuario)
{
    // caso base
    if (raiz == nullptr || raiz->dato.usuario == usuario)
    {
        return raiz;
    }

    // caso recursivo
    if (usuario < raiz->dato.usuario)
    {
        return buscar(raiz->izquierda, usuario);
    }
    else
    {
        return buscar(raiz->derecha, usuario);
    }
}

bool verificarPassword(Nodoarbol *nodo, const std::string &password)
{
    return nodo && nodo->dato.password == password;
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

// Funciones para utilidades

// Limpiar consola
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausar programa
void pausarConsola()
{
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Espera a que se presione Enter
}

// Imprimir centrado
void printCentered(const std::string &text, int width = 50)
{
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}

// Mensaje de error para opciones invalidas del menu
void opcioninvalida(int min, int max)
{
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Opcion invalida." << std::endl;
    std::cout << "Por favor ingrese un numero entre (" << min << "-" << max << ")" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

// Imprimir el encabezado de una opcion
void encabezado(const std::string &titulo)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '=') << std::endl;
}

// Leer texto por consola, con espacio y autoajustado
std::string leertexto()
{
    std::string entrada;

    // Limpiar posibles saltos de línea previos
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }

    // Leer la línea completa
    std::getline(std::cin, entrada);

    // Eliminar espacios en blanco al inicio/final
    size_t inicio = entrada.find_first_not_of(" ");
    size_t fin = entrada.find_last_not_of(" ");

    if (inicio == std::string::npos)
    { // Si es cadena vacía
        return "";
    }

    return entrada.substr(inicio, fin - inicio + 1);
}

// Generar id de los usuarios
std::string generarID()
{
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<int> distribucion(0, CARACTERES_VALIDOS.size() - 1);

    std::string id;
    for (int i = 0; i < 10; i++)
    {
        id += CARACTERES_VALIDOS[distribucion(generador)];
    }

    return id;
}

// imprimir un usuario registrado
void imprimirUsuario(Usuario &usuario)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered("Felicidades, nuevo usuario registrado.");
    std::cout << std::string(50, '=') << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Nombre: " << usuario.nombre << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Apellido: " << usuario.apellido << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Usuairo: " << usuario.usuario << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "ID: " << usuario.id << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Password: " << usuario.password << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

/* Comandos */

// Comando para registrar un usuario
void ComandoRegistrarUsuario()
{
    clearScreen();
    encabezado("Registro de usuario");
    std::cout << std::string(50, '=') << std::endl;

    Usuario nuevo;
    bool cancelado = false;

    // Función para validar campos vacíos
    auto validarCampo = [](const std::string &valor, const std::string &campo) -> bool
    {
        if (valor.empty())
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: El " << campo << " no puede estar vacio" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            return false;
        }
        return true;
    };

    // Validar nombre
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << std::endl;
        nuevo.nombre = leertexto();
    } while (!validarCampo(nuevo.nombre, "nombre"));
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Nombre registrado: " << nuevo.nombre << std::endl;

    // Validar apellido
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Apellido: " << std::endl;
        nuevo.apellido = leertexto();
    } while (!validarCampo(nuevo.apellido, "apellido"));
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Apellido registrado: " << nuevo.apellido << std::endl;

    // Validar usuario
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Usuario: " << std::endl;
        std::string input = leertexto();

        // Validar vacío
        if (!validarCampo(input, "usuario"))
            continue;

        // Validar espacios
        if (input.find(' ') != std::string::npos)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: El usuario no puede contener espacios" << std::endl;
            continue;
        }

        // Verificar unicidad
        Nodoarbol *coincidencia = buscar(Usuarios, input);
        if (coincidencia != nullptr)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "Usuario '" << input << "' ya registrado." << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Desea intentar con otro usuario? (s/n): ";
            std::string continuar = leertexto();
            std::cout << std::string(50, '-') << std::endl;

            if (continuar == "n" || continuar == "N")
            {
                std::cout << std::string(50, '=') << std::endl;
                printCentered("Registro de usuario cancelado");
                std::cout << std::string(50, '=') << std::endl;
                cancelado = true;
                break;
            }
            continue;
        }

        nuevo.usuario = input;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Usuario registrado: " << nuevo.usuario << std::endl;
        break;
    } while (true);

    if (cancelado)
    {
        pausarConsola();
        return;
    }

    // Validar contraseña
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Password (minimo 6 caracteres): " << std::endl;
        nuevo.password = leertexto();

        // Validar longitud mínima
        if (nuevo.password.length() < 6)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: La password debe tener minimo 6 caracteres" << std::endl;
            continue;
        }
        break;
    } while (true);

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Password registrada: " << nuevo.password << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Generar id
    nuevo.id = generarID();

    // Inicializar estructuras
    nuevo.historial = nullptr;
    nuevo.preferencias = nullptr;

    // Guardar usuario
    insertar(Usuarios, nuevo);

    // Mostrar resultado
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    printCentered("REGISTRO EXITOSO!");
    std::cout << std::string(50, '=') << std::endl;
    imprimirUsuario(nuevo);
    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}

// Comando para ingresar con un usuario
bool ComandoIngresarUsuario()
{
    do
    {
        clearScreen();
        encabezado("Ingresar a la plataforma.");
        std::cout << std::string(50, '=') << std::endl;

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese el usuario: " << std::endl;
        std::string usuario = leertexto();
        std::cout << std::string(50, '-') << std::endl;

        Nodoarbol *ingreso = buscar(Usuarios, usuario);

        if (ingreso == nullptr)
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "El usuario '" << usuario << "' no existe." << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Desea probar con otro usuario? (s/n): ";
            std::string opcion = leertexto();

            if (opcion == "n" || opcion == "N")
            {
                clearScreen();
                std::cout << std::string(50, '=') << std::endl;
                printCentered("Saliendo del login");
                std::cout << std::string(50, '=') << std::endl;
                pausarConsola();
                return false;
            }
            continue;
        }

        int intentos = 0;
        const int MAX_INTENTOS = 3;
        
        while (intentos < MAX_INTENTOS)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Ingrese la password: " << std::endl;
            std::string password = leertexto();
            std::cout << std::string(50, '-') << std::endl;

            if (verificarPassword(ingreso, password))
            {
                clearScreen();
                encabezado("LOGIN EXITOSO");
                pausarConsola();
                return true;
            }
            else
            {
                intentos++;
                std::cout << std::string(50, '=') << std::endl;
                std::cout << "Password incorrecta. Intento " << intentos << "/" << MAX_INTENTOS << std::endl;
                std::cout << std::string(50, '=') << std::endl;

                if (intentos < MAX_INTENTOS)
                {
                    std::cout << std::string(50, '-') << std::endl;
                    std::cout << "Desea intentar de nuevo? (s/n): ";
                    std::string reintentar = leertexto();
                    
                    if (reintentar == "n" || reintentar == "N")
                    {
                        clearScreen();
                        std::cout << std::string(50, '=') << std::endl;
                        printCentered("Saliendo del login");
                        std::cout << std::string(50, '=') << std::endl;
                        pausarConsola();
                        return false;
                    }
                }
            }
        }

        // Si se superan los intentos m�ximos
        std::cout << std::string(50, '=') << std::endl;
        printCentered("Ha superado el maximo de intentos");
        std::cout << std::string(50, '=') << std::endl;
        pausarConsola();
        return false;

    } while (true);
}

/* Menus */

void procesarMainmenu(int opcion)
{
    switch (opcion)
    {
    case 1:
        clearScreen();
        ComandoRegistrarUsuario();
        break;
    
    case 2:
    	clearScreen();
    	if(ComandoIngresarUsuario()){
			// Llamar al menu de usuario
		} else {
			// No se, hacemos algo si es false?
		}

    default:
        opcioninvalida(1, 3);
        pausarConsola();
        break;
    }
}

void Mainmenu()
{
    int opcion;

    do
    {
        clearScreen();
        encabezado("Bienvenid@ a Quantum Store.");
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "1.-Registrar un nuevo usuario." << std::endl;
        std::cout << "2.-Ingresar con un usuario existente." << std::endl;
        std::cout << "3.-Salir." << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        if (opcion == 3)
        {
            break;
        }
        else
        {
            procesarMainmenu(opcion);
        }

    } while (true);
}

int main()
{
    Mainmenu();

    std::cout << std::string(50, '=') << std::endl;
    printCentered("Gracias por visitar.");
    std::cout << std::string(50, '=') << std::endl;

    return 0;
}
