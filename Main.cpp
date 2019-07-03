
#include <cassert>
#include <map>

#include "Common.h"
#include "Map.h"
#include "Test.h"

int main() {
    srand(0xFEDCBA98);

    correrTestsStack();
    cout << endl;

    correrTestsMap();
    cout << endl;

    correrTestsNetwork();
    cout << endl;

    return 0;
}
