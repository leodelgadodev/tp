#ifndef __MAP_H__
#define __MAP_H__

typedef int Key;
typedef int Value;

struct MapRepr; 
typedef struct MapRepr* Map; 

// Crea un diccionario vacío.
Map emptyM();

// Devuelve el tamaño del diccionario (cantidad de claves distintas).
int sizeM(Map m);

// Inserta una clave k en el diccionario asociada al valor v.
// Si la clave ya estaba, sobreescribe su valor.
void insertM(Map m, Key k, Value v);

// Si la clave está en el diccionario,
// devuelve true y modifica el valor del parámetro v
// para que sea el valor asociado a k.
//
// Si la clave no está en el diccionario,
// devuelve false.
bool lookupM(Map m, Key k, Value& v);

// Borra la clave k del diccionario.
// Nota: la clave puede no estar en el diccionario.
void removeM(Map m, Key k);

// Libera toda la memoria usada por el diccionario.
void destroyM(Map m);

#endif
