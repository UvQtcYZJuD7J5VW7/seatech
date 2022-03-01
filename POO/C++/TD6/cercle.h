#include "forme.h"
#include <iostream>

#ifndef __CERCLE
#define __CERCLE

using namespace std;

class Cercle : public Forme {
    public :
        double rayon;
        double perimetre();
};

#endif
