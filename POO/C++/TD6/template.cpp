#include <iostream>
#include <vector>

using namespace std;

template<class X>
class Paire {
    public:
        X elem1;
        X elem2;

        void echanger();
};

template<class X>
void Paire<X>::echanger(){
    X tmp = elem1;
    elem1 = elem2;
    elem2 = tmp;
}

int main(){
    Paire<float> P;

    P.elem1 = 1.2;
    P.elem2 = 5.3;

    cout << P.elem1 << P.elem2 << endl;

    P.echanger();

    cout << P.elem1 << P.elem2 << endl;
}
