#include <cmath>
#include <iostream>

struct point2D {
	int x;
	int y;
};

int main()
{
	point2D p2d[4];

	//A
	p2d[0].x = 10; 
	p2d[0].y = 10;

	//B
	p2d[1].x = 40;
	p2d[1].y = 40;

	//C
	p2d[2].x = 20;
	p2d[2].y = 50;


	std::cout << sqrt(pow((p2d[1].x - p2d[0].x), 2) + pow((p2d[1].y - p2d[0].y), 2)) << std::endl;  //AB
	std::cout << sqrt(pow((p2d[2].x - p2d[0].x), 2) + pow((p2d[2].y - p2d[0].y), 2)) << std::endl;  //AC
	std::cout << sqrt(pow((p2d[2].x - p2d[1].x), 2) + pow((p2d[2].y - p2d[1].y), 2)) << std::endl;  //BC
}