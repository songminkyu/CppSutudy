#include <taskflow/taskflow/taskflow.hpp>  // Taskflow is header-only


void test_0()
{
    tf::Executor executor;
    tf::Taskflow taskflow;

    auto [A, B, C, D] = taskflow.emplace(
        []() { std::cout << "TaskA\n"; },               //  task dependency graph
        []() { std::cout << "TaskB\n"; },               // 
        []() { std::cout << "TaskC\n"; },               //          +---+          
        []() { std::cout << "TaskD\n"; }                //    +---->| B |-----+   
    );                                                 //    |     +---+     |
                                                       //  +---+           +-v-+ 
    A.precede(B);  // A runs before B                  //  | A |           | D | 
    A.precede(C);  // A runs before C                  //  +---+           +-^-+ 
    B.precede(D);  // B runs before D                  //    |     +---+     |    
    C.precede(D);  // C runs before D                  //    +---->| C |-----+    
                                                       //          +---+          
    executor.run(taskflow).wait();

}

void Dynamic_Tasking()
{
    tf::Taskflow tf;
   
    tf::Task A = tf.emplace([]() {}).name("A");
    tf::Task C = tf.emplace([]() {}).name("C");
    tf::Task D = tf.emplace([]() {}).name("D");

    // create a subflow graph (dynamic tasking)
    tf::Task B = tf.emplace([](tf::Subflow& subflow) {
        tf::Task B1 = subflow.emplace([]() {}).name("B1");
        tf::Task B2 = subflow.emplace([]() {}).name("B2");
        tf::Task B3 = subflow.emplace([]() {}).name("B3");
        B1.precede(B3);
        B2.precede(B3);
        }).name("B");

        A.precede(B);  // B runs after A 
        A.precede(C);  // C runs after A 
        B.precede(D);  // D runs after B 
        C.precede(D);  // D runs after C 

}
void Conditional_Tasking()
{
    tf::Taskflow tf;
    tf::Executor executor;

    tf::Task init = tf.emplace([]() {}).name("init");
    tf::Task stop = tf.emplace([]() {}).name("stop");

    // creates a condition task that returns 0 or 1
    tf::Task cond = tf.emplace([]() {
        std::cout << "flipping a coin\n";
        return rand() % 2;
        }).name("cond");

    // creates a feedback loop
    init.precede(cond);
    cond.precede(cond, stop);  // cond--0-->cond, cond--1-->stop

    executor.run(tf).wait();
}

void Composable_Tasking()
{
    tf::Taskflow f1, f2;

    auto [f1A, f1B] = f1.emplace(
        []() { std::cout << "Task f1A\n"; },
        []() { std::cout << "Task f1B\n"; }
    );
    auto [f2A, f2B, f2C] = f2.emplace(
        []() { std::cout << "Task f2A\n"; },
        []() { std::cout << "Task f2B\n"; },
        []() { std::cout << "Task f2C\n"; }
    );
    auto f1_module_task = f2.composed_of(f1);

    f1_module_task.succeed(f2A, f2B)
        .precede(f2C);
}
int main() {

    test_0();
    Dynamic_Tasking();
    Conditional_Tasking();
    Composable_Tasking();

    return 0;
}