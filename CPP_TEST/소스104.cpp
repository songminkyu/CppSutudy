#include <iostream>
#include <variant>

struct Cutter1 { void process() { std::cout << "Cutter1" << std::endl; } };
struct Cutter2 { void process() { std::cout << "Cutter2" << std::endl; } };
struct Cutter3 { void process() { std::cout << "Cutter3" << std::endl; } };
struct Cutter4 { void process() { std::cout << "Cutter4" << std::endl; } };

struct Luther {
	using value_type = std::variant<Cutter1, Cutter2, Cutter3, Cutter4>;
	value_type value_{};
	bool isdone = false;

	bool go_back_to_work() {
		std::visit([](auto v) {v.process(); }, value_);

		switch (value_.index())
		{
		case 0:value_ = Cutter2{}; break;
		case 1:value_ = Cutter3{}; break;
		case 2:value_ = Cutter4{}; break;
		case 3:isdone = true; break;
		default:
			break;
		}
		return isdone;
	}
};

int main()
{
	Luther process;
	while (!process.go_back_to_work());
}