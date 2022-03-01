#include <iostream>
#include "forme.h"

using namespace std;

#ifndef __CARRE
#define __CARRE

class Carre : public Forme {
    public:
        int cote;
        double perimetre();
};

#endif
