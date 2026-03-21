#include "tiempo.h"
#include "registro.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Pruebas del módulo tiempo:" << endl;
    cout << "------------------------" << endl;

    // Crear instancias de tiempo para pruebas
    Tiempo t1 = {2, 30, 45};  // 02:30:45 (entrada)
    Tiempo t2 = {3, 15, 20};  // 03:15:20 (salida)

    // Prueba de toStringT
    cout << "Tiempo t1 = " << toStringT(t1) << endl;
    cout << "Tiempo t2 = " << toStringT(t2) << endl;

    // Prueba de TiempoEnSegundos
    cout << "t1 en segundos = " << TiempoEnSegundos(t1) << " segundos" << endl;
    
    // Prueba de segundosEnTiempo
    int segundos = 9000; // 2h 30m
    Tiempo t3 = segundosEnTiempo(segundos);
    cout << segundos << " segundos = " << toStringT(t3) << endl;
    
    // Prueba de esPosterior
    cout << "¿Es t2 posterior a t1? " << (esPosterior(t2, t1) ? "Sí" : "No") << endl;
    
    // Prueba de sonIguales
    Tiempo t4 = {2, 30, 45}; // igual a t1
    cout << "¿Son t1 y t4 iguales? " << (sonIguales(t1, t4) ? "Sí" : "No") << endl;
    
    // Prueba de calcularNuevoTiempo
    Tiempo t5 = calcularNuevoTiempo(t1, 3600); // Añadir 1 hora
    cout << "t1 + 1 hora = " << toStringT(t5) << endl;

    cout << "\nPruebas del módulo registro:" << endl;
    cout << "---------------------------" << endl;

    // Crear registros para pruebas (tentrada, tsalida, matricula)
    Registro r1 = {t1, t2, "1234ABC"};
    Registro r2 = {t2, t1, "5678XYZ"}; // Este tiene los tiempos invertidos

    // Prueba de toStringR
    cout << "r1 = " << toStringR(r1) << endl;
    cout << "r2 = " << toStringR(r2) << endl;
    
    // Prueba de corrigeRegistro para r2 (tiene los tiempos invertidos)
    cout << "\nCorrigiendo r2..." << endl;
    Registro r2Corregido = r2;
    corrigeRegistro(r2Corregido);
    cout << "r2 original = " << toStringR(r2) << endl;
    cout << "r2 corregido = " << toStringR(r2Corregido) << endl;
    
    // Prueba de tiempoEnTramo
    cout << "\nTiempo en tramo r1 = " << tiempoEnTramo(r1) << " minutos" << endl;
    
    // Prueba de velocidadPromedio
    cout << "Velocidad promedio r1 = " << velocidadPromedio(r1) << " km/h" << endl;
    
    // Prueba de controlVehiculo
    cout << "\nControl de vehículo r1:\n" << controlVehiculo(r1) << endl;
    
    // Prueba de extraerDatos
    cout << "\nPrueba de extraerDatos:" << endl;
    // Crear un ControlDiario con algunos registros
    ControlDiario control;
    control.util = 2;
    control.conjunto[0] = r1;
    control.conjunto[1] = r2;
    
    // Crear contenedores para multas y no multas
    ControlDiario multas, noMultas;
    multas.util = 0;
    noMultas.util = 0;
    
    // Extraer datos
    extraerDatos(control, multas, noMultas);
    
    // Mostrar resultados
    cout << "Vehículos con multa: " << multas.util << endl;
    cout << "Vehículos sin multa: " << noMultas.util << endl;
    
}
