#include <iostream>
#include <cassert>
#include <cstdlib>
#include "maxqueue.h"

using namespace std;

bool hayPrecioJusto(MaxQueue q, int precioJusto) {
    bool hay=false;
    while(!q.empty()){
        int sum=0;
        MaxQueue aux=q;
        while(!aux.empty()){
            sum+=aux.front().value;
            aux.pop();
            if(sum==precioJusto){
                hay = true;
                break;
            } else if(sum>precioJusto){
                break;
            }
        }
        if(hay){
            break;
        }
        q.pop();
    }
    return hay;
}


int main() {
    MaxQueue q;

    // 🧪 Test 1: Secuencia exacta en el medio → true
    q.push(2); q.push(4); q.push(3); q.push(5); q.push(1);
    assert(hayPrecioJusto(q, 8) == true); // 3 + 5 = 8
    while (!q.empty()) q.pop();

    // 🧪 Test 2: Secuencia al inicio → true
    q.push(4); q.push(1); q.push(2); q.push(7);
    assert(hayPrecioJusto(q, 5) == true); // 4 + 1 = 5
    while (!q.empty()) q.pop();

    // 🧪 Test 3: Secuencia al final → true
    q.push(1); q.push(2); q.push(3); q.push(4);
    assert(hayPrecioJusto(q, 7) == true); // 3 + 4 = 7
    while (!q.empty()) q.pop();

    // 🧪 Test 4: No hay secuencia → false
    q.push(1); q.push(1); q.push(1); q.push(1);
    assert(hayPrecioJusto(q, 5) == false);
    while (!q.empty()) q.pop();

    // 🧪 Test 5: Toda la cola suma justo → true
    q.push(2); q.push(3); q.push(5);
    assert(hayPrecioJusto(q, 10) == true); // 2 + 3 + 5 = 10
    while (!q.empty()) q.pop();

    // 🧪 Test 6: Cola vacía → false
    assert(hayPrecioJusto(q, 5) == false);


    // 🧪 Test 7: Secuencia no continua → false
    q.push(1); q.push(2); q.push(10); q.push(0); q.push(2); q.push(8); q.push(20);
    assert(hayPrecioJusto(q, 18) == false); // No está de manera consecutiva
    while (!q.empty()) q.pop();

    cout << "✅ Todos los tests de precioJusto pasaron correctamente." << endl;
    return 0;
}
