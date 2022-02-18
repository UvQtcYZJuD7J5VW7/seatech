#include <iostream>
#include <memory>

using namespace std;

class Ressource{
    protected:

    public:
        Ressource();
        ~Ressource();
};

Ressource::Ressource(){
    cout << "Construction de " << this << endl;
}

Ressource::~Ressource(){
    cout << "Destruction de " << this << endl;
}

int main(){

    int taille;
    cin >> taille;

    shared_ptr<Ressource> shaptr;
    shaptr = make_shared<Ressource>();

    cout << shaptr.use_count() << endl;
    
    shared_ptr<Ressource> shaptr2;
    shaptr2 = shaptr;

    cout << shaptr.use_count() << endl;

    shared_ptr<Ressource> shaptr3;
    shaptr3 = shaptr2;

    cout << shaptr.use_count() << endl;

    shaptr3 = nullptr;
    cout << shaptr.use_count() << endl;
    shaptr2 = nullptr;
    cout << shaptr.use_count() << endl;
    shaptr = nullptr;
    cout << shaptr.use_count() << endl;

}