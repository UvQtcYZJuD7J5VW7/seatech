#include <iostream>
#include <cmath>

using namespace std;

class Vehicule{

	protected :
		int vitesse;
		int vitesse_max;
		double poids;

	public :
		int getVitesse();
		void setVitesse(int);
		int getVitesseMax();
		void setVitesseMax(int);
		double getPoids();
		void setPoids(double);
		
		void ralentir();
		Vehicule();
		Vehicule(int v, int vm=130);
		~Vehicule();
		void afficher();
		void accelerer();
		Vehicule attacher(Vehicule);
		Vehicule multiplier(double);

		Vehicule operator+(Vehicule); // Attacher un véhicule
		Vehicule operator*(double); // Multiplier la vitesse du véhicule
		Vehicule operator=(Vehicule); // Recopier les attributs d'un véhicule

		friend Vehicule operator*(double, Vehicule);
		friend ostream& operator<<(ostream&, Vehicule);
};

int Vehicule::getVitesse() 
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

int Vehicule::getVitesseMax() 
{
	return vitesse_max;
}


void Vehicule::setVitesseMax(int newVitesseMax) 
{
	vitesse_max = newVitesseMax;
}

double Vehicule::getPoids()
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
}

Vehicule::Vehicule(it take se);
	setPoids(1);
}

Vehicule::~Vehicule()
{
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
}

Vehicule Vehicule::operator=(Vehicule vehicule) 
{
	if(this == &vehicule)
	{
		cout << "Auto-affectation repérée" << endl;
		return vehicule;
	}
	setVitesse(vehicule.getVitesse());
	setVitesseMax(vehicule.getVitesseMax());
	setPoids(vehicule.getPoids());
	cout << "Copie effectuée" << endl;
	return vehicule;
}

Vehicule operator*(double coef, Vehicule vehicule)
{
	Vehicule newVehicle;
	newVehicle.setVitesseMax(vehicule.getVitesseMax());
	newVehicle.setPoids(vehicule.getPoids());
	newVehicle.setVitesse(vehicule.getVitesse() * coef);
	return newVehicle;
}

ostream& operator<<(ostream& stream, Vehicule vehicule)
{
	stream << vehicule.getVitesse() << "/" << vehicule.getVitesseMax() << " km/h\tPoids : " << vehicule.getPoids() << endl;
	return stream;
}

double energ(Vehicule vehicule)
{
	return .5 * vehicule.getPoids() * pow(vehicule.getVitesse(), 2);
}

int main() {
	Vehicule voiture = 100;
	cout << voiture << energ(voiture) << endl;
}