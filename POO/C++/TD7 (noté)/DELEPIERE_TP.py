# -*- coding: utf-8 -*-

class Trajet : # Class Trajet
    def __init__(self, i = 0) :
        self._distance = i

    def __str__(self) :
        return f"{self.distance} km" # Définition de la méthode d'affichage

    def getDistance(self) :
        return self._distance

    def setDistance(self, i) :
        self._distance = abs(i)

    distance = property(getDistance,setDistance) # Définition d'une propriété pour l'attribut distance

class Voyage(Trajet) : # Classe Voyage, héritière de Trajet
    def __init__(self, v = 0, i = 0) :
        super().__init__(i) # Appel du constructeur parent
        self._vitesse = v # Définition d'un nouvel attribut initialisé par paramètre (sinon 0)

    def __str__(self) :
        return f"{self.distance} km à {self.vitesse} (Durée {self.duree}h)" # Définition de la méthode d'affichage

    def getVitesse(self) :
        return self._vitesse

    def setVitesse(self, i) :
        self._vitesse = i

    vitesse = property(getVitesse,setVitesse) # Définition d'une propriété pour l'attribut vitesse

    def getDuree(self) :
        return self.distance/self.vitesse

    duree = property(getDuree) # Définition d'une propriété pour l'attribut durée

T = Trajet(8)
TT = T
print(TT)

V = Voyage(4)
VV = V
print(VV)

W = Voyage(4,5)
WW = W
print(WW)
