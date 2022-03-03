#include <iostream> // Import de la bibliothèque par défaut

using namespace std;

class Trajet{ // Définition de la classe Trajet
    protected:
        // Attributs
        float distance; // Attribut distance en réel

    public:
        // Définition des méthodes
        // Getter et Setter
        float getDistance() const; // Renvoie la valeur de l'attribut distance
        void setDistance(float);

        Trajet();
        Trajet(float);
        Trajet(const Trajet&);
        virtual ~Trajet();

        friend ostream& operator<<(ostream&, Trajet&);
};

float Trajet::getDistance() const{
    return distance;
}

void Trajet::setDistance(float d){
    distance = abs(d);
}

Trajet::Trajet(){
    setDistance(0);
    cout << "Construction d'un Trajet par défaut" << endl;
}

Trajet::Trajet(float i){
    setDistance(i);
    cout << "Construction d'un Trajet par paramètre" << endl;
}

Trajet::Trajet(const Trajet& t){
    setDistance(t.getDistance());
    cout << "Construction d'un Trajet par recopie" << endl;
}

Trajet::~Trajet(){
    cout << "Destruction d'un Trajet" << endl;
}

ostream& operator<<(ostream& stream, Trajet& trajet){
    stream << trajet.getDistance() << " km" << endl;
    return stream;
}

class Voyage : public Trajet{
    protected:
        float vitesse;

    public:
        float getVitesse() const;
        void setVitesse(float);
        float getDuree();

        Voyage();
        Voyage(float, float);
        Voyage(const Voyage&);
        virtual ~Voyage();

        Voyage& operator=(const Voyage&);

        friend ostream& operator<<(ostream&, Voyage&);
};

float Voyage::getVitesse() const{
    return vitesse;
}

void Voyage::setVitesse(float v){
    vitesse = abs(v);
}

float Voyage::getDuree(){
    return getDistance()/getVitesse();
}

Voyage::Voyage(){
    setVitesse(0);
    cout << "Construction d'un Voyage par défaut" << endl;
}

Voyage::Voyage(float i, float d = 0) : Trajet(d){
    setVitesse(i);
    cout << "Construction d'un Voyage par paramètre" << endl;
}

Voyage::Voyage(const Voyage& v){
    setVitesse(v.getVitesse());
    setDistance(v.getDistance());
    cout << "Construction d'un Voyage par recopie" << endl;
}

Voyage::~Voyage(){
    cout << "Destruction d'un Voyage" << endl;
}

ostream& operator<<(ostream& stream, Voyage& voyage){
    stream << voyage.getDistance() << " km à " << voyage.getVitesse() << " km/h (Duréee " << voyage.getDuree() << "h)" << endl;
    return stream;
}

Voyage& Voyage::operator=(const Voyage& voyage){
    if(this == &voyage)
	{
		cout << "Auto-affectation repérée" << endl;
		return *this;
	}
    setDistance(voyage.getDistance());
    setVitesse(voyage.getVitesse());
    return *this;
}

int main(){

    Trajet T(8);
    Trajet TT = T;
    cout << TT;

    Voyage V(4);
    Voyage VV = V;
    cout << VV;

    Voyage W(4,5);
    Voyage WW = W;
    cout << WW;
}
