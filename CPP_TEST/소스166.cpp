#include <utility>
#include <algorithm>
#include <string>
#include <iostream>

//https://www.fluentcpp.com/2020/08/07/if-you-see-cut-paste-it-is-rotate/

template<typename It>              // It models LegacyRandomAccessIterator
auto cut_paste(It cut_begin, It cut_end, It paste_begin)
-> std::pair<It, It>           // return the final location of the range [cut_begin, cut_end)
{
    if (paste_begin < cut_begin)   // handles left-rotate(case #1)
    {
        auto const updated_cut_begin = paste_begin;
        auto const updated_cut_end = std::rotate(paste_begin, cut_begin, cut_end);
        return { updated_cut_begin, updated_cut_end };
    }

    if (cut_end < paste_begin)     // handles right-rotate(case #2)
    {
        // Reinterpreting the right-rotate as a left rotate
        auto const updated_cut_begin = std::rotate(cut_begin, cut_end, paste_begin);
        auto const updated_cut_end = paste_begin;
        return { updated_cut_begin, updated_cut_end };
    }
    // else - no-operation required, there will be no change in the relative arrangement of data
    return { cut_begin, cut_end }; // (case #3)
}

void swap_firstname_lastname(std::string& name) // in-place swap
{
    auto const comma_position = std::find(name.begin(), name.end(), ',');         // step #1
    auto const paste_end = std::rotate(name.begin(), comma_position, name.end()); // step #2
    std::rotate(name.begin(), std::next(name.begin()), paste_end);                // step #3
}

void before(std::string const& value)
{
    std::cout << "    Before: " << value << '\n';
}

void after(std::string const& value)
{
    std::cout << "    After: " << value << "\n\n";
}

void func_name(std::string const& name)
{
    std::cout << name << ":\n";
}

void swap_firstname_lastname()
{
    func_name(__func__);
    auto name = std::string{ "ABHINAV,BADOLA" };
    before(name);   // ABHINAV,BADOLA
    swap_firstname_lastname(name);
    after(name);    // BADOLA,ABHINAV
}

// Scenario: paste_begin < cut_begin
void cut_paste_case_1()
{
    func_name(__func__);
    auto value = std::string{ "ABCDEFGHI" };
    before(value); // ABCDEFGHI

    auto const cut_begin = std::find(value.begin(), value.end(), 'C'); // C
    auto const cut_end = value.end();                                  // I
    auto const paste_begin = value.begin();                            // A

    cut_paste(cut_begin, cut_end, paste_begin);
    after(value); // CDEFGHIAB
}

// Scenario: cut_end < paste_begin
void cut_paste_case_2()
{
    func_name(__func__);
    auto value = std::string{ "ABCDEFGHI" };
    before(value); // ABCDEFGHI

    auto const cut_begin = value.begin();                            // A
    auto const cut_end = std::find(value.begin(), value.end(), 'D'); // D
    auto const paste_begin = value.end();                            // I

    cut_paste(cut_begin, cut_end, paste_begin);
    after(value); // DEFGHIABC
}

// Scenario: ( not (paste_begin < cut_begin ) ) and ( not (cut_end < paste_begin ) )
void cut_paste_case_3()
{
    func_name(__func__);
    auto value = std::string{ "ABCDEFGHI" };
    before(value); // ABCDEFGHI

    auto const cut_begin = std::find(value.begin(), value.end(), 'C');   // C
    auto const cut_end = value.end();                                    // I
    auto const paste_begin = std::find(value.begin(), value.end(), 'G'); // G

    cut_paste(cut_begin, cut_end, paste_begin);
    after(value); // ABCDEFGHI
}

void cut_paste()
{
    cut_paste_case_1();
    cut_paste_case_2();
    cut_paste_case_3();
}

int main()
{
    swap_firstname_lastname();
    cut_paste();
    return 0;
}