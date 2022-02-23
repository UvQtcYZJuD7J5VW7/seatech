#include <iostream>
#include <cmath>

using namespace std;

class Vehicule{

	protected :
		int vitesse;
		int vitesse_max;
		double poids;

	public :
		int getVitesse() const;
		void setVitesse(int);
		int getVitesseMax() const;
		void setVitesseMax(int);
		double getPoids() const;
		void setPoids(double);
		
		void ralentir();
		Vehicule();
        Vehicule(const Vehicule&);
		Vehicule(int k, int v=130);
		virtual ~Vehicule();
		void afficher();
		virtual void accelerer();
		//Vehicule attacher(Vehicule);
		//Vehicule multiplier(double);

		//Vehicule operator+(Vehicule); // Attacher un véhicule
		//Vehicule operator*(double); // Multiplier la vitesse du véhicule
		Vehicule& operator=(const Vehicule&); // Recopier les attributs d'un véhicule

		//friend Vehicule operator*(double, Vehicule);
		friend ostream& operator<<(ostream&, const Vehicule&);

        virtual string returnSpeedUnit() = 0;
};

int Vehicule::getVitesse() const
{
	return vitesse;
}

void Vehicule::setVitesse(int newVitesse) 
{
	if(newVitesse < getVitesseMax())
	{
		vitesse = newVitesse;
	}
	else
	{
		vitesse = 0;
	}
}

int Vehicule::getVitesseMax() const
{
	return vitesse_max;
}


void Vehicule::setVitesseMax(int newVitesseMax) 
{
	vitesse_max = newVitesseMax;
}

double Vehicule::getPoids() const
{
	return poids;
}

void Vehicule::setPoids(double newPoids) 
{
	poids = newPoids;
}

void Vehicule::ralentir()
{
	int v = getVitesse();
	v -= 50;
	if(v < 0) v = 0;
	setVitesse(v);
}

Vehicule::Vehicule()
{
	setVitesseMax(130);
	setVitesse(0);
	setPoids(1);
    cout << "construction vehicule" << endl;
}

Vehicule::Vehicule(const Vehicule& v)
{
	setVitesseMax(v.getVitesseMax());
	setVitesse(v.getVitesse());
	setPoids(v.getPoids());
    cout << "recopie vehicule" << endl;
}

Vehicule::Vehicule(int k, int v)
{
	setVitesseMax(v);
	setVitesse(k);
	setPoids(1);
}

Vehicule::~Vehicule()
{
    cout << "destruction vehicule" << endl;
}

void Vehicule::afficher()
{
	printf("%d/%d km/h\t%.2f\n", getVitesse(), getVitesseMax(), getPoids());
}

void Vehicule::accelerer()
{
	if(getVitesse() + 50 < getVitesseMax()) 
	{
		setVitesse(getVitesse() + 50);
	}
	else
	{
		setVitesse(getVitesseMax());
	}
}
/*
Vehicule Vehicule::attacher(Vehicule b) 
{	
	Vehicule att;
	att.setPoids(getPoids() + b.poids);
	att.setVitesse(getVitesse() );
	att.setVitesseMax(getVitesseMax());
	return att;
}

Vehicule Vehicule::operator+(Vehicule vehicule) 
{	
	return attacher(vehicule);
}

Vehicule Vehicule::multiplier(double coef)
{
	Vehicule newVehicle;
	newVehicle.setVitesseMax(getVitesseMax());
	newVehicle.setPoids(getPoids());
	newVehicle.setVitesse(getVitesse() * coef);
	return newVehicle;
}

Vehicule Vehicule::operator*(double coef)
{
	return multiplier(coef);
}*/

Vehicule& Vehicule::operator=(const Vehicule& vehicule) 
{
	if(this == &vehicule)
	{
		cout << "Auto-affectation repérée" << endl;
		return *this;
	}
	setVitesse(vehicule.getVitesse());
	setVitesseMax(vehicule.getVitesseMax());
	setPoids(vehicule.getPoids());
	cout << "Copie effectuée" << endl;
	return *this;
}
/*
Vehicule operator*(double coef, Vehicule vehicule)
{
	Vehicule newVehicle;
	newVehicle.setVitesseMax(vehicule.getVitesseMax());
	newVehicle.setPoids(vehicule.getPoids());
	newVehicle.setVitesse(vehicule.getVitesse() * coef);
	return newVehicle;
}*/

ostream& operator<<(ostream& stream, const Vehicule& vehicule)
{
	stream << vehicule.getVitesse() << "/" << vehicule.getVitesseMax() << " km/h\tPoids : " << vehicule.getPoids() << endl;
	return stream;
}
/*
double energ(Vehicule vehicule)
{
	return .5 * vehicule.getPoids() * pow(vehicule.getVitesse(), 2);
}
*/
class Bateau : public Vehicule{
    protected:
        int tirant;

    public:
        int getTirant() const {return tirant;}
        void setTirant(int k) {if(k>0) tirant = k;}

        Bateau() {setVitesseMax(50); setTirant(10); cout << "construction bateau" << endl;}
        ~Bateau() {cout << "destruction bateau" << endl;}
        Bateau(const Bateau&);

        bool testSafetyNav(int prof);
        Bateau& operator=(const Bateau&);
        void accelerer();

        string returnSpeedUnit() {return "noeuds";}
};

Bateau::Bateau(const Bateau& b) : Vehicule(b){
    cout << "recopie bateau" << endl;
    setTirant(b.getTirant());
}

bool Bateau::testSafetyNav(int prof){
    if(prof > getTirant() + 1){
        return true;
    }else{
        return false;
    }
}

Bateau& Bateau::operator=(const Bateau& b){
    if(this == &b)
	{
		cout << "Auto-affectation repérée bateau" << endl;
		return *this;
	}
	Vehicule::operator=(b);
    setTirant(b.getTirant());
	cout << "Copie effectuée bateau" << endl;
	return *this;
}

void Bateau::accelerer()
{
	if(getVitesse() + 5 < getVitesseMax()) 
	{
		setVitesse(getVitesse() + 5);
	}
	else
	{
		setVitesse(getVitesseMax());
	}
}

int tirantInCharge(Bateau B, int charge){
    return B.getTirant() + charge;
}

class Avion : public Vehicule{
    protected:
        int altitude;

    public:
        int getAltitude() const {return altitude;}
        void setAltitude(int k) {if(k>0) altitude = k;}

        Avion() {setVitesseMax(800); setAltitude(30000); cout << "construction avion" << endl;}
        ~Avion() {cout << "destruction avion" << endl;}
        Avion(const Avion&);

        Avion& operator=(const Avion&);
        void accelerer();

        string returnSpeedUnit() {return "machs";}
};

Avion::Avion(const Avion& b) : Vehicule(b){
    cout << "recopie avion" << endl;
    setAltitude(b.getAltitude());
}

void Avion::accelerer()
{
	if(getVitesse() + 100 < getVitesseMax()) 
	{
		setVitesse(getVitesse() + 100);
	}
	else
	{
		setVitesse(getVitesseMax());
	}
}

Avion& Avion::operator=(const Avion& b){
    if(this == &b)
	{
		cout << "Auto-affectation repérée avion" << endl;
		return *this;
	}
	Vehicule::operator=(b);
    setAltitude(b.getAltitude());
	cout << "Copie effectuée avion" << endl;
	return *this;
}

int main(){
    Vehicule** Tab = new Vehicule*[3];
    Tab[0] = new Bateau;
    Tab[1] = new Avion;
    Tab[2] = new Bateau;
    for (int i=0; i<3; i++){
        cout << (*Tab[i]).getVitesseMax();
        cout << Tab[i]->returnSpeedUnit() << endl;
    }
    delete Tab[0];
    delete Tab[1];
    delete Tab[2];
}
