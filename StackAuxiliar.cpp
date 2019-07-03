#include "Common.h"
#include "StackAuxiliar.h"

struct Nodo {
    Node* valor; ///Un puntero a un nodo correspondiente a un arbol
    Nodo* siguiente; ///Si es el ultimo nodo va a apuntar a NULL
    ///No le puedo encajar el stackRepr porque no lo reconoce, esta mas abajo en el codigo
};


struct StackRepr {
    int size;
    Nodo* last;
};


Stack emptyS() {
    StackRepr* s = new StackRepr;
    s->last = NULL;
    s->size = 0;
    return s;
}

int sizeS(Stack s) {
    return s->size;
}

void pushS(Stack s, Node* x) {
    Nodo* n = new Nodo;
    n->valor = x;
    n->siguiente = s->last;
    s->last = n;
    s->size++;
}

int topS(Stack s) {
    return s->last->valor;
}

void popS(Stack s) {
    ///Nodo* tmp = new Nodo;
    ///tmp = s->last;
    ///No hace falta crear un nuevo nodo y guardarme el last, puedo apuntar directamente a last
    Nodo* tmp = s->last;
    ///s->last = last->siguiente; La unica forma de obtener last es por medio de s, no puedo
    ///preguntar cosas de last directamente
    s->last = s-> last->siguiente; ///Si, puedo hacer esto
    delete tmp;
    s->size--;
}

void destroyS(Stack s) {

    while(s->size > 0) {
        popS(s);
    };

    delete s;

}


