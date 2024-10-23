#include <iostream>
#include <vector>
#include <ostream>
using namespace std;

template <typename ConcretePrinter>
class Printer {
    ostream& m_stream;
public:
    Printer(ostream& s) : m_stream(s) { }
    ConcretePrinter& print(auto&& t) {
        m_stream << t;
        return static_cast<ConcretePrinter&>(*this);
    }
    ConcretePrinter& println(auto&& t) {
        m_stream << t << endl;
        return static_cast<ConcretePrinter&>(*this);
    }
};
struct ColorPrinter : Printer<ColorPrinter> {
    enum Color { red, blue, green };
    ColorPrinter(ostream& s) : Printer(s) {}
    ColorPrinter& SetConsoleColor(Color c) {
        // ...
        return *this;
    }
};
int main() {
    ColorPrinter(cout).print("Hello ").SetConsoleColor(ColorPrinter::Color::red).println("Printer!");
    return EXIT_SUCCESS;
}