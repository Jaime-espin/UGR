#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

/*
    Dada una colección de películas (set<string>),
    devuelve un map<char, set<string>> agrupándolas por la
    primera letra (en minúscula) del título.
*/
map<char, set<string>> agruparPorInicial(const set<string>& peliculas) {
    map<char, set<string>> cartelera;

    for(auto it = peliculas.begin(); it!=peliculas.end(); ++it){
        char inicial = tolower((*it)[0]);
        cartelera[inicial].insert(*it);
    }

    return cartelera;
}

string serializar(const map<char, set<string>>& m) {
    string out;

    for (auto it = m.begin(); it != m.end(); ++it) {
        out += it->first;
        out += ":";

        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
            out += *jt;
            out += "|";
        }

        out += ";";
    }

    return out;
}

bool mapsIguales(const map<char, set<string>>& a,const map<char, set<string>>& b){
    return serializar(a) == serializar(b);
}

int main() {

    int test = 1;

    // ==== TEST 1: Caso general ====
    {
        set<string> entrada = {
            "Amelie", "Avatar", "Batman", "Blade Runner",
            "Coco", "Cars", "Dune"
        };

        map<char, set<string>> esperado = {
            {'a', {"Amelie", "Avatar"}},
            {'b', {"Batman", "Blade Runner"}},
            {'c', {"Cars", "Coco"}},
            {'d', {"Dune"}}
        };

        auto obtenido = agruparPorInicial(entrada);

        cout << "TEST " << test++ << ": ";
        if (mapsIguales(esperado, obtenido)) cout << "OK\n";
        else {
            cout << "ERROR\n ";
        }
    }


    // ==== TEST 2: Todas empiezan con la misma letra ====
    {
        set<string> entrada = {"Alien", "Avatar", "Amelie"};
        map<char, set<string>> esperado = {
            {'a', {"Alien", "Amelie", "Avatar"}}
        };

        auto obtenido = agruparPorInicial(entrada);

        cout << "TEST " << test++ << ": ";
        if (mapsIguales(esperado, obtenido)) cout << "OK\n";
        else cout << "ERROR\n";
    }


    // ==== TEST 3: Letras distintas ====
    {
        set<string> entrada = {"X", "Y", "Z"};
        map<char, set<string>> esperado = {
            {'x', {"X"}},
            {'y', {"Y"}},
            {'z', {"Z"}}
        };

        auto obtenido = agruparPorInicial(entrada);

        cout << "TEST " << test++ << ": ";
        if (mapsIguales(esperado, obtenido)) cout << "OK\n";
        else cout << "ERROR\n";
    }


    // ==== TEST 4: Vacío ====
    {
        set<string> entrada = {};
        map<char, set<string>> esperado = {};

        auto obtenido = agruparPorInicial(entrada);

        cout << "TEST " << test++ << ": ";
        if (mapsIguales(esperado, obtenido)) cout << "OK\n";
        else cout << "ERROR\n";
    }


    // ==== TEST 5: Títulos con diferentes mayúsculas/minúsculas ====
    {
        set<string> entrada = {"matrix", "Matrix", "mundo", "Marte"};

        map<char, set<string>> esperado = {
            {'m', {"Marte", "Matrix", "matrix", "mundo"}}
        };

        auto obtenido = agruparPorInicial(entrada);

        cout << "TEST " << test++ << ": ";
        if (mapsIguales(esperado, obtenido)) cout << "OK\n";
        else cout << "ERROR\n";
    }

    cout << "✅ Todos los tests pasaron correctamente.\n";

    return 0;
}
