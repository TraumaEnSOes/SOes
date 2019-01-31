/*
  Redondeo 'por arriba' de un número.
  Convertido a plantilla.
*/

#include <string>
#include <iostream>
#include <sstream>

template< typename T, typename STR = std::string > STR upround( const T &value, unsigned decimals, const char delimiter = '.' ) {
  std::basic_stringstream< typename STR::value_type > buffer;

  buffer << value;

  // `str( )` devuelve copias ... no vamos a estar todo el rato copiando cosas.
  STR workCopy( buffer.str( ) );

  // Buscamos la posición del punto decimal.
  auto posOfPoint = workCopy.find( delimiter );

  // Si es un número entero (sin punto), nada que hacer.
  if( posOfPoint == std::string::npos ) return workCopy;

  // Total de número a la derecha de la coma:
  auto workDecimals = workCopy.size( ) - 1 - posOfPoint;

  // Si hay menos decimales que los pedidos, nada que hacer.
  if( workDecimals < decimals ) return workCopy;

  // Recortamos la cadena.
  if( workDecimals > decimals ) workCopy.erase( workCopy.length( ) - ( workDecimals - decimals ) );
  
  // Trivial: el último dígito es != 9.
  if( workCopy.back( ) != '9' ) {
    ++( workCopy.back( ) );
  } else {
    // No trivial. El último dígito es un '9'. Es el caso 'chulo' :-)
    int pickup = 1;

    for( int idx = workCopy.length( ) - 1; idx >= 0; --idx ) {
      if( workCopy[idx] == delimiter ) continue;
      workCopy[idx] += pickup;
      if( workCopy[idx] > '9' ) {
        workCopy[idx] = '0';
        pickup = 1;
      } else {
        pickup = 0;
        break;
      }
    }

    // Ya terminamos con la cadena.
    // Si aún nos queda 1 por sumar, hay que añadir un número al principio.
    if( pickup ) workCopy.insert ( 0, 1, '1' );
  }

  return workCopy;
}

int main( ) {
  const auto testValue = 3.1415f;
  std::cout << "Valor de prueba: " << testValue << '\n';
  std::cout << upround( testValue, 2 ) << '\n';
  std::cout << upround( testValue, 3 ) << '\n';

  const auto testValue2 = 9.9999f;
  std::cout << "Valor de prueba: " << testValue2 << '\n';
  std::cout << upround( testValue2, 3 ) << '\n';
  std::cout << upround( testValue2, 4 ) << '\n';
  return 0;
}
