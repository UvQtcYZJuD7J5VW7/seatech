#include <iostream>
#include <memory>

using namespace std;

class Ensemble{
    protected:
        int taille;
        unique_ptr<int []> T;

    public:
        Ensemble();
        Ensemble(const Ensemble&);
        ~Ensemble() { cout << "destruction" << endl; }

        Ensemble& operator=(const Ensemble&);

        int getTaille()const;

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
    T = nullptr;
    cout << "construction" << endl;
}

Ensemble::Ensemble(const Ensemble& E){
    T = make_unique<int []>(E.getTaille());
    for (int i = 0 ; i < E.getTaille() ; i++){
        T[i] = E.T[i];
    }
    taille = E.getTaille();
}

int Ensemble::getTaille()const{
    return taille;
}

void Ensemble::afficher_info(){
    cout << "Taille : " << getTaille() << endl;
    cout << "Pointeur : " << T.get() << endl;
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

void Ensemble::ajouter(int k){
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
    unique_ptr<int []> T;
    T = make_unique<int []>(ensemble.getTaille());
    for (int i = 0 ; i < ensemble.getTaille() ; i++){
        T[i] = ensemble.T[i];
    }


	cout << "Copie effectuée" << endl;
	return *this;
}

int main(){
    Ensemble P;
    P.ajouter(1);
    P.ajouter(1);
    P.ajouter(2);
    Ensemble A = P;

    cout << P << endl;
}
