// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 4. Implementación de sistemas de tiempo real.
//
// Archivo: ejecutivo1.cpp
// Implementación del primer ejemplo de ejecutivo cíclico:
//
//   Datos de las tareas:
//   ------------
//   Ta.  T    C
//   ------------
//   A  400  100
//   B  800  120
//   C  200  40
//   D  200  30
//  -------------
//
//  Planificación (con Ts == 200 ms)
//  Ciclo principal dura 800ms (4 iteraciones de Ts)
//  *---------*----------*---------*--------*
//  | C D  A  | C D  B   | C D   A | C D    |
//  *---------*----------*---------*--------*
//  0         200        400       600      800
//
// Historial:
// Creado en Diciembre de 2017
//
//Preguntas:
//¿Cuál es el mínimo de tiempo de espera que queda al final de las iterciones del ciclo secundario con tu solución?
// El mínimo es 10
//¿Cuál es el máximo tiempo de espera que queda al final de las iteraciones del ciclo secundario con tu solución?
// El máximo es 130
// -----------------------------------------------------------------------------

#include <string>
#include <iostream> // cout, cerr
#include <thread>
#include <chrono>   // utilidades de tiempo
#include <ratio>    // std::ratio_divide

using namespace std ;
using namespace std::chrono ;
using namespace std::this_thread ;

// tipo para duraciones en segundos y milisegundos, en coma flotante:
//typedef duration<float,ratio<1,1>>    seconds_f ;
typedef duration<float,ratio<1,1000>> milliseconds_f ;

// -----------------------------------------------------------------------------
// tarea genérica: duerme durante un intervalo de tiempo (de determinada duración)

void Tarea( const std::string & nombre, milliseconds tcomputo )
{
   cout << "   Comienza tarea " << nombre << " (C == " << tcomputo.count() << " ms.) ... " ;
   sleep_for( tcomputo );
   cout << "fin." << endl ;
}

// -----------------------------------------------------------------------------
// tareas concretas del problema:

void TareaA() { Tarea( "A", milliseconds(100) );  }
void TareaB() { Tarea( "B", milliseconds(120) );  }
void TareaC() { Tarea( "C", milliseconds(40) );  }
void TareaD() { Tarea( "D", milliseconds(30) );  }

// -----------------------------------------------------------------------------
// implementación del ejecutivo cíclico:

int main( int argc, char *argv[] )
{
   // Ts = duración del ciclo secundario (en unidades de milisegundos, enteros)
   const milliseconds Ts_ms( 200 );

   // ini_sec = instante de inicio de la iteración actual del ciclo secundario
   time_point<steady_clock> ini_sec = steady_clock::now();

   while( true ) // ciclo principal
   {
      cout << endl
           << "---------------------------------------" << endl
           << "Comienza iteración del ciclo principal." << endl ;

      for( int i = 1 ; i <= 4 ; i++ ) // ciclo secundario (4 iteraciones)
      {
         cout << endl << "Comienza iteración " << i << " del ciclo secundario." << endl ;

         switch( i )
         {
            case 1 : TareaC(); TareaD(); TareaA(); break ; //Le sobra 30
            case 2 : TareaC(); TareaD(); TareaB(); break ; //Le sobra 10
            case 3 : TareaC(); TareaD(); TareaA(); break ; //Le sobra 30
            case 4 : TareaC(); TareaD();           break ; //Le sobra 130
         }

         // calcular el siguiente instante de inicio del ciclo secundario
         ini_sec += Ts_ms ;

         // esperar hasta el inicio de la siguiente iteración del ciclo secundario
         sleep_until( ini_sec );

         // instante real actual tras la espera
         time_point<steady_clock> fin_real_sec = steady_clock::now();
         
         // diferencia entre el instante real y el esperado
         milliseconds_f retraso_ms = fin_real_sec - ini_sec;
         cout << "Retraso al final del ciclo secundario: " << retraso_ms.count() << " ms." << endl;
      }
   }
}
