using System;

//닷넷 프레임워크 클래스 라이브러리

public class Four_Rule_Calc
{
    public double sum(double a, double b, string Msg)
    {
        Console.WriteLine(Msg);
        return a + b;
    }
    public double subtract(double a, double b, string Msg)
    {
        Console.WriteLine(Msg);
        return a - b;
    }
    public double division( double a, double b, string Msg)
    {
        Console.WriteLine(Msg);
        return a / b;
    }
    public double multiply(double a, double b, string Msg)
    {
        Console.WriteLine(Msg);
        return a * b;
    }
}
