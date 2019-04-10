#include <iostream>
#include "Unit.h"
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

namespace ariel{
    class PhysicalNumber{

        public:
            double _val;
            Unit _name;

            PhysicalNumber(double _val, Unit _name);
            const PhysicalNumber operator+() const;
            const PhysicalNumber operator-() const;
            const PhysicalNumber operator+(const PhysicalNumber &py) const;
            const PhysicalNumber operator-(const PhysicalNumber &py) const;
            PhysicalNumber& operator+=(const PhysicalNumber &py);
            PhysicalNumber& operator-=(const PhysicalNumber &py);

            friend bool operator>(const PhysicalNumber& ,const PhysicalNumber&);
            friend bool operator<(const PhysicalNumber& ,const PhysicalNumber&);
            friend bool operator>=(const PhysicalNumber& ,const PhysicalNumber&);
            friend bool operator<=(const PhysicalNumber& ,const PhysicalNumber&);
            friend bool operator!=(const PhysicalNumber& ,const PhysicalNumber&);
            friend bool operator==(const PhysicalNumber& ,const PhysicalNumber&);

            const PhysicalNumber operator++(int);
		    const PhysicalNumber operator--(int);
		    // Prefix: (--A)
		    PhysicalNumber& operator++(); 
		    PhysicalNumber& operator--();

            friend std::ostream& operator<<(std::ostream&, const PhysicalNumber&); 
		    friend std::istream& operator>>(std::istream&, PhysicalNumber&); 

            // Checking:
		   static  bool verifier(const PhysicalNumber&, const PhysicalNumber&) ; //[V]
		   static  bool is_len(const PhysicalNumber&, const PhysicalNumber&) ; //[V]
		   static  bool is_mass(const PhysicalNumber&, const PhysicalNumber&) ; //[V]
		   static  bool is_time(const PhysicalNumber&, const PhysicalNumber&) ; //[V]



    };
}
