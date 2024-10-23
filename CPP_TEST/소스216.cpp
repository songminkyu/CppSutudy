#include <date/date.h>
#include <iostream>

int main()
{
	using namespace date;
	using namespace std::chrono_literals;

	std::cout << std::boolalpha << std::endl;

	auto timeofDay = date::hh_mm_ss(10.5h + 98min + 2020s + 0.5s);

	std::cout << "timeofDay : " << timeofDay << std::endl;

	std::cout << std::endl;

	std::cout << "timeOfDay.hours() :" << timeofDay.hours() << std::endl;
	std::cout << "timeOfDay.minutes() :" << timeofDay.minutes() << std::endl;
	std::cout << "timeofDay.seconds() : " << timeofDay.seconds() << std::endl;
	std::cout << "timeofDay.subseconds() : " << timeofDay.subseconds() << std::endl;
	std::cout << "timeofDay.to_duration() : " << timeofDay.to_duration() << std::endl;

	std::cout << std::endl;

	std::cout << "date::hh_mm_ss(45700.5s): " << date::hh_mm_ss(45700.5s) << '\n';  

	std::cout << std::endl;

	std::cout << "date::is_am(5h): " << date::is_am(5h) << std::endl;                   
	std::cout << "date::is_am(15h): " << date::is_am(15h) << std::endl;             

	std::cout << std::endl;

	std::cout << "date::make12(5h): " << date::make12(5h) << std::endl;               
	std::cout << "date::make12(15h): " << date::make12(15h) << std::endl;    

	std::cout << std::endl;

	timeofDay = date::time_of_day(10.h + 98min + 2020s + 0.5s); // C++20

	std::cout << "timeofDay (c++20) : " << timeofDay << std::endl;


}