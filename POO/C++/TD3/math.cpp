#include <iostream>
#include <cmath>
#include <numeric>

using namespace std;

class Fraction{
    protected:
        int num;
        unsigned int den;

        void simplifier();

    public:
        int getNum();
        void setNum(int);
        unsigned int getDen();
        void setDen(unsigned int);

        float eval();
        void display();

        Fraction operator*(float);

        friend ostream& operator<<(ostream&, Fraction);
        friend Fraction operator+(Fraction, Fraction);
        friend Fraction operator*(float, Fraction);
        
        ~Fraction();
        Fraction();
        Fraction(int n, unsigned int d=1);
};

Fraction::Fraction(){
    setNum(0);
    setDen(1);
}

Fraction::Fraction(int n, unsigned int d){
    setNum(n);
    setDen(d);
}

Fraction::~Fraction(){

}

int Fraction::getNum(){
    return num;
}

void Fraction::setNum(int n){
    num = n;
}

unsigned int Fraction::getDen(){
    return den;
}

void Fraction::setDen(unsigned int d){
    if(d != 0){
        den = d;
    }
}

float Fraction::eval(){
    return getNum() / float(getDen());
}

void Fraction::simplifier(){
    int v = gcd(getNum(), getDen());
    setNum(getNum()/v);
    setDen(getDen()/v);
}

ostream& operator<<(ostream& stream, Fraction frac){
    frac.simplifier();
    stream << "La fraction vaut " << frac.getNum() << "/" << frac.getDen() << endl;
    return stream;
}

Fraction operator+(Fraction a, Fraction b){
    Fraction fraction;
    fraction.setNum(a.getNum() * b.getDen() + b.getNum() * a.getDen());
    fraction.setDen(a.getDen() * b.getDen());
    fraction.simplifier();
    return fraction;
}

Fraction Fraction::operator*(float coef){
    Fraction fraction;
    fraction.setNum(getNum() * coef);
    fraction.setDen(getDen());
    return fraction;
}

Fraction operator*(float coef, Fraction fraction){
    return fraction * coef;
}

class Ensemble{
    protected:
        int taille;
        int* T;

    public:
        Ensemble();
        Ensemble(const Ensemble&);
        ~Ensemble() { delete [] T; cout << "destruction" << endl; }

        Ensemble& operator=(const Ensemble&);

        int getTaille()const;
        int* getT()const;

        void afficher_info(void);
        bool contient(int);
        void ajouter(int);
        void retirer(int);
        Ensemble calculer_union(Ensemble A);
        Ensemble calculer_inter(Ensemble A);

        friend ostream& operator<<(ostream&, Ensemble);
};

Ensemble::Ensemble(){
    taille=0;
    T=nullptr;
    cout << "construction" << endl;
}

Ensemble::Ensemble(const Ensemble& E){
    
    
    T = new int[E.getTaille()];
    for (int i = 0 ; i < E.getTaille() ; i++){
        T[i] = E.T[i];
    }
    taille = E.getTaille();

}

int Ensemble::getTaille()const{
    return taille;
}

int* Ensemble::getT()const{
    return T;
}

void Ensemble::afficher_info(){
    cout << "Taille : " << getTaille() << endl;
    cout << "Pointeur : " << getT() << endl;
}

bool Ensemble::contient(int k){
    for (int i = 0 ; i < getTaille() ; i++){
        if (T[i] == k){
            return true;
        }
    }
    return false;
}

void Ensemble::retirer(int k){
    if (contient(k) == false){
        cout << "Valeur non présente dans l'ensemble !!!!!" << endl;
    }else{
        int* array;
        array = new int[getTaille() - 1];
        for (int i = 0 ; i < getTaille() ; i++){
            if(T[i] != k){
                array[i] = T[i];
            }
        }
        delete [] T ;
        T = array;
        taille--;
        cout << "Valeur supprimée de l'ensemble !" << endl;
    }
}

void Ensemble::ajouter(int k){
    if (contient(k) == true){
        cout << "Valeur déjà présente dans l'ensemble !!!!!" << endl;
    }else{
        int* array;
        array = new int[getTaille() + 1];
        for (int i = 0 ; i < getTaille() ; i++){
            array[i] = T[i];
        }
        delete [] T ;
        array[getTaille()] = k;
        T = array;
        taille++;
        cout << "Valeur ajoutée à l'ensemble !" << endl;
    }
}

Ensemble Ensemble::calculer_union(Ensemble A){
    Ensemble C;
    for (int i = 0 ; i < getTaille() ; i++){
        C.ajouter(T[i]);
    }
    for (int i = 0 ; i < A.getTaille() ; i++){
        C.ajouter(A.T[i]);  
    }
    return C;
}

Ensemble Ensemble::calculer_inter(Ensemble A){
    Ensemble C;
    for (int i = 0 ; i < A.getTaille() ; i++){
        if(contient(A.T[i]) == true){
            C.ajouter(A.T[i]);
        } 
    }
    return C;
}

ostream& operator<<(ostream& stream, Ensemble ensemble){
    for (int i = 0 ; i < ensemble.getTaille() ; i++){
        stream << ensemble.T[i] << "\t" << endl;
    }
    return stream;
}

Ensemble& Ensemble::operator=(const Ensemble& ensemble){
    if(this == &ensemble){
		cout << "Auto-affectation repérée" << endl;
		return *this;
	}
	taille = ensemble.getTaille();

    delete [] T;

    T = new int[ensemble.getTaille()];
    for (int i = 0 ; i < ensemble.getTaille() ; i++){
        T[i] = ensemble.T[i];
    }


	cout << "Copie effectuée" << endl;
	return *this;
}

int main(){
    Ensemble P;
    P.ajouter(1);
    P.ajouter(2);
    P.ajouter(4);
    P.ajouter(6);
    P.ajouter(8);
    P.ajouter(8);
    P.ajouter(8);
    P.ajouter(9);
    P.afficher_info();
    cout << P << endl;
    P.retirer(8);
    P.retirer(8); // Ressoource* ptr;
    cout << P;

    Ensemble A, B;
    A.ajouter(1);
    A.ajouter(2); // Ressoource* ptr;
    A=B;

    A.afficher_info();
}