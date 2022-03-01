#include <iostream>
#include <memory>

using namespace std;

template <class X>
class Ensemble{
    protected:
        int taille;
        unique_ptr<X []> T;

    public:
        Ensemble();
        Ensemble(const Ensemble&);
        ~Ensemble() { cout << "destruction" << endl; }

        template <class Y>
        Ensemble<X>& operator=(const Ensemble<Y>&);

        int getTaille()const;

        void afficher_info(void);
        bool contient(X);
        void ajouter(X);
        void retirer(X);
        Ensemble calculer_union(Ensemble A);
        Ensemble calculer_inter(Ensemble A);

        template <class Y>
        friend ostream& operator<<(ostream&, Ensemble<Y>);
};

template <class X>
Ensemble<X>::Ensemble(){
    taille=0;
    T = nullptr;
    cout << "construction" << endl;
}

template <class X>
Ensemble<X>::Ensemble(const Ensemble& E){
    T = make_unique<int []>(E.getTaille());
    for (int i = 0 ; i < E.getTaille() ; i++){
        T[i] = E.T[i];
    }
    taille = E.getTaille();
}

template <class X>
int Ensemble<X>::getTaille()const{
    return taille;
}

template <class X>
void Ensemble<X>::afficher_info(){
    cout << "Taille :int " << getTaille() << endl;
    cout << "Pointeur : " << T.get() << endl;
}

template <class X>
bool Ensemble<X>::contient(X k){
    for (int i = 0 ; i < getTaille() ; i++){
        if (T[i] == k){
            return true;
        }
    }
    return false;
}

template <class X>
void Ensemble<X>::retirer(X k){
    if (contient(k) == false){
        cout << "Valeur non présente dans l'ensemble !!!!!" << endl;
    }else{
        unique_ptr<int []> array;
        array = make_unique<int []>(getTaille() - 1);
        for (int i = 0 ; i < getTaille() ; i++){
            if(T[i] != k){
                array[i] = T[i];
            }
        }
        T = move(array);
        taille--;
        cout << "Valeur supprimée de l'ensemble !" << endl;
    }
}

template <class X>
void Ensemble<X>::ajouter(X k){
    if (contient(k) == true){
        cout << "Valeur déjà présente dans l'ensemble !!!!!" << endl;
    }else{
        unique_ptr<int []> array;
        array = make_unique<int []>(getTaille() + 1);
        for (int i = 0 ; i < getTaille() ; i++){
            array[i] = T[i];
        }
        array[getTaille()] = k;
        T = move(array);
        taille++;
        cout << "Valeur ajoutée à l'ensemble !" << endl;
    }
}

template <class X>
Ensemble<X> Ensemble<X>::calculer_union(Ensemble<X> A){
    Ensemble C;
    for (int i = 0 ; i < getTaille() ; i++){
        C.ajouter(T[i]);
    }
    return C;
}

template <class X>
Ensemble<X> Ensemble<X>::calculer_inter(Ensemble<X> A){
    Ensemble C;
    for (int i = 0 ; i < A.getTaille() ; i++){
        if(contient(A.T[i]) == true){
            C.ajouter(A.T[i]);
        } 
    }
    return C;
}

template <class Y>
ostream& operator<<(ostream& stream, Ensemble<Y> ensemble){
    for (int i = 0 ; i < ensemble.getTaille() ; i++){
        stream << ensemble.T[i] << "\t" << endl;
    }
    return stream;
}

template <class X>
template <class Y>
Ensemble<X>& Ensemble<X>::operator=(const Ensemble<Y>& ensemble){
    if(this == &ensemble){
		cout << "Auto-affectation repérée ptit con" << endl;
		return *this;
	}
	taille = ensemble.getTaille();
    unique_ptr<Y []> T;
    T = make_unique<Y []>(ensemble.getTaille());
    for (int i = 0 ; i < ensemble.getTaille() ; i++){
        T[i] = ensemble.T[i];
    }


	cout << "Copie effectuée" << endl;
	return *this;
}

int main(){
    Ensemble<int> P;
    P.ajouter(1);
    P.ajouter(1);
    P.ajouter(2);
    Ensemble A = P;

    cout << P << endl;
}
