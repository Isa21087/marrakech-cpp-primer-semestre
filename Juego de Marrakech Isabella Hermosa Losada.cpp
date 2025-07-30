#include <iostream>
#include <ctime>   // Librería para manejar funciones de tiempo
#include <windows.h>
#include <fstream>

using namespace std;

// Para guardar datos de los jugadores en un solo elemento
struct Jugador
{
    string nombreJugador;        // Nombre del jugador
    string colorAlfombra;        // Color de la alfombra
    int cantidadAlfombras = 10;  // Cantidad de alfombras segun hurtado
    int cantidadMonedas = 20;    // Número de monedas segun hurtado
    int posFila;                 // Posición en fila actual
    int posColumna;              // Posición en columna
    int direccionMovimiento = 2; // Dirección con la que inicia el jugador (inicia para abajo)
};

// Única variable global
int tableroDeJuego[7][7] = {0};

// funciones
void imprimirLogoMarrakech();
void iniciarJuego(int tableroJuego[7][7]);
void imprimirTablero(int tableroJuego[7][7], int posFila, int posColumna, int direccionMovimiento, Jugador jugador1, Jugador jugador2);
void exportarInformacionPartida(Jugador jugador1, Jugador jugador2, int idGanador);
Jugador crearHassam();
int validarTableroDeJuego(int tableroJuego[7][7]);
Jugador pagarAOponente(Jugador jugador, int cantidadMonedas);
int colocarAlfombra(int tableroJuego[7][7], int posFila, int posColumna, int jugadorID);
Jugador moverHassam(Jugador Assam);
int lanzarDado();
Jugador capturarInformacionJugador();
int calcularPago(int tableroJuego[7][7], int posFila, int posColumna, int jugadorID);
int calcularPuntos(int tableroJuego[7][7], Jugador jugador, int idJugador);
string codigoColor(string color, int idJugador);
string elegirAlfombra();

int main()
{
    srand(time(0)); // Inicializar semilla una sola vez
    system("title Marrakech : Proyecto Final de Introduccion a la Programacion");
    SetConsoleOutputCP(CP_UTF8); // para tildes y para mi super felchita jijijijijiji
    cout << "\033[38;2;202;141;22m";
    iniciarJuego(tableroDeJuego);
    cout << "\033[0m";
    return 0;
}

string elegirAlfombra()
{
    string entrada;
    string alfombra;

    cout << "Seleccione (1, 2 ó 3) para elegir el color preferido de alfombra." << endl;

    do
    {
        cout << "(1) Rojo." << endl;
        cout << "(2) Azul." << endl;
        cout << "(3) Verde." << endl;
        cout << "Ingrese una opcion => ";
        cin >> entrada;

        if (entrada == "1")
        {
            alfombra = "Rojo";
        }
        else if (entrada == "2")
        {
            alfombra = "Azul";
        }
        else if (entrada == "3")
        {
            alfombra = "Verde";
        }
        else
        {
            cout << "Oye, opción no válida. Selecciona un número." << endl;
        }
    } while (entrada != "1" && entrada != "2" && entrada != "3");

    return alfombra;
}

Jugador capturarInformacionJugador()
{
    int op = 0;
    Jugador jugador;
    cout << "Ingrese el nombre del jugador => ";
    cin >> jugador.nombreJugador;
    jugador.colorAlfombra = elegirAlfombra();
    return jugador;
}

string codigoColor(string color, int idJugador)
{
    if ((color == "Rojo" || color == "ROJO" || color == "rojo") && idJugador == 1)
    {
        return "\033[31m1\033[38;2;202;141;22m";
    }
    else if ((color == "Azul" || color == "AZUL" || color == "azul") && idJugador == 1)
    {
        return "\033[94m1\033[38;2;202;141;22m";
    }
    else if ((color == "Verde" || color == "VERDE" || color == "verde") && idJugador == 1)
    {
        return "\033[32m1\033[38;2;202;141;22m";
    }
    else if ((color == "Rojo" || color == "ROJO" || color == "rojo") && idJugador == 2)
    {
        return "\033[31m2\033[38;2;202;141;22m";
    }
    else if ((color == "Azul" || color == "AZUL" || color == "azul") && idJugador == 2)
    {
        return "\033[94m2\033[38;2;202;141;22m";
    }
    else if ((color == "Verde" || color == "VERDE" || color == "verde") && idJugador == 2)
    {
        return "\033[32m2\033[38;2;202;141;22m";
    }
    else
    {
        return "\033[0m\033[38;2;202;141;22m";
    }
}

int lanzarDado()
{
    switch ((rand() % 4) + 1)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    }
    return -1;
}

Jugador moverHassam(Jugador Assam)
{
    Jugador jugador = Assam;
    string entrada;
    int op = 0;
    int movimiento = 0;

    if (Assam.direccionMovimiento == 1)
    {
        do
        {
            cout << " (1) Arriba." << endl;
            cout << " (3) Derecha." << endl;
            cout << " (4) Izquierda." << endl;
            cout << " Seleccione una opcion => ";
            cin >> entrada;
            if (entrada == "1" || entrada == "3" || entrada == "4")
            {
                op = entrada[0] - '0';
            }
            else if (entrada == "2")
            {
                cout << "Opcion de movimiento no valida en este momento." << endl;
                op = 2;
            }
            else
            {
                cout << "Opcion no valida. Selecciona un numero." << endl;
                op = 0;
            }
        } while (op == 2 || op == 0);
    }
    else if (Assam.direccionMovimiento == 2)
    {
        do
        {
            cout << " (2) Abajo." << endl;
            cout << " (3) Derecha." << endl;
            cout << " (4) Izquierda." << endl;
            cout << " Seleccione una opcion => ";
            cin >> entrada;
            if (entrada == "2" || entrada == "3" || entrada == "4")
            {
                op = entrada[0] - '0';
            }
            else if (entrada == "1")
            {
                cout << "Opcion de movimiento no valida en este momento." << endl;
                op = 1;
            }
            else
            {
                cout << "Opcion no valida. Selecciona un numero." << endl;
                op = 0;
            }
        } while (op == 1 || op == 0);
    }
    else if (Assam.direccionMovimiento == 3)
    {
        do
        {
            cout << " (1) Arriba." << endl;
            cout << " (2) Abajo." << endl;
            cout << " (3) Derecha." << endl;
            cout << " Seleccione una opcion => ";
            cin >> entrada;
            if (entrada == "1" || entrada == "2" || entrada == "3")
            {
                op = entrada[0] - '0';
            }
            else if (entrada == "4")
            {
                cout << "Opcion de movimiento no valida en este momento." << endl;
                op = 4;
            }
            else
            {
                cout << "Opcion no valida. Selecciona un numero." << endl;
                op = 0;
            }
        } while (op == 4 || op == 0);
    }
    else if (Assam.direccionMovimiento == 4)
    {
        do
        {
            cout << " (1) Arriba." << endl;
            cout << " (2) Abajo." << endl;
            cout << " (4) Izquierda." << endl;
            cout << " Seleccione una opcion => ";
            cin >> entrada;
            if (entrada == "1" || entrada == "2" || entrada == "4")
            {
                op = entrada[0] - '0';
            }
            else if (entrada == "3")
            {
                cout << "Opcion de movimiento no valida en este momento." << endl;
                op = 3;
            }
            else
            {
                cout << "Opcion no valida. Selecciona un numero." << endl;
                op = 0;
            }
        } while (op == 3 || op == 0);
    }

    cout << "Mover a Assam" << endl;
    cout << " Lanzando el dado ..." << endl;
    movimiento = lanzarDado();
    cout << " Resultado del dado: " << movimiento << endl;

    while (movimiento > 0)
    {
        if (op == 1)
        {
            if (jugador.posColumna == 0 && jugador.posFila == 0)
            {
                jugador.posColumna = 1;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 1 && jugador.posFila == 0)
            {
                jugador.posColumna = 0;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 2 && jugador.posFila == 0)
            {
                jugador.posColumna = 3;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 3 && jugador.posFila == 0)
            {
                jugador.posColumna = 2;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 4 && jugador.posFila == 0)
            {
                jugador.posColumna = 5;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 5 && jugador.posFila == 0)
            {
                jugador.posColumna = 4;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posFila > 0)
            {
                jugador.posFila--;
            }
        }
        else if (op == 2)
        {
            if (jugador.posColumna == 6 && jugador.posFila == 6)
            {
                jugador.posColumna = 5;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 5 && jugador.posFila == 6)
            {
                jugador.posColumna = 6;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 4 && jugador.posFila == 6)
            {
                jugador.posColumna = 3;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 3 && jugador.posFila == 6)
            {
                jugador.posColumna = 4;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 2 && jugador.posFila == 6)
            {
                jugador.posColumna = 1;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 1 && jugador.posFila == 6)
            {
                jugador.posColumna = 2;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posFila < 6)
            {
                jugador.posFila++;
            }
        }
        else if (op == 3)
        {
            if (jugador.posColumna == 6 && jugador.posFila == 0)
            {
                jugador.posColumna = 6;
                jugador.posFila = 0;
                op = 2;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 1)
            {
                jugador.posColumna = 6;
                jugador.posFila = 2;
                op = 4;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 2)
            {
                jugador.posColumna = 6;
                jugador.posFila = 1;
                op = 4;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 3)
            {
                jugador.posColumna = 6;
                jugador.posFila = 4;
                op = 4;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 4)
            {
                jugador.posColumna = 6;
                jugador.posFila = 3;
                op = 4;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 5)
            {
                jugador.posColumna = 6;
                jugador.posFila = 6;
                op = 4;
            }
            else if (jugador.posColumna == 6 && jugador.posFila == 6)
            {
                jugador.posColumna = 6;
                jugador.posFila = 5;
                op = 4;
            }
            else if (jugador.posColumna < 6)
            {
                jugador.posColumna++;
            }
        }
        else if (op == 4)
        {
            if (jugador.posColumna == 0 && jugador.posFila == 6)
            {
                jugador.posColumna = 0;
                jugador.posFila = 6;
                op = 1;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 5)
            {
                jugador.posColumna = 0;
                jugador.posFila = 4;
                op = 3;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 4)
            {
                jugador.posColumna = 0;
                jugador.posFila = 5;
                op = 3;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 3)
            {
                jugador.posColumna = 0;
                jugador.posFila = 2;
                op = 3;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 2)
            {
                jugador.posColumna = 0;
                jugador.posFila = 3;
                op = 3;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 1)
            {
                jugador.posColumna = 0;
                jugador.posFila = 0;
                op = 3;
            }
            else if (jugador.posColumna == 0 && jugador.posFila == 0)
            {
                jugador.posColumna = 0;
                jugador.posFila = 1;
                op = 3;
            }
            else if (jugador.posColumna > 0)
            {
                jugador.posColumna--;
            }
        }
        movimiento--;
    }

    cout << " Nueva posicion de Assam: (" << jugador.posFila << ", " << jugador.posColumna << ")" << endl;
    jugador.direccionMovimiento = op;
    return jugador;
}

bool esValida(int f1, int c1, int f2, int c2, int tableroJuego[7][7], int jugadorID)
{
    if (f1 < 0 || f1 >= 7 || c1 < 0 || c1 >= 7 || f2 < 0 || f2 >= 7 || c2 < 0 || c2 >= 7)
    {
        return false;
    }

    if ((tableroJuego[f1][c1] == jugadorID && tableroJuego[f2][c2] == jugadorID) ||
        (tableroJuego[f1][c1] == 1 && tableroJuego[f2][c2] == 1) ||
        (tableroJuego[f1][c1] == 2 && tableroJuego[f2][c2] == 2))
    {
        return false;
    }

    return true;
}

int colocarAlfombra(int tableroJuego[7][7], int posFila, int posColumna, int jugadorID)
{
    int opciones[12][4];
    int numOpciones = 0;

    if (esValida(posFila - 1, posColumna, posFila - 1, posColumna - 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila - 1;
        opciones[numOpciones][1] = posColumna;
        opciones[numOpciones][2] = posFila - 1;
        opciones[numOpciones][3] = posColumna - 1;
        numOpciones++;
    }

    if (esValida(posFila - 1, posColumna, posFila - 1, posColumna + 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila - 1;
        opciones[numOpciones][1] = posColumna;
        opciones[numOpciones][2] = posFila - 1;
        opciones[numOpciones][3] = posColumna + 1;
        numOpciones++;
    }

    if (esValida(posFila - 1, posColumna, posFila - 2, posColumna, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila - 1;
        opciones[numOpciones][1] = posColumna;
        opciones[numOpciones][2] = posFila - 2;
        opciones[numOpciones][3] = posColumna;
        numOpciones++;
    }

    if (esValida(posFila, posColumna - 1, posFila - 1, posColumna - 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila;
        opciones[numOpciones][1] = posColumna - 1;
        opciones[numOpciones][2] = posFila - 1;
        opciones[numOpciones][3] = posColumna - 1;
        numOpciones++;
    }

    if (esValida(posFila, posColumna - 1, posFila, posColumna - 2, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila;
        opciones[numOpciones][1] = posColumna - 1;
        opciones[numOpciones][2] = posFila;
        opciones[numOpciones][3] = posColumna - 2;
        numOpciones++;
    }

    if (esValida(posFila, posColumna - 1, posFila + 1, posColumna - 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila;
        opciones[numOpciones][1] = posColumna - 1;
        opciones[numOpciones][2] = posFila + 1;
        opciones[numOpciones][3] = posColumna - 1;
        numOpciones++;
    }

    if (esValida(posFila + 1, posColumna - 1, posFila + 1, posColumna, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila + 1;
        opciones[numOpciones][1] = posColumna - 1;
        opciones[numOpciones][2] = posFila + 1;
        opciones[numOpciones][3] = posColumna;
        numOpciones++;
    }

    if (esValida(posFila + 1, posColumna, posFila + 1, posColumna + 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila + 1;
        opciones[numOpciones][1] = posColumna;
        opciones[numOpciones][2] = posFila + 1;
        opciones[numOpciones][3] = posColumna + 1;
        numOpciones++;
    }

    if (esValida(posFila + 1, posColumna + 1, posFila, posColumna + 1, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila + 1;
        opciones[numOpciones][1] = posColumna + 1;
        opciones[numOpciones][2] = posFila;
        opciones[numOpciones][3] = posColumna + 1;
        numOpciones++;
    }

    if (esValida(posFila, posColumna + 1, posFila, posColumna + 2, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila;
        opciones[numOpciones][1] = posColumna + 1;
        opciones[numOpciones][2] = posFila;
        opciones[numOpciones][3] = posColumna + 2;
        numOpciones++;
    }

    if (esValida(posFila + 1, posColumna, posFila + 2, posColumna, tableroJuego, jugadorID))
    {
        opciones[numOpciones][0] = posFila + 1;
        opciones[numOpciones][1] = posColumna;
        opciones[numOpciones][2] = posFila + 2;
        opciones[numOpciones][3] = posColumna;
        numOpciones++;
    }

    cout << "Jugador " << jugadorID << ", estas son las opciones para colocar una alfombra:" << endl;
    for (int i = 0; i < numOpciones; i++)
    {
        cout << " (" << i + 1 << ") Desde (" << opciones[i][0] << ", " << opciones[i][1] << ") hasta ("
             << opciones[i][2] << ", " << opciones[i][3] << ")" << endl;
    }

    if (numOpciones == 0)
    {
        cout << "No hay posiciones validas para colocar una alfombra." << endl;
        return 0;
    }

    string entrada;
    int eleccion;
    do
    {
        cout << "Seleccione una opcion (1-" << numOpciones << "): ";
        cin >> entrada;
        if (entrada.length() == 1 && entrada[0] >= '1' && entrada[0] <= '0' + numOpciones)
        {
            eleccion = entrada[0] - '0';
        }
        else
        {
            cout << "Opcion no valida. Intente nuevamente ;C." << endl;
            eleccion = 0;
        }
    } while (eleccion < 1 || eleccion > numOpciones);

    int filaInicio = opciones[eleccion - 1][0];
    int columnaInicio = opciones[eleccion - 1][1];
    int filaFin = opciones[eleccion - 1][2];
    int columnaFin = opciones[eleccion - 1][3];

    tableroJuego[filaInicio][columnaInicio] = jugadorID;
    tableroJuego[filaFin][columnaFin] = jugadorID;

    cout << "Alfombra colocada desde (" << filaInicio << ", " << columnaInicio << ") hasta (" << filaFin << ", " << columnaFin << ")." << endl;

    return 2;
}

int calcularPago(int tableroJuego[7][7], int posFila, int posColumna, int jugadorID)
{
    int enemigoID = (jugadorID == 1) ? 2 : 1;

    if (tableroJuego[posFila][posColumna] == enemigoID) // Corrección: debe ser ==, no !=
    {
        int visitado[7][7] = {0};
        int cola[49][2];
        int inicio = 0, fin = 0;

        cola[fin][0] = posFila;
        cola[fin][1] = posColumna;
        fin++;
        visitado[posFila][posColumna] = 1;

        int pago = 1;
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (inicio < fin)
        {
            int fila = cola[inicio][0];
            int columna = cola[inicio][1];
            inicio++;

            for (int i = 0; i < 4; i++)
            {
                int nuevaFila = fila + dx[i];
                int nuevaColumna = columna + dy[i];

                if (nuevaFila >= 0 && nuevaFila < 7 && nuevaColumna >= 0 && nuevaColumna < 7)
                {
                    if (!visitado[nuevaFila][nuevaColumna] && tableroJuego[nuevaFila][nuevaColumna] == enemigoID)
                    {
                        visitado[nuevaFila][nuevaColumna] = 1;
                        cola[fin][0] = nuevaFila;
                        cola[fin][1] = nuevaColumna;
                        fin++;
                        pago++;
                    }
                }
            }
        }

        return pago;
    }

    return 0;
}
Jugador pagarAOponente(Jugador jugador, int cantidadMonedas)
{
    cout << jugador.nombreJugador << " tenía " << jugador.cantidadMonedas << " monedas. Debe pagar " << cantidadMonedas << "." << endl;
    jugador.cantidadMonedas -= cantidadMonedas;
    if (jugador.cantidadMonedas < 0)
    {
        jugador.cantidadMonedas = 0;
    }
    cout << "Ahora tiene: " << jugador.cantidadMonedas << " monedas." << endl;
    return jugador;
}

int validarTableroDeJuego(int tableroJuego[7][7])
{
    int contadorCasillasVacias = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (tableroJuego[i][j] == 0)
            {
                contadorCasillasVacias++;
            }
        }
    }
    return contadorCasillasVacias;
}

Jugador crearHassam()
{
    Jugador hassam;
    hassam.cantidadAlfombras = 0;
    hassam.cantidadMonedas = 0;
    hassam.colorAlfombra = " ";
    hassam.nombreJugador = "Assam";
    hassam.posColumna = 3;
    hassam.posFila = 3;
    return hassam;
}

void exportarInformacionPartida(Jugador jugador1, Jugador jugador2, int idGanador)
{
    ofstream archivoSalida("resultado_partida.txt");
    if (archivoSalida.is_open())
    {
        archivoSalida << "Nombre: " << jugador1.nombreJugador << ".........." << "Nombre: " << jugador2.nombreJugador << endl;
        archivoSalida << "Color: " << jugador1.colorAlfombra << ".........." << "Color: " << jugador2.colorAlfombra << endl;
        archivoSalida << "Cantidad de alfombras: " << jugador1.cantidadAlfombras << ".........." << "Cantidad alfombras: " << jugador2.cantidadAlfombras << endl;
        archivoSalida << "Cantidad de monedas: " << jugador1.cantidadMonedas << ".........." << "Cantidad monedas: " << jugador2.cantidadMonedas << endl;
        archivoSalida << endl;
        if (idGanador == 1)
        {
            archivoSalida << "El ganador es " << jugador1.nombreJugador << endl;
        }
        else if (idGanador == 2)
        {
            archivoSalida << "El ganador es " << jugador2.nombreJugador << endl;
        }
        else
        {
            archivoSalida << "Hubo un empate." << endl;
        }

        archivoSalida.close();
        cout << "Informacion exportada a resultado_partida.txt" << endl;
    }
    else
    {
        cout << "Error al crear el archivo de resultados." << endl;
    }
}

void imprimirTablero(int tableroJuego[7][7], int posFila, int posColumna, int direccionMovimiento, Jugador jugador1, Jugador jugador2)
{
    string colorJugador1 = codigoColor(jugador1.colorAlfombra, 1);
    string colorJugador2 = codigoColor(jugador2.colorAlfombra, 2);
    cout << "*" << endl;
    cout << "*     0 1 2 3 4 5 6 *" << endl;
    cout << "-------------------" << endl;
    for (int f = 0; f < 7; f++)
    {
        cout << "* " << f << " | ";
        for (int c = 0; c < 7; c++)
        {
            if (f == posFila && posColumna == c && direccionMovimiento == 1)
            {
                cout << "🠕" << " ";
            }
            else if (f == posFila && posColumna == c && direccionMovimiento == 2)
            {
                cout << "🠗" << " ";
            }
            else if (f == posFila && posColumna == c && direccionMovimiento == 3)
            {
                cout << "➞" << " ";
            }
            else if (f == posFila && posColumna == c && direccionMovimiento == 4)
            {
                cout << "🠔" << " ";
            }
            else if (tableroJuego[f][c] == 0)
            {
                cout << "_" << " ";
            }
            else
            {
                if (tableroJuego[f][c] == 1)
                {
                    cout << colorJugador1 << " ";
                }
                else if (tableroJuego[f][c] == 2)
                {
                    cout << colorJugador2 << " ";
                }
                else
                {
                    cout << tableroJuego[f][c] << " ";
                }
            }
        }
        cout << "*" << endl;
    }
    cout << "-------------------" << endl;
    cout << "*" << endl;
}

int calcularPuntos(int tableroJuego[7][7], Jugador jugador, int idJugador)
{
    int sumaPuntos = 0;
    for (int f = 0; f < 7; f++)
    {
        for (int c = 0; c < 7; c++)
        {
            if (tableroJuego[f][c] == idJugador)
            {
                sumaPuntos++;
            }
        }
    }
    return sumaPuntos + jugador.cantidadMonedas;
}

void iniciarJuego(int tableroJuego[7][7])
{
    cout << ".................................................................................." << endl;
    imprimirLogoMarrakech();
    cout << ".................................................................................." << endl;
    cout << "Bienvenido a Marrakech" << endl;

    Jugador jugador1, jugador2, Assam;

    cout << ".................................................................................." << endl;
    cout << "Jugador 1" << endl;
    jugador1 = capturarInformacionJugador();
    jugador1.posFila = 0;
    jugador1.posColumna = 0;

    cout << ".................................................................................." << endl;
    cout << "Jugador 2" << endl;
    jugador2 = capturarInformacionJugador();
    jugador2.posFila = 6;
    jugador2.posColumna = 6;

    while (jugador1.colorAlfombra == jugador2.colorAlfombra)
    {
        cout << ".................................................................................." << endl;
        cout << "Jugador 1 y 2 tienen el mismo color de alfombra. Vuelve a elegir los dos colores." << endl;
        cout << ".................................................................................." << endl;
        cout << "Alfombra Jugador 1" << endl;
        jugador1.colorAlfombra = elegirAlfombra();
        cout << ".................................................................................." << endl;
        cout << "Alfombra Jugador 2" << endl;
        jugador2.colorAlfombra = elegirAlfombra();
    }

    Assam = crearHassam();

    int ronda = 1;
    int monedasPagar = 0;

    while (validarTableroDeJuego(tableroJuego) > 0 && jugador1.cantidadMonedas > 0 && jugador2.cantidadMonedas > 0 && jugador1.cantidadAlfombras > 0 && jugador2.cantidadAlfombras > 0)
    {
        for (int turno = 1; turno <= 2; turno++)
        {
            cout << "................................... Ronda " << ronda << " ......................................" << endl;
            if (turno == 1)
            {
                cout << "Turno del jugador " << turno << " => " << jugador1.nombreJugador << endl;
            }
            else
            {
                cout << "Turno del jugador " << turno << " => " << jugador2.nombreJugador << endl;
            }

            imprimirTablero(tableroJuego, Assam.posFila, Assam.posColumna, Assam.direccionMovimiento, jugador1, jugador2);
            Assam = moverHassam(Assam);
            cout << ".................................................................................." << endl;
            cout << "Assam se encuentra ahora en (" << Assam.posFila << ", " << Assam.posColumna << ")." << endl;
            imprimirTablero(tableroJuego, Assam.posFila, Assam.posColumna, Assam.direccionMovimiento, jugador1, jugador2);

            // Verificar si Assam cae en una alfombra del oponente y manejar el pago
            if (tableroJuego[Assam.posFila][Assam.posColumna] != 0 && tableroJuego[Assam.posFila][Assam.posColumna] != turno)
            {
                cout << "Assam cayó en una casilla con valor: " << tableroJuego[Assam.posFila][Assam.posColumna] << endl;
                monedasPagar = calcularPago(tableroJuego, Assam.posFila, Assam.posColumna, turno);
                if (monedasPagar > 0)
                {
                    if (turno == 1)
                    {
                        cout << ".................................................................................." << endl;
                        cout << "Jugador 1 debe pagar $" << monedasPagar << " al jugador 2!" << endl;
                        jugador1 = pagarAOponente(jugador1, monedasPagar);
                        jugador2.cantidadMonedas += monedasPagar;
                    }
                    else
                    {
                        cout << ".................................................................................." << endl;
                        cout << "Jugador 2 debe pagar $" << monedasPagar << " al jugador 1!" << endl;
                        jugador2 = pagarAOponente(jugador2, monedasPagar);
                        jugador1.cantidadMonedas += monedasPagar;
                    }
                    // Mostrar actualización de monedas después del pago
                    cout << "Jugador 1 ahora tiene: " << jugador1.cantidadMonedas << " monedas." << endl;
                    cout << "Jugador 2 ahora tiene: " << jugador2.cantidadMonedas << " monedas." << endl;
                }
            }

            if (turno == 1 && jugador1.cantidadAlfombras > 0)
            {
            if (colocarAlfombra(tableroJuego, Assam.posFila, Assam.posColumna, turno) > 0)
            {
                jugador1.cantidadAlfombras -= 1;
            }
            }
        else if (turno == 2 && jugador2.cantidadAlfombras > 0)
        {
            if (colocarAlfombra(tableroJuego, Assam.posFila, Assam.posColumna, turno) > 0)
            {
                jugador2.cantidadAlfombras -= 1;
            }
        }

            else
            {
                cout << "No puede colocar más alfombras. Su número actual de alfombras es 0 :c." << endl;
            }

            imprimirTablero(tableroJuego, Assam.posFila, Assam.posColumna, Assam.direccionMovimiento, jugador1, jugador2);
            cout << ".................................................................................." << endl;
            cout << "Jugador 1 : " << jugador1.nombreJugador << ", Alfombras : " << jugador1.cantidadAlfombras << ", Monedas : " << jugador1.cantidadMonedas << endl;
            cout << "Jugador 2 : " << jugador2.nombreJugador << ", Alfombras : " << jugador2.cantidadAlfombras << ", Monedas : " << jugador2.cantidadMonedas << endl;

            if (jugador1.cantidadMonedas == 0 || jugador2.cantidadMonedas == 0)
            {
                cout << "El juego ha terminado." << endl;
                break;
            }
            else if (jugador1.cantidadAlfombras == 0 && jugador2.cantidadAlfombras == 0)
            {
                cout << "El juego ha terminado." << endl;
                break;
            }
        }
        ronda++;
    }

    int puntosJugador1 = calcularPuntos(tableroJuego, jugador1, 1);
    int puntosJugador2 = calcularPuntos(tableroJuego, jugador2, 2);
    if (puntosJugador1 > puntosJugador2)
    {
        cout << "Felicidades " << jugador1.nombreJugador << ". Ganaste el juego!" << endl;
        exportarInformacionPartida(jugador1, jugador2, 1);
    }
    else if (puntosJugador1 == puntosJugador2)
    {
        cout << "Hubo un empate :D." << endl;
        exportarInformacionPartida(jugador1, jugador2, 0);
    }
    else
    {
        cout << "Felicidades " << jugador2.nombreJugador << ". Ganaste el juego!" << endl;
        exportarInformacionPartida(jugador1, jugador2, 2);
    }

    cout << "Gracias por jugar Marrakech, Besitos." << endl;
}


void imprimirLogoMarrakech()
{
    cout << "   ##   ##   #   #####  #####    #   ##   ## ##### ###### ##   ##" << endl;
    cout << "   ### ###  # #  #   #  #   #   # #  ##  ##  ##    ##     ##   ##" << endl;
    cout << "   ## # ##  # #  #####  #####   # #  ####    ##### ##     #######" << endl;
    cout << "   ##   ## ##### ####   ####   ##### ##  ##  ##    ##     ##   ##" << endl;
    cout << "   ##   ## #   # #   ## #   ## #   # ##   ## ##### ###### ##   ##" << endl;
}
