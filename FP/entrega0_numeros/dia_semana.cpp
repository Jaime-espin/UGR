/**
  * @file dia_semana.cpp
  * @brief Cálculo del día de la semana (Ej. 1.15)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que primero lea el día de la semana como un entero
  * de 0 (lunes) a 6 (domingo), a continuación un número de días que pasarán y
  * finalmente escriba el día de la semana que resultará.
  *
  * Por ejemplo, si estamos en miércoles lee 2, si decimos que pasan 8 días
  * escribirá 3 (que corresponde al jueves).
  *
  */
  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    int día, pasan;
    int result;

    cout<<"Intrduzca el día de la semana: "<<endl;
    cin>>día;
    cout<<"Intrduzca los días que pasan: "<<endl;
    cin>>pasan;

    result=(día+pasan)%6;
    cout<<"es el día: "<<result<<endl;

  }
