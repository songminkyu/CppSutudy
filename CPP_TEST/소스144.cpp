#include <iostream>
#include <map>
#include <functional>

//http://www.vishalchovatiya.com/factory-design-pattern-in-modern-cpp/

/*
Functional Approach to Factory Design Pattern using Modern C++

In our Abstract Factory example, we have followed the object-oriented approach but 
its equally possible nowadays to a more functional approach.

So, let¡¯s build a similar kind of Factory without relying on polymorphic functionality as 
it might not suit some time-constrained application like an embedded system. Because 
the virtual table & dynamic dispatch mechanism may troll system during critical functionality.

This is pretty straight forward as it uses functional & lambda functions as follows:

If you are thinking that we are over-engineering, then keep in mind that our object construction 
is simple here just to demonstrate the technique & so does our lambda function.

When your object representation increases, it requires a lot of methods to call in order to instantiate object properly, 
in such case you just need to modify lambda expression of the factory or introduce Builder Design Pattern.
*/
using namespace std;
enum class PointType { Point2D, Point3D};

class Point {
    float   m_x;
    float   m_y;
    Point(float x, float y) : m_x(x), m_y(y) {}
public:
    struct Factory {
        static Point NewCartesian(float x, float y) { return { x,y }; }
        static Point NewPolar(float r, float theta) { return{ r * cos(theta), r * sin(theta) }; }
    };
};


struct Point2D : Point {/* . . . */ };
struct Point3D : Point {/* . . . */ };
class PointFunctionalFactory {
    map<PointType, function<unique_ptr<Point>() >>      m_factories;
public:
    PointFunctionalFactory() {
        m_factories[PointType::Point2D] = [] { return make_unique<Point2D>(); };
        m_factories[PointType::Point3D] = [] { return make_unique<Point3D>(); };
    }
    unique_ptr<Point> create(PointType type) { return m_factories[type](); }
};
int main() {
    PointFunctionalFactory pf;
    auto p2D = pf.create(PointType::Point2D);
    return EXIT_SUCCESS;
}

/*

Benefits of Factory Design Pattern

    1.  Single point/class for different object creation. Thus easy to maintain & understand software.

    2. You can create the object without even knowing its type by using Abstract Factory.

    3. It provides great modularity. Imagine programming a video game, where you would like to add new 
    types of enemies in the future, each of which has different AI functions and can update differently.
    By using a factory method, the controller of the program can call to the factory to create the enemies,
    without any dependency or knowledge of the actual types of enemies. Now, future developers can create 
    new enemies, with new AI controls and new drawing member functions, add it to the factory, 
    and create a level which calls the factory, asking for the enemies by name. Combine this method with an 
    XML description of levels, and developers could create new levels without having to recompile their program. 
    All this, thanks to the separation of creation of objects from the usage of objects.

    4. Allows you to change the design of your application more readily, this is known as loose coupling.

*/