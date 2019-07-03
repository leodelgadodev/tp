#ifndef __STACK_H__
#define __STACK_H__

struct StackRepr; 
typedef struct StackRepr* Stack;

// Crea una pila vacía.
Stack emptyS();

// Apila un elemento.
void pushS(Stack s, int x);

// Tamaño de la pila.
int sizeS(Stack s);

// Devuelve el tope de la pila.
// Pre: la pila no está vacía.
int topS(Stack s);

// Desapila el tope de la pila.
// Pre: la pila no está vacía.
void popS(Stack s);

// Libera toda la memoria usada por la pila.
void destroyS(Stack s);

#endif
