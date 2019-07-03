#ifndef __NETWORK_H__
#define __NETWORK_H__

struct NetworkRepr; 
typedef struct NetworkRepr* Network;

typedef int Id;

// Crea una red vacía.
Network emptyN();

// Agrega un elemento a la red, con el identificador 'id'.
//
// Precondición: el elemento no está en la red aún.
void addN(Network net, Id id);

// Devuelve verdadero si el elemento está en la red.
bool elemN(Network net, Id id);

// Establece una conexión *directa* entre dos elementos de la red.
// Si los elementos ya están conectados (ya sea directa o indirectamente),
// esta acción no tiene efecto.
//
// Precondición: id1 e id2 identifican a dos elementos de la red.
void connectN(Network net, Id id1, Id id2);

// Devuelve verdadero si id1 e id2 identifican a dos elementos
// de la red que están conectados, ya sea directa o indirectamente.
//
// Precondición: id1 e id2 identifican a dos elementos de la red.
bool connectedN(Network net, Id id1, Id id2);

// Deshace la última acción (agregar un elemento o conectar dos
// elementos).
//
// Precondición: debe haber habido una última acción.
void undoN(Network net);

// Libera toda la memoria usada por la red.
void destroyN(Network net);

#endif