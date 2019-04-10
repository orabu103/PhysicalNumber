using namespace std;


namespace ariel{
    class Conversion{
         public:
          static double conver(Unit sur ,Unit des, double size)
        {
            switch (des)
            {
              case Unit::KM : // KM -> M ,CM
              switch (sur)
            {
              case Unit::M:
                return 1000 *size; 
                break;
              case Unit::CM:
                return 100000 *size; 
                break;
                default:return size;
                break;
            }
            break;
            case Unit::M : // M -> KM,CM
            switch (sur)
            {
              case Unit::KM:
                return 0.001 *size; 
                break;
              case Unit::CM:
                return 100 *size; 
                break;
                default:return size;
                break;
            }
            break;
            case Unit::CM : //CM -> M , KM
            switch (sur)
            {
              case Unit::M:
                return 0.01 *size; 
                break;
              case Unit::KM:
                return 0.00001 *size; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::G : //G -> KG , TON
            switch (sur)
            {
              case Unit::KG:
                return 0.001 *size; 
                break;
              case Unit::TON:
                return 0.000001 *size; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::KG : //KG -> G , TON
            switch (sur)
            {
              case Unit::G:
                return 1000 *size; 
                break;
              case Unit::TON:
                return size / 1000; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::TON : //TON -> G , KG
            switch (sur)
            {
              case Unit::G:
                return (1000000 *size); 
                break;
              case Unit::KG:
                return 1000 *size; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::SEC : //SEC -> MIN , HOUR
            switch (sur)
            {
              case Unit::MIN:
                return size / 60; 
                break;
              case Unit::HOUR:
                return size / 3600; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::MIN : //MIN -> SEC , HOUR
            switch (sur)
            {
              case Unit::SEC:
                return 60 *size; 
                break;
              case Unit::HOUR:
                return size / 60 ; 
                break;
                default:return size;
                break;
            }
            break;
             case Unit::HOUR : //HOUR -> MIN , SEC
            switch (sur)
            {
              case Unit::MIN:
                return 60 *size; 
                break;
              case Unit::SEC:
                return  3600*size; 
                break;
                default:return size;
                break;
            }
            break;
            default:return size;
                break;
          }
      }
  };
}
