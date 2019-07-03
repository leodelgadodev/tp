///Stack utilizado solamente en la implementacion de InsertM de map (para realizar el balanceo segun prioridad).
///NO es accedido por ningun otro usuario, ni tampoco es accedido en el Main.
///Es un Stack implementado con linked list, y que guarda dentro de sus nodos, punteros a nodos de un arbol (el arbol del Map).

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
