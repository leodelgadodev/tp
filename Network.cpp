#include "Common.h"
#include "Network.h"

struct NetworkRepr {
    Map flechas;
    Stack acciones;
};

Network emptyN() {
    NetworkRepr net = new NetworkRepr();
    net->flechas = emptyM();
    net->acciones = emptyS();
}

void addN(Network net, Id id) {
    insertM(net->flechas,id,id);
    pushS(net->acciones,id);
}

bool elemN(Network net, Id id) {

    Value v;
    return lookupM(net->flechas, id, v);
}

void connectN(Network net, Id id1, Id id2) {

    if (!connectedN(net, id1, id2)) {

    } ///Si ya estan conectados, no hacer nada, solo agregar a la pila.

    /// Inserto en la pila el elemento que se apunta a si mismo (tras seguir toda una linea de conexiones
    /// que parte de id1).
    ///pushS(net->acciones,x')

}

Id representante(Network net, Id id) {
    ///Sigue las flechas y denota el ultimo valor

    Id r;
    lookupM(net->flechas, id, r);

    while(id != r) {
        if = r;
        lookupM(net->flechas,id,r);
    }
    return r;
}

bool connectedN(Network net, Id id1, Id id2) {
    return representante(net, id1) == representante(net, id2);
}

void undoN(Network net) {
    COMPLETAR(undoN);
}

void destroyN(Network net) {
    destroyS(net->acciones);
    destroyM(net->flechas);

    delete net;
}
