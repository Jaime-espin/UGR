#include <list>
#include <cassert>
#include <iostream>

using namespace std;

bool hayMontana(const list<int>& L) {
    if(L.size()<3){ return false;}

    bool hasubido=false;
    bool habajado=true;

    list<int>::const_iterator it = L.begin();
    list<int>::const_iterator next = it;
    next++;

    //Tiene que empezar subiendo, por lo que el primer objeto de la lista debe ser menor al siguiente
    if(*it<*next){
        hasubido=true;
    }
    //Sigo comprobando que sigue subiendo
    for(it; it!=L.end(); it++){
        if(*it>*next){
            it++;
            next++;
            break;
        }else if(*it==*next){
            hasubido=false;
        }
        next++;
    }


    //Ahora compruebo si baja
    if(hasubido){   //Solo puede bajar si antes subió
        for(it; it!=--L.end(); it++){
            if(*it<=*next){
                habajado=false;
                break;
            }
            next++;
        }
    }

    //Compobamos que ha subido y que ha bajado una única vez y que el iterador llegó al final de la lista
    if(hasubido && habajado && it==--L.end()){
        return true;
    }else{
        return false;
    }

}

int main() {

    {   // Sí hay montaña
        cout << "Pasando el primer test ⏳" << endl;
        list<int> L = {1,3,6,4,2};
        assert(hayMontana(L) == true);
    }
    {   // No (solo sube)
        cout << "Pasando el segundo test ⏳" << endl;
        list<int> L = {1,2,3,4};
        assert(hayMontana(L) == false);
    }
    {   // No (solo baja)
        cout << "Pasando el tercer test ⏳" << endl;
        list<int> L = {9,7,4,3};
        assert(hayMontana(L) == false);
    }
    {   // Sí, aunque haya más cosas después
        cout << "Pasando el cuarto test ⏳" << endl;
        list<int> L = {2,4,9,5,7,8};
        assert(hayMontana(L) == false);
    }
    {   // No (plano)
        cout << "Pasando el quinto test ⏳" << endl;
        list<int> L = {1,3,3,2};
        assert(hayMontana(L) == false);
    }
    {   // Sí, montaña mínima de 3 elementos
        cout << "Pasando el sexto test ⏳" << endl;
        list<int> L = {1,3,2};
        assert(hayMontana(L) == true);
    }
    {   // Menos de 3 elementos
        cout << "Pasando el séptimo test ⏳" << endl;
        list<int> L = {1,3};
        assert(hayMontana(L) == false);
    }

    cout << "Se han pasado TODOS los test. Enhorabuena! ✅\n";
    return 0;
}

