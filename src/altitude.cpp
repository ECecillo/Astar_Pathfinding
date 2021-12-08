#include <cstdio> 
#include "module/altitude.h"
#include <cassert>

ostream &operator<<(ostream& flux, const Altitude &h)
{
  h.affichageAltitudeent(flux);
  return flux;  
}
void Altitude::affichageAltitudeent(ostream& flux) const
{
  flux << h;
}
int Altitude::operator-(const Altitude& h2)
{
  return (h - h2.h);
}
int Altitude::operator+(Altitude h2)
{
  return (h + h2.h);
}
int Altitude::operator/(Altitude h2)
{
  return (h / h2.h);
}
int Altitude::operator*(Altitude& h2)
{
  return (h * h2.h);
}
bool Altitude::operator<=(const Altitude& h2)
{
  return (h <= h2.h);
}
bool Altitude::operator<(const Altitude& h_cmp)
{
  return (this->h < h_cmp.h);
}
bool Altitude::operator>(const Altitude& h_cmp)
{
  return (this->h > h_cmp.h);
}
bool Altitude::operator==(const Altitude& h_cmp) const
{
  //assert(this->e == e_cmp.e);
  return (h_cmp.h == this->h);
}