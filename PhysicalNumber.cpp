std::istream& ariel::operator>>(std::istream& is, PhysicalNumber& other)
{
    ios::pos_type startPosition = is.tellg();
    std:string s;
 if ( (!(is >> other._val))               ||
         (!getAndCheckNextCharIs(is,'[')) ||
         (!(is >> s))                     ||
         (!(getAndCheckNextCharIs(is,']')))) {
        s.erase(std::remove(s.begin(), s.end(), ']'), s.end());        

        Unit new_type;
        if( s.compare("km") == 0 ) new_type = Unit::KM; 
        else if( s.compare("m") == 0 ) new_type = Unit::M; 
        else if( s.compare("cm") == 0 ) new_type = Unit::CM; 

        else if( s.compare("ton") == 0 ) new_type = Unit::TON; 
        else if( s.compare("kg") == 0 ) new_type = Unit::KG; 
        else if( s.compare("g") == 0 ) new_type = Unit::G; 

        else if( s.compare("hour") == 0 ) new_type = Unit::HOUR; 
        else if( s.compare("min") == 0 ) new_type = Unit::MIN; 
        else if( s.compare("sec") == 0 ) new_type = Unit::SEC; 
        else{
        auto errorState = is.rdstate(); // remember error state
        is.clear(); // clear error so seekg will work
        is.seekg(startPosition); // rewind
        is.clear(errorState); // set back the error flag
        }
        other._name = new_type;
         }
         else {
            auto errorState = is.rdstate(); // remember error state
            is.clear(); // clear error so seekg will work
            is.seekg(startPosition); // rewind
            is.clear(errorState); // set back the error flag
        return is;
         }
        
        return is;
}
