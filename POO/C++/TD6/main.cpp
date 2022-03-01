#include <iostream>
using namespace std;

#include "cercle.h"
#include "carre.h"

int main(){
    Cercle C;
    C.rayon = 2;
    cout << C.perimetre() << endl;
}
