#pragma once
#include <vector>

enum class EscenarioPivote { //Creo el enum para elegir el escenario
    PeorCaso,
    MejorCaso,
    Medio
};

class Practica2 {
public: 
    void testProfe();
    double crearTestAlgoritmoBasico(const int k, EscenarioPivote escenario = EscenarioPivote::PeorCaso); //Añado argumento a los test
    double crearTestAleatorioAlgoritmoDivideVenceras(const int k, EscenarioPivote escenario = EscenarioPivote::PeorCaso); //Añado argumento a los test
    


private: 
    std::vector<int> v {};
    int seleccionarPivote(const int k, EscenarioPivote escenario) const; //Núevo método para seleccionar el pivote si el escenario es medio
    
    int algoritmoObvio(const std::vector<int>& vec) const;
    void rellenarvector(std::vector<int>& vec, const int k, const int pivote);
    int DivideyVenceras(const std::vector<int>& vec, int izq, int drch);
   
};