#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

const int MAX_SIZE = 1024;

struct pila
{
    char nombre[MAX_SIZE];
    pila *bottom;
};

pila *push(pila *last)
{
    pila *nueva = (pila*)malloc(sizeof(pila));
    if(nueva == nullptr) {
        cerr << "Error en la reserva de memoria" << endl;
    } else {
        cout << "Ingrese nombre: " << endl;
        cin >> ws;
        cin.getline(nueva->nombre, MAX_SIZE);

        nueva->bottom = last;
    }
    return nueva;
}

pila *pop(pila *last)
{
    pila *aux = last->bottom;

    free(last);

    return aux;
}

pila* limpiar (pila* last) {
    while(last != nullptr){
        last=pop(last);
    }
    return nullptr;
}

void show(pila *last)
{
    pila *aux = last;
    while(aux != nullptr) {
        cout << "==============" << endl;
        cout << "| Dir actual: " << aux << endl;
        cout << "| Nombre: " << aux->nombre << endl;
        cout << "| ------------" << endl;
        cout << "| Debajo: " << aux->bottom << endl; 
        cout << "==============" << endl;
        aux = aux->bottom;
    }
}

void menu()
{
    pila *last = nullptr;
    int opcion = 5;
    do {
        cout << "Ingrese opcion: " << endl;
        cout << "1. Ingresar elemento a la pila" << endl;
        cout << "2. Mostrar la pila" << endl;
        cout << "3. Quitar el utilmo elemento" << endl;
        cout << "4. Limpiar pila" << endl;
        cout << "5. Salir" << endl;
        cin >> opcion;

        if(opcion == 1) {
            last = push(last);
        } else if(opcion == 2) {
            show(last);
        } else if(opcion == 3) {
            last = pop(last);
        } else if(opcion == 4) {
            last = limpiar(last);
        } else if(opcion == 5 && last != nullptr) {
            cout << "Pila no vacia! Se ha vaciado automáticamente";
            last = limpiar(last);
        }
    } while(opcion != 5);
}

int main()
{
    menu();

    return 0;
}
