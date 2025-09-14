#include <iostream>
#include <cstdlib>

using namespace std;

int* init_arreglo(int tamano_inicial){
    int* arreglo = (int*)malloc(tamano_inicial * sizeof(int));
    for (int i = 0; i < tamano_inicial  ; i++){
        arreglo[i] = i;
    }
    return arreglo;
}

void mostrar_arreglo(int *arreglo, int tamano){
    cout << "\nEl tamaño del arreglo es: "<< tamano << endl;
    for (int i = 0; i < tamano; i++)
    {
        cout << "arreglo[" << i << "] = " << arreglo[i] << endl;
    }
}

int* nuevo_arreglo(int* arreglo, int tamano, int incremento){
    int* nuevo = (int*)realloc(arreglo, (tamano + incremento) * sizeof(int));
    //cout << tamano + incremento << "\n";
    if(incremento > 0){
        for (int i = 0; i < incremento ; i++){
            nuevo[tamano + i] = tamano + i;
        }
    }
    return nuevo;
}

int main()
{
    // variables necesarias
    int tamano = 5; //tamano inicial
    int *arreglo = init_arreglo(tamano);
    int opcion;
    string menu = "~ MENU ~\n1. Aumentar n elementos\n2. Disminuir m elementos\n3. Salir\n";
    
    // Inicio del ciclo
    do {
        mostrar_arreglo(arreglo, tamano);
        cout << menu;
        cin >> opcion;
        if(opcion == 1){
            int n;
            cout << "Ingrese n: ";
            cin >> n;
            arreglo = nuevo_arreglo(arreglo, tamano, n);
            tamano += n;
        } else if(opcion == 2){
            int m;
            cout << "Ingrese m: ";
            cin >> m;
            arreglo = nuevo_arreglo(arreglo, tamano,-1 * m);
            tamano -= m;
        } else if(opcion != 3){
            cout << "¡Opcion invalida!\n";
        }
    } while (opcion != 3);
    
    // Libera memoria
    free(arreglo);
    arreglo = nullptr;
    return 0;
}
