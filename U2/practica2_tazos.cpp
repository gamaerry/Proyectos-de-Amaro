#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Tazo
{
    string name;
    string type;
    Tazo *bottom;
};

Tazo *push(Tazo *last, string name, string type)
{
    Tazo *newTazo = new Tazo;
    newTazo->name = name;
    newTazo->type = type;
    newTazo->bottom = last;
    return newTazo;
}

Tazo *pop(Tazo *last)
{
    Tazo *newLast = last->bottom;
    delete last;
    return newLast;
}

void print(Tazo *last)
{
    Tazo *aux = last;
    while(aux != nullptr) {
        //cout << "----------------------" << endl;
        cout << "[" << aux << "]" << endl;
        cout << aux->name << " - " << aux->type << endl;
        aux = aux->bottom;
    }
}

Tazo *fill()
{
    Tazo *last = nullptr;
    last = push(last, "Tazo1", "Normal");
    last = push(last, "Tazo2", "Normal");
    last = push(last, "Tazo3", "Dorado");
    last = push(last, "Tazo4", "Plateado");
    last = push(last, "Tazo5", "Normal");
    last = push(last, "Tazo6", "Plateado");
    last = push(last, "Tazo7", "Normal");
    last = push(last, "Tazo8", "Normal");
    last = push(last, "Tazo9", "Dorado");
    last = push(last, "Tazo10", "Normal");
    return last;
}

void jugar(Tazo *last)
{
    bool jugador1 = true;
    // Mientras haya tazos en la pila el juego sigue
    while(last != nullptr) {
        cout << endl << "Turno del Jugador " << (jugador1 ? "1" : "2") << " (Enter)" << endl;
        getchar();

        // Se simula la probabilidad de que el jugador le pegue a un tazo o dos
        int num = (rand() % 6) + 1;

        cout << "Resultado:" << num << endl;
        if(num == 1 || num == 6) {
            cout << "(*o*) Tiro fallido" << endl;
        } else {
            if(num == 3) {
                cout << "(^_^) Tiro critico (3 tazos)" << endl;
                last = pop(last);
                last = pop(last);
                last = pop(last);
            } else {
                cout << "('-') Tiro acertado" << endl;
                last = pop(last);
            }
        }

        print(last);

        jugador1 = !jugador1;
    }
}

int main()
{
    // Se llena la pila de tazos
    Tazo *last = fill();

    print(last);

    // Comienza el juego
    jugar(last);

    return 0;
}
