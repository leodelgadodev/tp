#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

#define TEST(NOMBRE, CUERPO) \
	void NOMBRE() { \
		string test = #NOMBRE; \
		cout << "[ TEST   ] " << test << endl; \
		{ CUERPO } \
		cout << "[     OK ] " << test << endl; \
	}

#define ASSERT_EQ(EXPR, EXPECTED) { \
	__typeof__(EXPECTED) expected = (EXPECTED); \
	__typeof__(EXPR) obtained = (EXPR); \
	if (expected != obtained) { \
		cout << "[    MAL ] " << test << endl; \
		cout << endl; \
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; \
		cout << "FALLA EL TEST \"" << test << "\"" << endl; \
		cout << "Al evaluar:" << endl; \
		cout << "    " << #EXPR << endl; \
		cout << "Se esperaba obtener el valor:" << endl; \
		cout << "    " << expected << endl; \
		cout << "Pero se obtuvo:" << endl; \
		cout << "    " << obtained << endl; \
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl; \
		exit(1); \
	} \
}

/***************************** Tests de Stack *****************************/

#include "Stack.h"

TEST(testStackEmpty, {
	Stack s = emptyS();
	ASSERT_EQ(sizeS(s), 0);
	destroyS(s);
})

TEST(testStackPush, {
	Stack s = emptyS();
	ASSERT_EQ(sizeS(s), 0);
    pushS(s, 100);
	ASSERT_EQ(sizeS(s), 1);
    pushS(s, 200);
	ASSERT_EQ(sizeS(s), 2);
    pushS(s, 300);
	ASSERT_EQ(sizeS(s), 3);
	destroyS(s);
})

TEST(testStackTop, {
	Stack s = emptyS();
	ASSERT_EQ(sizeS(s), 0);
    pushS(s, 100);
	ASSERT_EQ(sizeS(s), 1);
	ASSERT_EQ(topS(s), 100);
    pushS(s, 200);
	ASSERT_EQ(sizeS(s), 2);
	ASSERT_EQ(topS(s), 200);
    pushS(s, 300);
	ASSERT_EQ(sizeS(s), 3);
	ASSERT_EQ(topS(s), 300);
	destroyS(s);
})

TEST(testStackPop, {
	Stack s = emptyS();
	ASSERT_EQ(sizeS(s), 0);
    pushS(s, 100);
	ASSERT_EQ(sizeS(s), 1);
	ASSERT_EQ(topS(s), 100);
    pushS(s, 200);
	ASSERT_EQ(sizeS(s), 2);
	ASSERT_EQ(topS(s), 200);
    pushS(s, 300);
	ASSERT_EQ(sizeS(s), 3);
	ASSERT_EQ(topS(s), 300);
    popS(s);
	ASSERT_EQ(sizeS(s), 2);
	ASSERT_EQ(topS(s), 200);
    popS(s);
	ASSERT_EQ(sizeS(s), 1);
	ASSERT_EQ(topS(s), 100);
    popS(s);
	ASSERT_EQ(sizeS(s), 0);
	destroyS(s);
})

TEST(testStackStress, {
	Stack s = emptyS();
    for (int i = 0; i < 1000; i++) {
        int j = (i * i - 100 * i + 7) % 997;
	    ASSERT_EQ(sizeS(s), i);
        pushS(s, j);
	    ASSERT_EQ(sizeS(s), i + 1);
	    ASSERT_EQ(topS(s), j);
    }
    for (int i = 999; i >= 0; i--) {
        int j = (i * i - 100 * i + 7) % 997;
	    ASSERT_EQ(sizeS(s), i + 1);
	    ASSERT_EQ(topS(s), j);
        popS(s);
	    ASSERT_EQ(sizeS(s), i);
    }
	destroyS(s);
})

void correrTestsStack() {
	cout << "[========] Testeando el tipo Stack." << endl;
	testStackEmpty();
	testStackPush();
	testStackTop();
	testStackPop();
	testStackStress();
	cout << "[========] Todos los tests de Stack OK." << endl;
}

/***************************** Tests de Map *****************************/

#include "Map.h"

bool elemM(Map m, Key k) {
    Value v;
    return lookupM(m, k, v);
}

Value valueM(Map m, Key k) {
    Value v;
    lookupM(m, k, v);
    return v;
}

TEST(testMapEmpty, {
	Map m = emptyM();
	ASSERT_EQ(sizeM(m), 0);
	destroyM(m);
})

// Inserta tres números.
TEST(testMapInsert, {
	Map m = emptyM();
	ASSERT_EQ(sizeM(m), 0);
	ASSERT_EQ(elemM(m, 10), false);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), false);

    insertM(m, 10, 10);
	ASSERT_EQ(sizeM(m), 1);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), false);
	ASSERT_EQ(valueM(m, 10), 10);

    insertM(m, 10, 11);
	ASSERT_EQ(sizeM(m), 1);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), false);
	ASSERT_EQ(valueM(m, 10), 11);

    insertM(m, 20, 11);
	ASSERT_EQ(sizeM(m), 2);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), false);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 11);

    insertM(m, 30, 11);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 11);
	ASSERT_EQ(valueM(m, 30), 11);

    insertM(m, 20, 12);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 12);
	ASSERT_EQ(valueM(m, 30), 11);

    insertM(m, 30, 12);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 12);
	ASSERT_EQ(valueM(m, 30), 12);

    insertM(m, 30, 13);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 12);
	ASSERT_EQ(valueM(m, 30), 13);

	destroyM(m);
})

TEST(testMapRemove, {
	Map m = emptyM();

    insertM(m, 30, 13);
    insertM(m, 20, 12);
    insertM(m, 10, 11);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 12);
	ASSERT_EQ(valueM(m, 30), 13);

    removeM(m, 40);
	ASSERT_EQ(sizeM(m), 3);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), true);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 20), 12);
	ASSERT_EQ(valueM(m, 30), 13);

    removeM(m, 20);
	ASSERT_EQ(sizeM(m), 2);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 30), 13);

    removeM(m, 20);
	ASSERT_EQ(sizeM(m), 2);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), true);
	ASSERT_EQ(valueM(m, 10), 11);
	ASSERT_EQ(valueM(m, 30), 13);

    removeM(m, 30);
	ASSERT_EQ(sizeM(m), 1);
	ASSERT_EQ(elemM(m, 10), true);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), false);
	ASSERT_EQ(valueM(m, 10), 11);

    removeM(m, 10);
	ASSERT_EQ(sizeM(m), 0);
	ASSERT_EQ(elemM(m, 10), false);
	ASSERT_EQ(elemM(m, 20), false);
	ASSERT_EQ(elemM(m, 30), false);

	destroyM(m);
})

TEST(testMapDestroy, {
    int n = 1000;
	Map m = emptyM();
    for (int i = 0; i < n; i++) {
        int key = n;
        int value = -n;
        insertM(m, key, value);
        ASSERT_EQ(valueM(m, key), value);
    }
	destroyM(m);
})

struct Dist {
    int a, b;

    Dist(int aa, int bb) : a(aa), b(bb) {
    }

    int eval(int x) {
        return a * x + b;
    }
};

void testMapDistribution(string test, int n, Dist dkey, Dist dvalue) {
	Map m = emptyM();

    // Insertar
    for (int i = 0; i < n; i++) {
        int key = dkey.eval(i);
        int value = dvalue.eval(i);
        ASSERT_EQ(elemM(m, key), false);
        ASSERT_EQ(sizeM(m), i);
        insertM(m, key, value);
        ASSERT_EQ(elemM(m, key), true);
        ASSERT_EQ(sizeM(m), i + 1);
        ASSERT_EQ(valueM(m, key), value);
    }

    // Insertar de nuevo
    for (int i = 0; i < n; i++) {
        int key = dkey.eval(i);
        int value = dvalue.eval(i);
        ASSERT_EQ(elemM(m, key), true);
        ASSERT_EQ(sizeM(m), n);
        insertM(m, key, value);
        ASSERT_EQ(elemM(m, key), true);
        ASSERT_EQ(sizeM(m), n);
        ASSERT_EQ(valueM(m, key), value);
    }

    // Verificar presencia
    for (int i = 0; i < n; i++) {
        int key = dkey.eval(i);
        int value = dvalue.eval(i);
        ASSERT_EQ(elemM(m, key), true);
        ASSERT_EQ(valueM(m, key), value);
        ASSERT_EQ(sizeM(m), n);
    }

    // Eliminar
    for (int i = 0; i < n; i++) {
        int key = dkey.eval(i);
        int value = dvalue.eval(i);
        ASSERT_EQ(sizeM(m), n - i);
        ASSERT_EQ(elemM(m, key), true);
        ASSERT_EQ(valueM(m, key), value);
        removeM(m, key);
        ASSERT_EQ(elemM(m, key), false);
        ASSERT_EQ(sizeM(m), n - i - 1);
    }

	destroyM(m);
}

// Inserta y borra los números de 0 a 999 en orden.
TEST(testMapDistribution1000m1, {
    testMapDistribution(test, 1000, Dist(1, 0), Dist(2, 0));
})

// Inserta y borra los números de 0 a 999 en orden inverso.
TEST(testMapDistribution1000m2, {
    testMapDistribution(test, 1000, Dist(-1, 999), Dist(4, -500));
})

// Inserta y borra (rotación = 1)
TEST(testMapDistribution1000m3, {
    testMapDistribution(test, 1000, Dist(122713351, 5), Dist(3, -50));
})

// Inserta y borra (rotación = 5)
TEST(testMapDistribution1000m4, {
    testMapDistribution(test, 1000, Dist(171798691, 99), Dist(-1, 44));
})

void correrTestsMap() {
	cout << "[========] Testeando el tipo Map." << endl;
	testMapEmpty();
	testMapInsert();
	testMapRemove();
	testMapDestroy();
	testMapDistribution1000m1();
	testMapDistribution1000m2();
	testMapDistribution1000m3();
	testMapDistribution1000m4();
	cout << "[========] Todos los tests de Map OK." << endl;
}

/***************************** Tests de Network *****************************/

#include "Network.h"

TEST(testNetworkEmpty, {
	Network net = emptyN();
    ASSERT_EQ(elemN(net, 1), false);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
	destroyN(net);
})

TEST(testNetworkAdd, {
	Network net = emptyN();
    ASSERT_EQ(elemN(net, 1), false);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 1);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 2);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 3);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), true);
	destroyN(net);
})

TEST(testNetworkConnect, {
	Network net = emptyN();
    addN(net, 1);
    addN(net, 2);
    addN(net, 3);
    ASSERT_EQ(connectedN(net, 1, 2), false);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), false);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    connectN(net, 1, 2);
    ASSERT_EQ(connectedN(net, 1, 2), true);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), true);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    connectN(net, 2, 3);
    ASSERT_EQ(connectedN(net, 1, 2), true);
    ASSERT_EQ(connectedN(net, 1, 3), true);
    ASSERT_EQ(connectedN(net, 2, 1), true);
    ASSERT_EQ(connectedN(net, 2, 3), true);
    ASSERT_EQ(connectedN(net, 3, 1), true);
    ASSERT_EQ(connectedN(net, 3, 2), true);
	destroyN(net);
})

TEST(testNetworkConnectStar, {
	Network net = emptyN();
    int N = 16;
    for (int i = 0; i < N; i++) {
        addN(net, i);
    }
    for (int i = 0; i < N - 1; i++) {
        connectN(net, 0, i);
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ASSERT_EQ(connectedN(net, j, k), j == k || (j <= i && k <= i));
            }
        }
    }
    destroyN(net);
})

TEST(testNetworkConnectLinear, {
	Network net = emptyN();
    int N = 16;
    for (int i = 0; i < N; i++) {
        addN(net, i);
    }
    for (int i = 0; i < N - 1; i++) {
        connectN(net, i, i + 1);
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ASSERT_EQ(connectedN(net, j, k), j == k || (j <= i + 1 && k <= i + 1));
            }
        }
    }
    destroyN(net);
})

TEST(testNetworkConnectBinary, {
	Network net = emptyN();
    int B = 6;
    int N = 64;
    for (int i = 0; i < N; i++) {
        addN(net, i);
    }
    for (int b = 0; b <= B; b++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ASSERT_EQ(connectedN(net, i, j), (i >> b) == (j >> b));
            }
        }
        for (int i = 0; i < N; i++) {
            // Flippear el b-ésimo bit.
            int j = i ^ (0x1 << b);
            if (i < j) {
                connectN(net, i, j);
            }
        }
    }
    destroyN(net);
})

TEST(testNetworkUndoAdd, {
	Network net = emptyN();
    ASSERT_EQ(elemN(net, 1), false);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 1);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 2);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), false);
    addN(net, 3);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), true);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), false);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), false);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
	destroyN(net);
})

TEST(testNetworkUndoConnect, {
	Network net = emptyN();
    addN(net, 1);
    addN(net, 2);
    addN(net, 3);
    ASSERT_EQ(connectedN(net, 1, 2), false);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), false);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    connectN(net, 1, 2);
    ASSERT_EQ(connectedN(net, 1, 2), true);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), true);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    connectN(net, 2, 3);
    ASSERT_EQ(connectedN(net, 1, 2), true);
    ASSERT_EQ(connectedN(net, 1, 3), true);
    ASSERT_EQ(connectedN(net, 2, 1), true);
    ASSERT_EQ(connectedN(net, 2, 3), true);
    ASSERT_EQ(connectedN(net, 3, 1), true);
    ASSERT_EQ(connectedN(net, 3, 2), true);
    undoN(net);
    ASSERT_EQ(connectedN(net, 1, 2), true);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), true);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    undoN(net);
    ASSERT_EQ(connectedN(net, 1, 2), false);
    ASSERT_EQ(connectedN(net, 1, 3), false);
    ASSERT_EQ(connectedN(net, 2, 1), false);
    ASSERT_EQ(connectedN(net, 2, 3), false);
    ASSERT_EQ(connectedN(net, 3, 1), false);
    ASSERT_EQ(connectedN(net, 3, 2), false);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), true);
    ASSERT_EQ(elemN(net, 3), false);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), true);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
    undoN(net);
    ASSERT_EQ(elemN(net, 1), false);
    ASSERT_EQ(elemN(net, 2), false);
    ASSERT_EQ(elemN(net, 3), false);
	destroyN(net);
})

TEST(testNetworkUndoStress, {
	Network net = emptyN();
    int N = 16;
    addN(net, 0);
    for (int i = 0; i < N; i++) {
        addN(net, i);
        connectN(net, 0, i);
        for (int j = 0; j < N; j++) {
            ASSERT_EQ(elemN(net, j), j <= i);
        }
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                ASSERT_EQ(connectedN(net, j, k), true);
            }
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            ASSERT_EQ(elemN(net, j), j <= i);
        }
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                ASSERT_EQ(connectedN(net, j, k), true);
            }
        }
        undoN(net);
        undoN(net);
    }
    destroyN(net);
})

void correrTestsNetwork() {
	cout << "[========] Testeando el tipo Network." << endl;
	testNetworkEmpty();
	testNetworkAdd();
	testNetworkConnect();
	testNetworkConnectStar();
	testNetworkConnectLinear();
	testNetworkConnectBinary();
	testNetworkUndoAdd();
	testNetworkUndoConnect();
	testNetworkUndoStress();
	cout << "[========] Todos los tests de Network OK." << endl;
}
