
#ifndef ALTITUDE_H
#define ALTITUDE_H
#include <iostream>

using namespace std;

class Altitude
{
    friend ostream &operator<<(ostream& flux, const Altitude &h);
public:
    Altitude(){h = 0;};
    // Constructeur qui prend un entier en paramètre et qui donne à e la valeur de x.
    Altitude(int x){h = x;};
    
    void affichageAltitudeent(ostream& flux) const;
    // Surcharge de < pour comparer les éléments où e_cmp sera l'élément auxquels on voudra comparer pour voir si il est plus grand que notre élément local.
    bool operator<(const Altitude &h);
    bool operator>(const Altitude &h);
    //On va comparer si 2 éléments sont égaux ou non.
    bool operator==(const Altitude &h) const;
    int operator-(const Altitude& h);
    int operator+(Altitude h);
    int operator*(Altitude& h);
    int operator/(Altitude h);
    bool operator<=(const Altitude&);
private:
    int h;
};

#endif
