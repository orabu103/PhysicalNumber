#include "PhysicalNumber.h"
#include "Conversion.h"
using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double val, Unit name)
{
    _val = val;
    _name = name;
}
const PhysicalNumber PhysicalNumber::operator+() const {  return *this; }
const PhysicalNumber PhysicalNumber::operator-() const { return PhysicalNumber(-this->_val,this->_name); }

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber &py) const
{
    if(verifier(*this,py)){
    double temp = Conversion::conver(this->_name,py._name,py._val);  
   
    return PhysicalNumber(this->_val + temp, this->_name);
    }
    else throw std::string("Not the same Unit");

}
const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber &py) const
{
    if(verifier(*this,py)){
    double temp = Conversion::conver(this->_name,py._name,py._val);
    //  cout << temp<<"\n";
    return PhysicalNumber(this->_val - temp, this->_name);
    }
    else throw std::string("Not the same Unit");
}


PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber &py)
{
    PhysicalNumber temp = *this + py;
    *this=temp;   
    return *this;
}
PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber &py)
{
    PhysicalNumber temp = *this - py;
    *this=temp;   
    return *this;
}
const PhysicalNumber PhysicalNumber::operator++(int){
    PhysicalNumber temp(*this);
    this->_val++ ;
    return temp;
}
const PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber temp(*this);
    this->_val++ ;
    return temp;
}
PhysicalNumber& PhysicalNumber::operator++(){
     ++this->_val;
    return *this;
}
PhysicalNumber& PhysicalNumber::operator--(){
    --this->_val;
    return *this;
}
bool ariel::operator>(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    // if(verifier(p1,p2)){
    double p2_double = Conversion::conver(p1._name,p2._name,p2._val);
    if(p1._val>p2_double) return true;
    return false;
    // }
    // else throw std::string("Not the same Unit");

}
bool ariel::operator<(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if((p2 > p1)) return true;
    return false;
}
bool ariel::operator==(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    // if(verifier(p1,p2)){
    double p2_double = Conversion::conver(p1._name,p2._name,p2._val);
    // cout << p1._val<<"\n";
    // cout << p2_double<<"\n";
    // double a =p2_double-p1._val;
    // cout <<a <<"\n";

    if(p1._val-p2_double==0) return true;
    return false;
    // }
    // else throw std::string("Not the same Unit");
    
}
bool ariel::operator!=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(!(p1==p2)) return true;
    return false;
}
bool ariel::operator>=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(!(p1 < p2)) {return true;}
    return false;
}
bool ariel::operator<=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(!(p1 > p2)) return true;
    return false;
}
std::ostream& ariel::operator<<(std::ostream& os, const PhysicalNumber& other)
{
    std::string typeof;
switch(other._name) 
{
    case Unit::KM : typeof = "km"; break;
    case Unit::M : typeof = "m"; break;
    case Unit::CM : typeof = "cm"; break;
    case Unit::TON : typeof = "ton"; break;
    case Unit::KG : typeof = "kg"; break;
    case Unit::G : typeof = "g"; break;
    case Unit::HOUR : typeof = "hour"; break;
    case Unit::MIN : typeof = "min"; break;
    case Unit::SEC : typeof = "sec"; break;
}
return os << other._val << "[" << typeof <<"]";
}


static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
    char actualChar;
    input >> actualChar;
    if (!input) return input;

    if (actualChar!=expectedChar) 
        // failbit is for format error
        input.setstate(ios::failbit);
    return input;
}
std::istream& ariel::operator>>(std::istream& is, PhysicalNumber& other)
{
    ios::pos_type startPosition = is.tellg();
    std:string s;
 if ( (!(is >> other._val))               ||
         (!getAndCheckNextCharIs(is,'[')) ||
         (!(is >> s))                     ||
         (!(getAndCheckNextCharIs(is,']')))) {
        s.erase(std::remove(s.begin(), s.end(), ']'), s.end());

        // other._name=other.m[s];
        auto errorState = is.rdstate(); // remember error state
        is.clear(); // clear error so seekg will work
        is.seekg(startPosition); // rewind
        is.clear(errorState); // set back the error flag

        Unit new_type;
        if( s.compare("km") == 0 ) new_type = Unit::KM; 
        else if( s.compare("m") == 0 ) new_type = Unit::M; 
        else if( s.compare("cm") == 0 ) new_type = Unit::CM; 

        else if( s.compare("ton") == 0 ) new_type = Unit::TON; 
        else if( s.compare("kg") == 0 ) new_type = Unit::KG; 
        else if( s.compare("g") == 0 ) new_type = Unit::G; 

        else if( s.compare("hour") == 0 ) new_type = Unit::HOUR; 
        else if( s.compare("min") == 0 ) new_type = Unit::MIN; 
        else new_type = Unit::SEC; // ( s.compare("sec") ==0  )
        other._name = new_type;
        }
        return is;
}
// Checking:                                                              
bool PhysicalNumber::verifier(const PhysicalNumber& input1, const PhysicalNumber& input2) const {
if( (is_len(input1,input2) || is_mass(input1,input2) || is_time(input1,input2)) ) return true;
else return false;
}
bool PhysicalNumber::is_len(const PhysicalNumber& input1, const PhysicalNumber& input2) const {
Unit type1 = input1._name;
Unit type2 = input2._name;
if(      ((type1 == Unit::KM) || (type1 == Unit::M) || (type1 == Unit::CM)) && 
         ((type2 == Unit::KM) || (type2 == Unit::M) || (type2 == Unit::CM))         ) return true;
else return false;
}
bool PhysicalNumber::is_mass(const PhysicalNumber& input1, const PhysicalNumber& input2) const {
Unit type1 = input1._name;
Unit type2 = input2._name;   
 if(      ((type1 == Unit::TON) || (type1 == Unit::KG) || (type1 == Unit::G)) && 
         ((type2 == Unit::TON) || (type2 == Unit::KG) || (type2 == Unit::G))         ) return true;
else return false;   
 }
bool PhysicalNumber::is_time(const PhysicalNumber& input1, const PhysicalNumber& input2) const {
Unit type1 = input1._name;
Unit type2 = input2._name;
if(      ((type1 == Unit::HOUR) || (type1 == Unit::MIN) || (type1 == Unit::SEC)) && 
         ((type2 == Unit::HOUR) || (type2 == Unit::MIN) || (type2 == Unit::SEC))         ) return true;
else return false;    
}
