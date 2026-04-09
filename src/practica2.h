#pragma once
#include <vector>

class Practica2 {
public: 
    void testProfe();
    void crearTestAleatorioAlgoritmoBasico(const int min, const int max);
    


private: 
    std::vector<int> v {};

    int algoritmoObvio(const std::vector<int>& vec, const int k) const;
    void rellenarvector(std::vector<int>& vec, const int k, const int pivote);
    int aleatorio(const int min, const int max) const;
   
};