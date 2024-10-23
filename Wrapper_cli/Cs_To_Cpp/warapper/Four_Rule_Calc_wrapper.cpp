#include <msclr\auto_gcroot.h>
#include <string>
#include <memory>
using namespace System::Runtime::InteropServices; // Marshal
using namespace System;

class Four_Rule_CalcPrivate
{
public: msclr::auto_gcroot<Four_Rule_Calc^> four_Rule_Calc;
};

class __declspec(dllexport) Four_Rule_Calc_wrapper
{
private: std::shared_ptr<Four_Rule_CalcPrivate> _private;

public: 
    Four_Rule_Calc_wrapper()
    {
        _private = std::make_shared<Four_Rule_CalcPrivate>();
        _private->four_Rule_Calc = gcnew Four_Rule_Calc();
    }

    double sum(double a, double b, std::string msg)
    {        
        String^ toMsg = gcnew String(msg.c_str());

        return _private->four_Rule_Calc->sum(a, b, toMsg);
    }
    double subtract(double a, double b , std::string msg)
    {       
        String^ toMsg = gcnew String(msg.c_str());

        return _private->four_Rule_Calc->subtract(a, b, toMsg);
    }
    double division(double a, double b, std::string msg)
    {       
        String^ toMsg = gcnew String(msg.c_str());

        return _private->four_Rule_Calc->division(a, b, toMsg);
    }
    double multiply(double a, double b, std::string msg)
    {       
        String^ toMsg = gcnew String(msg.c_str());

        return _private->four_Rule_Calc->multiply(a, b, toMsg);
    }
};