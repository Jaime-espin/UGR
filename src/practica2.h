#pragma once
#include <vector>

class Practica2 {
public: 
    void testProfe();
    [[nodiscard ]] double crearTestAleatorioAlgoritmoBasico(const int min, const int k);
    [[nodiscard ]] double crearTestAleatorioAlgoritmoDivideVenceras(const int min, const int k);
    


private: 
    std::vector<int> v {};

    int algoritmoObvio(const std::vector<int>& vec) const;
    void rellenarvector(std::vector<int>& vec, const int k, const int pivote);
    int aleatorio(const int min, const int max) const;
    int DivideyVenceras(const std::vector<int>& vec);
    int recursiva(const std::vector<int>& vec, int izq, int drch);
   
};