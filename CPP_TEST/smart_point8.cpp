#include <iostream>
#include <memory>

class NVI
{
public:
	void play() { this->do_play(); }
	void stop() { this->do_stop(); }

private:
	virtual void do_play() { std::cout << "NVI::play\n"; }
	virtual void do_stop() { std::cout << "NVI::play\n"; }
};

class A : public NVI
{
private:
	void do_play() override { std::cout << "A::play\n"; }
	void do_stop() override { std::cout << "A::stop\n"; }
};

int main() {
	std::unique_ptr<NVI> ptr = std::make_unique<A>();
	ptr->play();
	ptr->stop();
}