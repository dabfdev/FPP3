#include <iostream> //Entrada y salida estandar
#include <fstream> //Manipulación de archivos
#include <string> //manejo de cadenas y caracteres
#include <vector> //Contenedores dinamicos
#include <map> // Contenedor de mapa para almacenar pares clave
#include <cstdlib> // Para la función system()

// Función para autenticar usuarios
bool autenticarUsuario() {
    std::map<std::string, std::string> usuarios = {
        {"Javier", "umg1"},
        {"Jose", "umg2"},
        {"Diego", "umg3"}
    };

    std::string usuario;
    std::string contrasena;

    std::cout << "Ingrese el nombre de usuario: ";
    std::cin >> usuario;
    std::cout << "Ingrese la contrasena: ";
    std::cin >> contrasena;

    auto it = usuarios.find(usuario);
    if (it != usuarios.end() && it->second == contrasena) {
        std::cout << "Autenticacion exitosa." << std::endl;
        return true;
    } else {
        std::cout << "Usuario o contraseña incorrectos." << std::endl;
        return false;
    }
}

// Almacenamos las traducciones de una palabra en distintos idiomas
struct Traduccion {
    std::string italiano;
    std::string frances;
    std::string aleman;
    std::string ingles;
};

// Representa el árbol de búsqueda para identificar las palabras
struct Nodo {
    std::string espanol;
    Traduccion traducciones;
    Nodo* izquierda;
    Nodo* derecha;
};

//PARTE 1 NUEVO///
// Clase para encriptar y desencriptar palabras
class Encriptador {
public:
    std::string encriptar(const std::string& palabra);
    std::string desencriptar(const std::string& palabra);
};

std::string Encriptador::encriptar(const std::string& palabra) {
    std::string resultado;
    for (char c : palabra) {
        switch (c) {
            case 'a': resultado += "U1"; break;
            case 'e': resultado += "U2"; break;
            case 'i': resultado += "U3"; break;
            case 'o': resultado += "U4"; break;
            case 'u': resultado += "U5"; break;
            case 'b': resultado += "m1"; break;
            case 'c': resultado += "m2"; break;
            case 'd': resultado += "m3"; break;
            case 'f': resultado += "m4"; break;
            case 'g': resultado += "m5"; break;
            case 'h': resultado += "m6"; break;
            case 'j': resultado += "m7"; break;
            case 'k': resultado += "m8"; break;
            case 'l': resultado += "m9"; break;
            case 'm': resultado += "m10"; break;
            case 'n': resultado += "m11"; break;
            case 'ñ': resultado += "m12"; break;
            case 'p': resultado += "m13"; break;
            case 'q': resultado += "m14"; break;
            case 'r': resultado += "m15"; break;
            case 's': resultado += "m16"; break;
            case 't': resultado += "m17"; break;
            case 'v': resultado += "m18"; break;
            case 'w': resultado += "m19"; break;
            case 'x': resultado += "m20"; break;
            case 'y': resultado += "m21"; break;
            case 'z': resultado += "m22"; break;
            case 'B': resultado += "g1"; break;
            case 'C': resultado += "g2"; break;
            case 'D': resultado += "g3"; break;
            case 'F': resultado += "g4"; break;
            case 'G': resultado += "g5"; break;
            case 'H': resultado += "g6"; break;
            case 'J': resultado += "g7"; break;
            case 'K': resultado += "g8"; break;
            case 'L': resultado += "g9"; break;
            case 'M': resultado += "g10"; break;
            case 'N': resultado += "g11"; break;
            case 'Ñ': resultado += "g12"; break;
            case 'P': resultado += "g13"; break;
            case 'Q': resultado += "g14"; break;
            case 'R': resultado += "g15"; break;
            case 'S': resultado += "g16"; break;
            case 'T': resultado += "g17"; break;
            case 'V': resultado += "g18"; break;
            case 'W': resultado += "g19"; break;
            case 'X': resultado += "g20"; break;
            case 'Y': resultado += "g21"; break;
            case 'Z': resultado += "g22"; break;
            default: resultado += c;
        }
    }
    return resultado;
}

std::string Encriptador::desencriptar(const std::string& palabra) {
    // Implementación de desencriptar
    return palabra; //
}

// Función para reproducir sonido usando espeak
void reproducirSonido(const std::string& palabra, const std::string& idioma) {
    std::string comando = "espeak -v " + idioma + " \"" + palabra + "\"";
    system(comando.c_str());
}
//FIN PARTE 1 NUEVO//

// Manipulación del árbol de búsqueda //DIEGO//
class ArbolTraductor {
private:
    Nodo* raiz;
    Encriptador encriptador; // Agregar un objeto de la clase Encriptador 
    std::map<std::string, int> historialBusqueda; // Para almacenar el historial de búsqueda

    Nodo* insertar(Nodo* nodo, std::string espanol, Traduccion traducciones);
    Nodo* eliminar(Nodo* nodo, std::string espanol);
    Nodo* encontrarMinimo(Nodo* nodo);
    void destruirArbol(Nodo* nodo);
    void mostrar(Nodo* nodo);
    Nodo* buscar(Nodo* nodo, std::string espanol);

public:
    ArbolTraductor();
    ~ArbolTraductor();

    void cargarDesdeArchivo(const std::string& nombreArchivo);
    void agregarPalabra(std::string espanol, Traduccion traducciones);
    void eliminarPalabra(std::string espanol);
    void mostrarArbol();
    void buscarPalabra(std::string espanol);
    void menu();
    void menuAgregarPalabra();
    void guardarHistorial(const std::string& archivo); //Parte 2// Agregado recientemente//
    void generarLlave(const std::string& archivo);
    void generarArchivoInformacionOriginal(const std::string& archivo);
};

ArbolTraductor::ArbolTraductor() : raiz(nullptr) {}

ArbolTraductor::~ArbolTraductor() {
    destruirArbol(raiz);
}

void ArbolTraductor::destruirArbol(Nodo* nodo) {
    if (nodo) {
        destruirArbol(nodo->izquierda);
        destruirArbol(nodo->derecha);
        delete nodo;
    }
}

void ArbolTraductor::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string espanol, italiano, frances, aleman, ingles;
    while (archivo >> espanol >> italiano >> frances >> aleman >> ingles) {
        Traduccion traducciones = { italiano, frances, aleman, ingles };
        agregarPalabra(espanol, traducciones);
    }

    archivo.close();
}
//Diego//
void ArbolTraductor::agregarPalabra(std::string espanol, Traduccion traducciones) {
    // Encriptar la palabra antes de agregarla al árbol
    std::string palabraEncriptada = encriptador.encriptar(espanol);
    raiz = insertar(raiz, palabraEncriptada, traducciones);
}

Nodo* ArbolTraductor::insertar(Nodo* nodo, std::string espanol, Traduccion traducciones) {
    if (nodo == nullptr) {
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->espanol = espanol;
        nuevoNodo->traducciones = traducciones;
        nuevoNodo->izquierda = nullptr;
        nuevoNodo->derecha = nullptr;
        return nuevoNodo;
    }

    if (espanol < nodo->espanol) {
        nodo->izquierda = insertar(nodo->izquierda, espanol, traducciones);
    } else if (espanol > nodo->espanol) {
        nodo->derecha = insertar(nodo->derecha, espanol, traducciones);
    }

    return nodo;
}

void ArbolTraductor::eliminarPalabra(std::string espanol) {
    raiz = eliminar(raiz, encriptador.encriptar(espanol));
}

Nodo* ArbolTraductor::eliminar(Nodo* nodo, std::string espanol) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (espanol < nodo->espanol) {
        nodo->izquierda = eliminar(nodo->izquierda, espanol);
    } else if (espanol > nodo->espanol) {
        nodo->derecha = eliminar(nodo->derecha, espanol);
    } else {
        // Nodo con solo un hijo o sin hijos
        if (nodo->izquierda == nullptr) {
            Nodo* temp = nodo->derecha;
            delete nodo;
            return temp;
        } else if (nodo->derecha == nullptr) {
            Nodo* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Nodo con dos hijos: obtener el sucesor inorden (el mínimo en el subárbol derecho)
        Nodo* temp = encontrarMinimo(nodo->derecha);

        // Copiar el sucesor inorden al nodo actual
        nodo->espanol = temp->espanol;
        nodo->traducciones = temp->traducciones;

        // Eliminar el sucesor inorden
        nodo->derecha = eliminar(nodo->derecha, temp->espanol);
    }
    return nodo;
}

Nodo* ArbolTraductor::encontrarMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierda != nullptr) {
        actual = actual->izquierda;
    }
    return actual;
}

void ArbolTraductor::mostrarArbol() {
    // Función principal para mostrar todas las palabras y sus traducciones en el árbol.
    mostrar(raiz); // inicia recursión desde la raíz
}

void ArbolTraductor::mostrar(Nodo* nodo) {
    if (nodo) {
        mostrar(nodo->izquierda);
        //Parte 3// Jose
        // Mostrar la palabra en su idioma original y en su forma encriptada
        std::cout << "Palabra en su idioma original: " << nodo->espanol << std::endl;
        std::cout << "Palabra encriptada: " << encriptador.encriptar(nodo->espanol) << std::endl;

        std::cout << "Italiano: " << nodo->traducciones.italiano << std::endl;
        std::cout << "Italiano encriptado: " << encriptador.encriptar(nodo->traducciones.italiano) << std::endl;

        std::cout << "Frances: " << nodo->traducciones.frances << std::endl;
        std::cout << "Frances encriptado: " << encriptador.encriptar(nodo->traducciones.frances) << std::endl;

        std::cout << "Aleman: " << nodo->traducciones.aleman << std::endl;
        std::cout << "Aleman encriptado: " << encriptador.encriptar(nodo->traducciones.aleman) << std::endl;

        std::cout << "Ingles: " << nodo->traducciones.ingles << std::endl;
        std::cout << "Ingles encriptado: " << encriptador.encriptar(nodo->traducciones.ingles) << std::endl;

        std::cout << std::endl;

        mostrar(nodo->derecha);
    }
}

//Jose//
void ArbolTraductor::buscarPalabra(std::string espanol) {
    // Busca una palabra específica en español en el árbol.
    Nodo* resultado = buscar(raiz, encriptador.encriptar(espanol)); // Encriptar la palabra antes de buscar
    if (resultado) { // Verifica si se encontró la palabra.
        
        std::cout << std::endl;
        // Mostrar la palabra en español en su forma original y encriptada
        std::cout << "Palabra en espanol: " << espanol << std::endl;
        std::cout << "Palabra encriptada: " << resultado->espanol << std::endl;
std::cout << std::endl;
        // Mostrar las traducciones en sus idiomas originales y encriptadas
        std::cout << "Italiano: " << resultado->traducciones.italiano << std::endl;
        std::cout << "Italiano encriptado: " << encriptador.encriptar(resultado->traducciones.italiano) << std::endl;
std::cout << std::endl;
        std::cout << "Frances: " << resultado->traducciones.frances << std::endl;
        std::cout << "Frances encriptado: " << encriptador.encriptar(resultado->traducciones.frances) << std::endl;
std::cout << std::endl;
        std::cout << "Aleman: " << resultado->traducciones.aleman << std::endl;
        std::cout << "Aleman encriptado: " << encriptador.encriptar(resultado->traducciones.aleman) << std::endl;
std::cout << std::endl;
        std::cout << "Ingles: " << resultado->traducciones.ingles << std::endl;
        std::cout << "Ingles encriptado: " << encriptador.encriptar(resultado->traducciones.ingles) << std::endl;
        
        //Reproducir sonido mediante espeak
        reproducirSonido(resultado->traducciones.italiano, "it");
        reproducirSonido(resultado->traducciones.frances, "fr");
        reproducirSonido(resultado->traducciones.aleman, "de");
        reproducirSonido(resultado->traducciones.ingles, "en");
        // Incrementar el contador del historial de búsqueda
        historialBusqueda[resultado->espanol]++;
        
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "La palabra '" << espanol << "' no fue encontrada." << std::endl;
    }
}


Nodo* ArbolTraductor::buscar(Nodo* nodo, std::string espanol) {
    // Función recursiva para buscar una palabra específica en el árbol.
    if (nodo == nullptr || nodo->espanol == espanol) {
        return nodo; // Devuelve el nodo si es nulo o si contiene la palabra buscada.
    }

    if (espanol < nodo->espanol) {
        return buscar(nodo->izquierda, espanol); 
    } else {
        return buscar(nodo->derecha, espanol); // Búsqueda en el subárbol derecho.
    }
}

void ArbolTraductor::menu() {
    int opcion;

    do {
        std::cout << "--------------------Menu-----------------------------" << std::endl;
        std::cout << "1. Buscar una palabra y sus traducciones." << std::endl;
        std::cout << "2. Agregar una nueva palabra y sus traducciones." << std::endl;
        std::cout << "3. Eliminar una palabra del arbol." << std::endl;
        std::cout << "4. Mostrar el arbol." << std::endl;
        std::cout << "5. Guardar el historial con palabras encriptado." << std::endl;
        std::cout << "6. Generar archivo con la llave." << std::endl;
        std::cout << "7. Salir." << std::endl;
        std::cout << "Elija una opcion: ";
        std::cin >> opcion;
        
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        switch (opcion) {
            case 1:
                {
                    std::string palabra;
                    std::cout << "Ingrese la palabra en espanol: ";
                    std::cin >> palabra;
                    buscarPalabra(palabra);
                    break;
                }
            case 2:
                menuAgregarPalabra();
                break;
            case 3:
                {
                    std::string palabra;
                    std::cout << "Ingrese la palabra en espanol que desea eliminar: ";
                    std::cin >> palabra;
                    eliminarPalabra(palabra);
                    std::cout << "Palabra eliminada exitosamente." << std::endl;
                    break;
                }
            case 4:
                std::cout << "Arbol binario de busqueda:" << std::endl;
                mostrarArbol();
                break;
            case 5:
                {
                    std::string archivo;
                    std::cout << "Ingrese el nombre del archivo para guardar el historial: ";
                    std::cin >> archivo;
                    guardarHistorial(archivo);
                    std::cout << "Historial guardado exitosamente." << std::endl;
                    break;
                }
            case 6:
                {
                    std::string archivo;
                    std::cout << "Ingrese el nombre del archivo para generar la llave: ";
                    std::cin >> archivo;
                    generarLlave(archivo);
                    std::cout << "Llave generada exitosamente." << std::endl;
                    break;
                }
            case 7:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }

    } while (opcion != 7);
}

void ArbolTraductor::menuAgregarPalabra() {
	
    std::string palabra;
    Traduccion traducciones;

    std::cout << "Ingrese la palabra en espanol: ";
    std::cin >> palabra;
    std::cout << "Ingrese la traduccion en italiano: ";
    std::cin >> traducciones.italiano;
    std::cout << "Ingrese la traduccion en frances: ";
    std::cin >> traducciones.frances;
    std::cout << "Ingrese la traduccion en aleman: ";
    std::cin >> traducciones.aleman;
    std::cout << "Ingrese la traduccion en ingles: ";
    std::cin >> traducciones.ingles;

    agregarPalabra(palabra, traducciones);
    std::cout << "Palabra agregada exitosamente." << std::endl;
}

void ArbolTraductor::guardarHistorial(const std::string& archivo) {
    std::ofstream outFile(archivo);
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar el historial." << std::endl;
        return;
    }

    std::ofstream espanolFile("palabras_buscadas_espanol.txt"); // Archivo para guardar palabras buscadas en español
    if (!espanolFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar las palabras buscadas en español." << std::endl;
        return;
    }

    for (const auto& pair : historialBusqueda) {
        outFile << pair.first << " " << pair.second << std::endl;
        espanolFile << encriptador.desencriptar(pair.first) << std::endl; // Guarda la palabra desencriptada en español
    }

    outFile.close();
    espanolFile.close();
}

void ArbolTraductor::generarLlave(const std::string& archivo) {
    std::ofstream outFile(archivo);
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para generar la llave." << std::endl;
        return;
    }
    
    // Lista de mapeo de caracteres a su correspondiente encriptación
    std::vector<std::pair<char, std::string>> listaMapeo = {
        {'a', "U1"}, {'e', "U2"}, {'i', "U3"}, {'O', "U4"}, {'U', "U5"},
        {'b', "m1"}, {'c', "m2"}, {'d', "m3"}, {'f', "m4"}, {'g', "m5"},
        {'h', "m6"}, {'j', "m7"}, {'k', "m8"}, {'l', "9"}, {'m', "m10"},
        {'n', "m11"}, {'ñ', "m12"}, {'p', "m13"}, {'q', "m14"}, {'r', "m15"},
        {'s', "m16"}, {'t', "m17"}, {'v', "m18"}, {'w', "m19"}, {'x', "m20"},
        {'y', "m21"}, {'z', "m22"},
        {'B', "g1"}, {'C', "g2"}, {'D', "g3"}, {'F', "g4"}, {'G', "g5"},
        {'H', "g6"}, {'J', "g7"}, {'K', "g8"}, {'L', "g9"}, {'M', "g10"},
        {'N', "g11"}, {'Ñ', "g12"}, {'P', "g13"}, {'Q', "g14"}, {'R', "g15"},
        {'S', "g16"}, {'T', "g17"}, {'V', "g18"}, {'W', "g19"}, {'X', "g20"},
        {'Y', "g21"}, {'Z', "g22"}
    };

    // Escribir la lista en el archivo
    for (const auto& pair : listaMapeo) {
        outFile << pair.first << "=" << pair.second << std::endl;
    }

    outFile.close();
}

void ArbolTraductor::generarArchivoInformacionOriginal(const std::string& archivo) {
    std::ofstream outFile(archivo);
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para generar la información original." << std::endl;
        return;
    }

    std::ifstream archivoOriginal("traductor.txt");
    if (!archivoOriginal.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo original para leer la información." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(archivoOriginal, line)) {
        outFile << line << std::endl;
    }

    archivoOriginal.close();
    outFile.close();
}

int main() {
    if (!autenticarUsuario()) {
        return 1; // Salir del programa si la autenticación falla
    }

    ArbolTraductor arbol;
    arbol.cargarDesdeArchivo("traductor.txt");

    std::cout << "Bienvenido al traductor multilingue" << std::endl;
    std::cout << "====================================" << std::endl;

    arbol.menu();

    return 0;
}
