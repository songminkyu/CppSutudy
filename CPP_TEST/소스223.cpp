#include <iostream>
#include <vector>
#include <algorithm>

double find_median(std::vector<double> len)
{
    if (len.size() < 1)
        return std::numeric_limits<double>::signaling_NaN();

    const auto alpha = len.begin();
    const auto omega = len.end();

    // Find the two middle positions (they will be the same if size is odd)
    const auto i1 = alpha + (len.size() - 1) / 2;
    const auto i2 = alpha + len.size() / 2;

    // Partial sort to place the correct elements at those indexes (it's okay to modify the vector,
    // as we've been given a copy; otherwise, we could use std::partial_sort_copy to populate a
    // temporary vector).
    std::nth_element(alpha, i1, omega);
    std::nth_element(i1, i2, omega);

    return 0.5 * (*i1 + *i2);
}


int main()
{
	std::vector<double> v{0,1,2,3,4,5,6 };
	double r = find_median(v);
	std::cout << r << std::endl;    
}