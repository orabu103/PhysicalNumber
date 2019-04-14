#include <iostream>
#include "Unit.h"
#include <sstream>


using namespace std;

namespace ariel{
    class PhysicalNumber{
        double _Value;
        Unit _Type;

        public:
            
            PhysicalNumber(double Value, Unit Type);
            const PhysicalNumber operator+() const;
            const PhysicalNumber operator-() const;
            const PhysicalNumber operator+(const PhysicalNumber &py) const;
            const PhysicalNumber operator-(const PhysicalNumber &py) const;
            PhysicalNumber& operator+=(const PhysicalNumber &py);
            PhysicalNumber& operator-=(const PhysicalNumber &py);

            bool operator>(const PhysicalNumber& ,const PhysicalNumber&);
            bool operator<(const PhysicalNumber& ,const PhysicalNumber&);
            bool operator>=(const PhysicalNumber& ,const PhysicalNumber&);
            bool operator<=(const PhysicalNumber& ,const PhysicalNumber&);
            bool operator!=(const PhysicalNumber& ,const PhysicalNumber&);
            bool operator==(const PhysicalNumber& ,const PhysicalNumber&);

            const PhysicalNumber operator++(int);
	    const PhysicalNumber operator--(int);
	    // Prefix: (--A)
	    PhysicalNumber& operator++(); 
	    PhysicalNumber& operator--();

            friend std::ostream& operator<<(std::ostream&, const PhysicalNumber&); 
	    friend std::istream& operator>>(std::istream&, PhysicalNumber&); 

            // Checking:
	    static  bool verifier(const PhysicalNumber&, const PhysicalNumber&) ; 
            static  bool is_len(const PhysicalNumber&, const PhysicalNumber&) ;
	    static  bool is_mass(const PhysicalNumber&, const PhysicalNumber&) ; 
   	    static  bool is_time(const PhysicalNumber&, const PhysicalNumber&) ;

    };
}
