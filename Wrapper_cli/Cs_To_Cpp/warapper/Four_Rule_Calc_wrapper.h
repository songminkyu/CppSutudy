
class Four_Rule_CalcPrivate;

class Four_Rule_Calc_wrapper
{
private: std::shared_ptr<Four_Rule_CalcPrivate> _private;

public: Four_Rule_Calc_wrapper();

public: double sum(double a, double b,std::string toMsg);
public: double subtract(double a, double b,std::string toMsg);
public: double division(double a, double b,std::string toMsg);
public: double multiply(double a, double b,std::string toMsg);

};