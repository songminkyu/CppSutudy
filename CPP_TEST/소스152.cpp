#include <iostream>
#include <vector>

using namespace std;


template <typename Self>
struct SomeNeurons {
    template <typename T>
    void connect_to(T& other);
};
struct Neuron : SomeNeurons<Neuron> {
    vector<Neuron*>     in, out;
    uint32_t            id;
    Neuron() {
        static int id = 1;
        this->id = id++;
    }
    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }
};
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer> {
    NeuronLayer(int count) {
        while (count-- > 0)
            emplace_back(Neuron{});
    }
};
/* ----------------------------------------------------------------------- */
template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T& other) {
    for (Neuron& from : *static_cast<Self*>(this)) {
        for (Neuron& to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}
/* ----------------------------------------------------------------------- */
template <typename Self>
ostream& operator<<(ostream& os, SomeNeurons<Self>& object) {
    for (Neuron& obj : *static_cast<Self*>(&object)) {
        for (Neuron* n : obj.in)
            os << n->id << "\t-->\t[" << obj.id << "]" << endl;
        for (Neuron* n : obj.out)
            os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
}
int main() {
    Neuron n1, n2;
    NeuronLayer l1{ 1 }, l2{ 2 };
    n1.connect_to(l1); // Scenario 1: Neuron connects to Layer
    l2.connect_to(n2); // Scenario 2: Layer connects to Neuron
    l1.connect_to(l2); // Scenario 3: Layer connects to Layer
    n1.connect_to(n2); // Scenario 4: Neuron connects to Neuron
    cout << "Neuron " << n1.id << endl << n1 << endl;
    cout << "Neuron " << n2.id << endl << n2 << endl;
    cout << "Layer " << endl << l1 << endl;
    cout << "Layer " << endl << l2 << endl;
    return EXIT_SUCCESS;
}