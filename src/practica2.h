#pragma once
#include <vector>

class Practica2 {
public: 
    void testProfe();
    [[nodiscard ]] double crearTestAlgoritmoBasico(const int k);
    [[nodiscard ]] double crearTestAleatorioAlgoritmoDivideVenceras(const int k);
    


private: 
    std::vector<int> v {};
    
    int algoritmoObvio(const std::vector<int>& vec) const;
    void rellenarvector(std::vector<int>& vec, const int k, const int pivote);
    int DivideyVenceras(const std::vector<int>& vec, int izq, int drch);
   
};