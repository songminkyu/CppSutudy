#include <future>
/*
C++17 introduces the by-value capture of *this. The proposal document P0018R3 argues that by-value 
capture of *this is significantly important for concurrent applications that need to do asynchronous 
dispatch of closures.

Consider the following lambda that captures this and executes asynchronously in a different thread. 
The this pointer might be invalidated by the time lambda runs:
*/
struct Processor {
    //Some state data..

    std::future<void> process(/*args*/) {
        //Pre-process...
        //Do the data processing asynchronously
        return
            std::async(std::launch::async,
                [=](/*data*/) {
                    /*
                      Runs in a different thread.
                     'this' might be invalidated here
                    */

                    //process data
                });
    }
};

auto caller() {
    Processor p;
    return p.process(/*args*/);
}

int main()
{

}