#include <cstdio> 
#include "module/altitude.h"
#include <cassert>

ostream &operator<<(ostream& flux, const Altitude & e)
{
  e.affichageAltitudeent(flux);
  return flux;  
}
void Altitude::affichageAltitudeent(ostream& flux) const
{
  flux << e;
}
bool Altitude::operator<(const Altitude& e_cmp)
{
  return (this->e < e_cmp.e);
}
bool Altitude::operator>(const Altitude& e_cmp)
{
  return (this->e > e_cmp.e);
}
bool Altitude::operator==(const Altitude& e_cmp) const
{
  //assert(this->e == e_cmp.e);
  return (e_cmp.e == this->e);
}