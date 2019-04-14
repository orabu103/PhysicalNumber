#include "PhysicalNumber.h"
#include "Conversion.h"
using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double Value, Unit Type)
{
    _Value = Value;
    _Type = Type;
}
const PhysicalNumber PhysicalNumber::operator+() const {  return *this; }
const PhysicalNumber PhysicalNumber::operator-() const { return PhysicalNumber(-this->_Value,this->_Type); }

const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber &py) const
{
    if(verifier(*this,py)){
    double temp = Conversion::conver(this->_Type,py._Type,py._Value);  
    return PhysicalNumber(this->_Value + temp, this->_Type);
    }
    else throw std::string("Not the same Unit");

}
const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber &py) const
{
    if(verifier(*this,py)){
    double temp = Conversion::conver(this->_Type,py._Type,py._Value);
    return PhysicalNumber(this->_Value - temp, this->_Type);
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

// Increasing and decreasing by one operators
// Postfix: (A++)
const PhysicalNumber PhysicalNumber::operator++(int){
    PhysicalNumber temp(*this);
    this->_Value++ ;
    return temp;
}
const PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber temp(*this);
    this->_Value-- ;
    return temp;
}
// Prefix: (++A)
PhysicalNumber& PhysicalNumber::operator++(){
     ++this->_Value;
    return *this;
}
PhysicalNumber& PhysicalNumber::operator--(){
    --this->_Value;
    return *this;
}
bool ariel::operator>(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {   
    if(PhysicalNumber::verifier(p1,p2)){
    double ans = (p1 - p2)._Value;
    if(ans > 0) return true;
    else
    return false;
    }
    else throw std::string("Not the same Unit");

}
bool ariel::operator<(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if((p2 > p1)) return true;
    return false;
}
bool ariel::operator==(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(PhysicalNumber::verifier(p1,p2)){
    if((p1 >= p2) && !(p1 > p2)) return true;
    return false;
    }
    else throw std::string("Not the same Unit");
    
}
bool ariel::operator!=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(!(p1==p2)) return true;
    return false;
}
bool ariel::operator>=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {

    if (!(p1 < p2)) return true;
    return false;
}
bool ariel::operator<=(const PhysicalNumber &p1 ,const PhysicalNumber &p2) {
    if(!(p1 > p2)) return true;
    return false;
}
std::ostream& ariel::operator<<(std::ostream& os, const PhysicalNumber& other)
{
    std::string typeof;
switch(other._Type) 
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
return os << other._Value << "[" << typeof <<"]";
}

std::istream& ariel::operator>>(std::istream& is, PhysicalNumber& other) {
std::string input;

// remember place for rewinding
std::ios::pos_type startPosition = is.tellg();

is >> input;

Unit new_type; // Answers
double new_Value; // Ansers

int f_index = input.find('[');
int l_index = input.find(']');

if(f_index == -1 || l_index == -1 || f_index >= l_index) 
{
    auto errorState = is.rdstate(); // remember error state
    is.clear(); // clear error so seekg will work
    is.seekg(startPosition); // rewind
    is.clear(errorState); // set back the error flag
    return is;
}

std::string numbers = input.substr(0,f_index);
std::string s_type = input.substr(f_index+1,l_index - f_index - 1 );

try
{
    new_Value = stod(numbers);   
}
catch(std::exception& e)
{
    auto errorState = is.rdstate(); // remember error state
    is.clear(); // clear error so seekg will work
    is.seekg(startPosition); // rewind
    is.clear(errorState); // set back the error flag
    return is;
}

if( s_type.compare("km") == 0 ) new_type = Unit::KM; 
else if( s_type.compare("m") == 0 ) new_type = Unit::M; 
else if( s_type.compare("cm") == 0 ) new_type = Unit::CM; 

else if( s_type.compare("ton") == 0 ) new_type = Unit::TON; 
else if( s_type.compare("kg") == 0 ) new_type = Unit::KG; 
else if( s_type.compare("g") == 0 ) new_type = Unit::G; 

else if( s_type.compare("hour") == 0 ) new_type = Unit::HOUR; 
else if( s_type.compare("min") == 0 ) new_type = Unit::MIN; 
else if( s_type.compare("sec") == 0 ) new_type = Unit::SEC;
else {
    auto errorState = is.rdstate(); // remember error state
    is.clear(); // clear error so seekg will work
    is.seekg(startPosition); // rewind
    is.clear(errorState); // set back the error flag
    return is;
}

other._Type = new_type;
other._Value = new_Value;
return is;
}

// Checking:                                                              
bool PhysicalNumber::verifier(const PhysicalNumber& input1, const PhysicalNumber& input2)  {
if( (is_len(input1,input2) || is_mass(input1,input2) || is_time(input1,input2)) ) return true;
else return false;
}
bool PhysicalNumber::is_len(const PhysicalNumber& input1, const PhysicalNumber& input2)  {
Unit type1 = input1._Type;
Unit type2 = input2._Type;
if(      ((type1 == Unit::KM) || (type1 == Unit::M) || (type1 == Unit::CM)) && 
         ((type2 == Unit::KM) || (type2 == Unit::M) || (type2 == Unit::CM))         ) return true;
else return false;
}
bool PhysicalNumber::is_mass(const PhysicalNumber& input1, const PhysicalNumber& input2)  {
Unit type1 = input1._Type;
Unit type2 = input2._Type;   
 if(      ((type1 == Unit::TON) || (type1 == Unit::KG) || (type1 == Unit::G)) && 
         ((type2 == Unit::TON) || (type2 == Unit::KG) || (type2 == Unit::G))         ) return true;
else return false;   
 }
bool PhysicalNumber::is_time(const PhysicalNumber& input1, const PhysicalNumber& input2)  {
Unit type1 = input1._Type;
Unit type2 = input2._Type;
if(      ((type1 == Unit::HOUR) || (type1 == Unit::MIN) || (type1 == Unit::SEC)) && 
         ((type2 == Unit::HOUR) || (type2 == Unit::MIN) || (type2 == Unit::SEC))         ) return true;
else return false;    
}
