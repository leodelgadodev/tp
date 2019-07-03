#include "Common.h"
#include "Map.h"
#include "StackAuxiliar.h"

typedef int Priority;

Priority randomPriority() {
    return rand();
}

struct Node {
    Key clave; ///Es un int pero mas disfrazado
    Value valor; ///Este tambien es un int
    Priority prioridad; ///Un int que es un numero al azar
    Node* hijoIzq;
    Node* hijoDer;
};

//typedef Node* Tree;

struct MapRepr {
    Node* raiz;
    int tam;
};


Map emptyM() {
    MapRepr* m = new MapRepr;
    m->raiz = NULL;
    m->tam = 0;
}

int sizeM(Map m) {
    return m->tam;
}

Priority prioridadDe(Node* n) {
    return n->prioridad;
}

bool lookupM(Map m, Key k, Value& v) {
    ///Denota True si existe una clave k asociada con valor v
    ///Recorre el map segun invariante de BST
    ///Recorre el arbol y se guarda el nodo (si no existe, se guarda NULL)
    ///Y despues compara, primero si es null, y despues si corresponde el valor
    Node* tmp = m->raiz;
    bool ret = false;

    while ( tmp != NULL && tmp->clave != k  ) {
        if ( k > tmp->clave ) {

        tmp = tmp->hijoDer;
        } else {

        tmp = tmp->hijoIzq;
        }
    }

    if ( tmp != NULL ) {
        ///Si existe, debe modificar el valor
        //tmp->valor = v;
        v = tmp->valor;
        ret = true;
        //ret = (tmp->clave == k) && (tmp->valor == v);
    }

    return ret;

}



/// ////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////
/// ///////////////////////////////// INSERTAR /////////////
/// ////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////


Node* insertarHoja(Key k, Value v) {
    ///Crea un nuevo nodo con las siguientes cosas:
    ///Esta funcion es invocada cuando en el algo. de insert por BST llego a la posicion a la que quiero insertar
    Node* n = new Node;
    n->clave = k;
    n->valor = v;
    n->prioridad = randomPriority();
    n->hijoIzq = NULL;
    n->hijoDer = NULL;
    return n;
}

///Necesito cambiar esto por las implementaciones de rotacion con void DDDD:  DUGLAAASSSS
Node* rotacionIzq(Node*& n) {
    Node* tmp = n->hijoDer;
    n->hijoDer = tmp->hijoIzq;
    tmp->hijoIzq = n;

    //return tmp;
}

Node* rotacionDer(Node*& n) {
    Node* tmp = n->hijoIzq;
    n->hijoIzq= tmp->hijoDer;
    tmp->hijoDer = n;

    //return tmp;
}

bool nodosOrdenados(Node* padre) {
    ///Denota true si la prioridad del nodo que recibe como parametro es mayor a la de sus hijos
    bool ret = true;

    if (padre->hijoDer != NULL ) {
        ret = ret && prioridadDe(padre) > prioridadDe(padre->hijoDer);
    }

    if (padre->hijoIzq != NULL) {
        ret = ret && prioridadDe(padre) > prioridadDe(padre->hijoIzq);
    }

    return ret;
}

Stack caminoHastaNodoInsertado(Map m, Node* insertado) {
    ///Denota un Stack de node* que corresponden a todos los nodos desde la raiz hasta el ultimo nodo que inserte
    ///Precondicion: el nodo que inserte ya esta en el map
    Node* tmp = m->raiz;
    Stack ret = emptyS();
    pushS(ret,tmp);

    while(tmp->clave != insertado->clave) {

        ///Nunca llega a un null, entonces no hace falta comprobar si el hijo es null
        if (insertado->clave > tmp->clave) {
            pushS(ret,tmp->hijoDer);
            tmp = tmp->hijoDer;
        } else {
            pushS(ret,tmp->hijoIzq);
            tmp = tmp->hijoIzq;
        }
    }

    return ret;
}

Node* segundoTop( Stack s ) {
///Denota el top que queda de hacer popS
///Vuelve a dejar el stack como estaba
    Node* tmp;
    Node* tmpPush = topS(s);
    popS(s);
    tmp = topS(s);
    pushS(s,tmpPush);
    delete tmpPush;
    return tmp;
}

void balancear(Map m, Node* insertado) {
/// ORDENAR SIGNIFICA, UNA VEZ QUE INSERTE UN NUEVO NODO CON UNA NUEVA PRIORIDAD, COMPARO CON LA PRIORIDAD DE SU PADRE

/// Voy hasta el padre del nodo que inserte y comparo prioridades. Si su hijo tiene menor prioridad, listo, ya esta. Sino:

/// Si es su hijo izq, efectuar rotacion der. Si es su hijo der, efectuar rotacion izq.

/// Ahora tengo que comparar con el abuelo original del nodo que inserte (ahora es el padre directo). Y verificar nuevamente las prioridades.

/// Voy a tener que ir comparando constantemente con los antecesores del nodo que inserte. En el peor caso tiene mayor prioridad que la raiz

/// Una opcion puede ser, que la comparacion de ordenamiento le pase una clave (el padre) y que de ahi compare todo
/// guardandome en algun lado una lista de todas las claves desde la raiz hasta el padre del insertado
/// y pasandole constantemente esa funcion hasta que quede ordenado.

/// <??> Puedo importar un stack para resolver esto?
/// El stack que ya existe es un stack de int, no un stack de punteros. Puedo crear un stack de punteros para resolver esto?
/// Si no, entonces necesito una fuc. auxiliar que le de una clave y me devuelva un Node* y todo funcionaria de la misma forma
    Stack claves = caminoHastaNodoInsertado(m, insertado);
    int iter = sizeS(claves); ///Usado en caso de que destruya el stack
    Node* tmp = topS(claves);
    Node* tmpPadre = segundoTop(claves));

    while ( iter > 1 ) {
        if( nodosOrdenados(tmpPadre) ) {
            iter = 0;
        } else {
            if (tmpPadre->clave < tmp->clave) {
                ///Osea, si el que tengo que rotar es su hijo der
                rotacionIzq(tmpPadre);
                } else {
                rotacionDer(tmpPadre);
                }

            iter--;
            popS(claves);
            popS(claves);
            pushS(claves,tmp);
            tmp = topS(claves);
            tmpPadre = segundoTop(claves));
        }
    }

    destroyS(claves);
    delete claves; ///Depende de si puedo crear un stack con punteros o usar el stack con ints, uso esto o no.
    ///delete iter; Solo hago delete a referencias o punteros. Variables que guardan un valor normal no se hace delete.
    delete tmp; ///idem claves
    delete tmpPadre; ///idem claves

//    if ( !nodosOrdenados(tmpPadre,tmp) ) {
//     ///Ultimo caso fuera del while (porque me quedaron dos nodos en el stack)
//        if (tmpPadre->clave < tmp->clave) {
//                ///Osea, si el que tengo que rotar es su hijo der
//                rotacionIzq(tmpPadre);
//            } else {
//                rotacionDer(tmpPadre);
//            }
//    }
}




void insertM(Map m, Key k, Value v) {
    ///Nodo para insertar
//    Node* n = new Node;
//    n->clave = k;
//    n->valor = v;
//    n->prioridad = randomPriority();
//    n->hijoIzq = NULL;
//    n->hijoDer = NULL;

    ///Map
    ///Al final de la insercion, en el caso de que no tengo exista ya el nodo, tengo que hacer:
    ///m->tam++;

    ///Insert BST -
    Node* tmp = m->raiz;
    Node* padreTmp = NULL;

    while ( tmp != NULL && tmp->clave != k  ) {
    ///Esto me posiciona el puntero tmp en el lugar en donde deberia insertar un nuevo nodo
    ///Corta cuando encuentro el nodo con la clave, o cuando encuentro el nodo en NULL

        Node* padreTmp = tmp; /// <??> Funciona? Me estoy intentando guardar el padre

    ///tmp se guarda una referencia al nodo. Si modifico tmp, modifico tambien el nodo (NO es una deep copy)
        if ( k > tmp->clave ) {
            tmp = tmp->hijoDer;
        } else {
            tmp = tmp->hijoIzq;
        }
    }

    if ( tmp->clave != NULL ) {
    ///Si NO es null, entonces ya existe el nodo con la clave, pero con otro valor, y finaliza el insert
        tmp->valor = v;
    } else {
        tmp = insertarHoja(k, v);
        balancear(m, tmp);
    }
    delete tmp;
    delete padreTmp;
}







void removeM(Map m, Key k) {

    //COMPLETAR(removeM);
}

void _destroyM(Node* raiz) {
///Implementacion parcial
///Destruye el arbol que inicie con la raiz
    if( raiz->hijoIzq != NULL) {
        _destroyM(raiz->hijoIzq);
    }

    if( raiz->hijoDer != NULL ) {
        _destroyM(raiz->hijoDer);
    }

    delete raiz;
}

void destroyM(Map m) {

    while(m->raiz != NULL) {
        _destroyM(m->raiz);
    }

    delete m;
}



