#include <iostream> // Import de la bibliothèque par défaut

using namespace std;

class Trajet{ // Définition de la classe Trajet
    protected:
        // Attributs
        float distance; // Attribut distance (réel) en km

    public:
        // Méthodes
        // Get/Set
        float getDistance() const; // Renvoie la valeur de l'attribut distance
        void setDistance(float); // Définit la valeur de l'attribut distance

        // Constructeur et destructeur
        Trajet(); // Constructeur par défaut
        Trajet(float); // Constructeur paramétré
        Trajet(const Trajet&); // Constructeur par recopie
        virtual ~Trajet(); // Destructeur

        // Surcharge d'opérateurs
        Voyage& operator=(const Voyage&); // Surcharge de l'opérateur égal
        friend ostream& operator<<(ostream&, Trajet&); // Surcharge de l'opérateur affichage
};

// Get/Set distance
float Trajet::getDistance() const{
    return distance; // Renvoie la valeur de l'attribut distance
}

void Trajet::setDistance(float d){
    distance = abs(d); // Définit la valeur de l'attribut distance par valeur absolue
}

// Constructeur par défaut
Trajet::Trajet(){
    setDistance(0);
    cout << "Construction d'un Trajet par défaut" << endl;
}

// Constructeur paramétré
Trajet::Trajet(float i){
    setDistance(i);
    cout << "Construction d'un Trajet par paramètre" << endl;
}

// Constructeur par recopie
Trajet::Trajet(const Trajet& t){
    setDistance(t.getDistance());
    cout << "Construction d'un Trajet par recopie" << endl;
}

// Destructeur
Trajet::~Trajet(){
    cout << "Destruction d'un Trajet" << endl;
}

// Surcharge de l'opérateur affichage
ostream& operator<<(ostream& stream, Trajet& trajet){
    stream << trajet.getDistance() << " km" << endl; // Mise en forme du canal de sortie
    return stream; // Renvoie le canal de sortie
}

// Surcharge de l'opérateur égal
Trajet& Trajet::operator=(const Trajet& trajet){
    // Vérification de l'auto-affectation
    if(this == &trajet)
	{
		cout << "Auto-affectation repérée" << endl;
		return *this;
	}
    setDistance(trajet.getDistance()); // Recopie de l'attribut distance
    return *this;
}

class Voyage : public Trajet{ // Définition de la classe Voyage, héritière de Trajet
    protected:
        float vitesse; // Définition d'un nouvel attribut vitesse

    public:
        // Définition de nouvelles méthodes (constructeurs, get/set)
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
    stream << voyage.getDistance() << " km à " << voyage.getVitesse() << " km/h (Durée " << voyage.getDuree() << "h)" << endl;
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
