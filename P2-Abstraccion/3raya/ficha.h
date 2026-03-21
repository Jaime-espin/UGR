
#ifndef __FICHA__H__
#define __FICHA__H__

/* ***************************************** */

#include <iostream>

/* ***************************************** */

/**
 * @brief Tipo enumerado que contiene las fichas que se usan.
 */ 
enum Ficha {BLANCO, CIRCULO, CRUZ};

/* ***************************************** */

/**
 * @brief Sobrecarga del operador de inserción << para imprimir una ficha.
 * Escribe en el flujo de salida el símbolo asociado a la ficha proporcionada.
 * @param salida Flujo de salida en el que se mostrará el símbolo de la ficha.
 * @param fic    Referencia constante a la ficha que se desea imprimir.
 * @return Una referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream &salida, const Ficha &fic);

/* ***************************************** */

#endif
