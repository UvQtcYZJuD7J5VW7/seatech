#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class Ensemble{
    protected:
        int taille;
        unique_ptr<int []> T;

    public:
        Ensemble();
        Ensemble(const Ensemble&);
        ~Ensemble() {}

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
/*
bool Ensemble::contient(int k){
    if(getTaille() < 2){
        for (int i = 0 ; i < getTaille() ; i++){
            if (T[i] == k){
                return true;
            }
       }
        return false;
    }else{
        int vStart = 0;
        int vEnd = getTaille();
        int vMid = getTaille()/2;
        int vNow, i;
        while(i < getTaille()){
            if(k < vMid){
                vMid = vMid/2;
            }else{
                vMid = (vMid + vEnd)/2;
            }
            if(k == T[vMid]){
                return true;
            }
            i++;
        }
        return false;
    }
}*/

void Ensemble::retirer(int k){
    if (contient(k) == false){
        //cout << "Valeur non présente dans l'ensemble !!!!!" << endl;
    }else{
        unique_ptr<int []> array;
        array = make_unique<int []>(getTaille() - 1);
        for (int i = 0 ; i < getTaille() ; i++){
            if(k > T[i] && T[i] != k){
                array[i] = T[i];
            }else{
                array[i] = T[i+1];
            }
        }
        T = move(array);
        taille--;
        //cout << "Valeur supprimée de l'ensemble !" << endl;
    }
}

void Ensemble::ajouter(int k){
    if (contient(k) == true){
        //cout << "Valeur déjà présente dans l'ensemble !!!!!" << endl;
    }else{
        unique_ptr<int []> array;
        array = make_unique<int []>(getTaille() + 1);
        if(getTaille() == 0){
            array[getTaille()] = k;
        }else if(getTaille() == 1){
            array[0] = T[0];
            array[getTaille()] = k;
            if(array[0] > k){
                swap(array[0],array[1]);
            }
        }else{
            int vBefore, vNow;
            int vStart = T[0];
            int vEnd = T[getTaille() - 1];
            if(k < vStart){
                array[0] = k;
                for (int i = 0 ; i < getTaille() ; i++){
                    array[i+1] = T[i];
                }
            }else if(k > vEnd){
                for (int i = 0 ; i < getTaille() ; i++){
                    array[i] = T[i];
                }
                array[getTaille()] = k;
            }else{
                for (int i = 0 ; i < getTaille() ; i++){
                    vNow = T[i];
                    if(vNow < k){
                        array[i] = T[i];
                    }else if(vBefore < k && k < vNow){
                        array[i] = k;
                        array[i+1] = vNow;
                    }else{
                        array[i+1] = vNow;
                    }
                    vBefore = vNow;
                }
            }
        }
        T = move(array);
        taille++;
        //cout << "Valeur ajoutée à l'ensemble !" << endl;
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
        stream << ensemble.T[i] << "\t";
    }
    stream << endl;
    return stream;
}

Ensemble& Ensemble::operator=(const Ensemble& ensemble){
    if(this == &ensemble){
		cout << "Auto-affectation repérée ptit con" << endl;
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
    cout << P;
    P.ajouter(4);
    cout << P;
    P.ajouter(6);
    cout << P;
    P.ajouter(5);
    cout << P;
    P.ajouter(1);
    cout << P;
    P.ajouter(9);
    cout << P;
    P.ajouter(8);
    cout << P;
    P.ajouter(2);
    cout << P;
    P.ajouter(-7);
    cout << P;
    P.retirer(8);
    cout << P;
    // cout << P.contient(8);
}
