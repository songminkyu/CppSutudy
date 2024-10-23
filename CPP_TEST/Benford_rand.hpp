
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <vector>
class benford_rand {

private:

    template<class RandomIt, class RandomFunc>
    void random_shuffle(RandomIt first, RandomIt last, RandomFunc&& r)
    {
        typename std::iterator_traits<RandomIt>::difference_type i, n;
        n = last - first;
        for (i = n - 1; i > 0; --i) {
            using std::swap;
            swap(first[i], first[r(i + 1)]);
        }
    }
    template< class RandomIt >
    void random_shuffle(RandomIt first, RandomIt last)
    {
        typename std::iterator_traits<RandomIt>::difference_type i, n;
        n = last - first;
        for (i = n - 1; i > 0; --i) {
            using std::swap;
            swap(first[i], first[std::rand() % (i + 1)]);
            // rand() % (i+1) isn't actually correct, because the generated number
            // is not uniformly distributed for most values of i. A correct implementation
            // will need to essentially reimplement C++11 std::uniform_int_distribution,
            // which is beyond the scope of this example.
        }
    }

    int ms_time() {
        //Get current time in microseconds
        namespace c = std::chrono;
        long int nanos = static_cast<long int>(c::duration_cast<c::nanoseconds>(c::high_resolution_clock::now().time_since_epoch()).count());
        return abs((int)nanos);
    }

    int time_rand(int min, int max) {
        //Generate random number from microsecond time stamps
        int nanos = ms_time();
        for (int i = 3; i < 10; i++) {
            if (nanos % i == 0) {
                return min + (nanos) % (int)(max - min + 1);
            }
            nanos = ms_time();
        }

        return min + (nanos) % (int)(max - min + 1);
    }

    double get_probability(double n, int digit = 1) {
        //Probability a number will exist based on Bendford's law
        double probability = 0;
        if (digit == 1) {
            if (n == 0.0) {
                probability = 0;
            }
            else {
                probability = log10(1 + (1 / n)); //Benford's law probability rule
            }
        }
        else if (digit < 4) { //if digit is 2-3 use Benford's law generalized past 1 digit
            double max_value = pow(10, (digit - 1)) - 1;
            double k = 0;
            for (int i = 0; i < max_value; i++) {
                k += pow(10, (digit - 2));
                probability += log10(1 + (1 / ((10 * k) + n)));
            }
        }
        else { //Digits greater than four have probability of 10% for each number
            probability = 0.1;
        }
        return probability;
    }

public:
    int rand(int pool_size = 100000) {
        unsigned int first_digit_arr_size = 0;

        //Determine size of random number pool for the first digit
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0);
            first_digit_arr_size += (int)((probability * pool_size) + 0.5);
        }
            
        //int first_digit_pool[_first_digit_arr_size];
        std::vector<int> first_digit_pool(first_digit_arr_size + 1);

        int arr_counter = 0;
        //Creates pool of numbers following Benford's law to pull randomly from
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0);
            int n_norm_probability = (int)((probability * pool_size) + 0.5);
            for (int p = 0; p < n_norm_probability; p++) {
                first_digit_pool[arr_counter] = i;
                arr_counter += 1;
            }
        }
        random_shuffle(&first_digit_pool[0], &first_digit_pool[first_digit_arr_size]);


        //Determine size of second/third digit random number pool
        unsigned int second_digit_arr_size = 0;
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 2);
            second_digit_arr_size += (int)((probability * pool_size) + 0.5);
        }

        std::vector<int> second_digit_pool( second_digit_arr_size + 1);
        arr_counter = 0;
        //Creates pool of numbers following Benford's law to pull randomly from
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 2);
            int n_norm_probability = (int)((probability * pool_size) + 0.5);
            for (int p = 0; p < n_norm_probability; p++) {
                second_digit_pool[arr_counter] = i;
                arr_counter += 1;
            }
        }
        random_shuffle(&second_digit_pool[0], &second_digit_pool[second_digit_arr_size]);


        //Determine size of second/third digit random number pool
        unsigned int third_digit_arr_size = 0;
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 3);
            third_digit_arr_size += (int)((probability * pool_size) + 0.5);
        }

        std::vector<int> third_digit_pool(third_digit_arr_size + 1);
        
        arr_counter = 0;
        //Creates pool of numbers following Benford's law to pull randomly from
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 3);
            int n_norm_probability = (int)((probability * pool_size) + 0.5);
            for (int p = 0; p < n_norm_probability; p++) {
                third_digit_pool[arr_counter] = i;
                arr_counter += 1;
            }
        }
        random_shuffle(&third_digit_pool[0], &third_digit_pool[third_digit_arr_size]);

        //Determine size of second/third digit random number pool
        unsigned int fourth_digit_arr_size = 0;
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 4);
            fourth_digit_arr_size += (int)((probability * pool_size) + 0.5);
        }

        std::vector<int> fourth_digit_pool(fourth_digit_arr_size + 1);
        arr_counter = 0;
        //Creates pool of numbers following Benford's law to pull randomly from
        for (int i = 0; i < 10; i++) {
            double probability = get_probability(i * 1.0, 4);
            int n_norm_probability = (int)((probability * pool_size) + 0.5);
            for (int p = 0; p < n_norm_probability; p++) {
                fourth_digit_pool[arr_counter] = i;
                arr_counter += 1;
            }
        }
        random_shuffle(&fourth_digit_pool[0], &fourth_digit_pool[fourth_digit_arr_size]);

        int rand_size_min = 1;
        int rand_size_max = 9;
        int rand_size = time_rand(rand_size_min, rand_size_max); //Determines number of digits within random number
        std::string rand_str;
        for (int i = 0; i < rand_size; i++) {
            if (i == 0) {
                int rand_index_min = 1;
                int rand_index_max = first_digit_arr_size;
                int rand_index = time_rand(rand_index_min, rand_index_max);
                rand_str += std::to_string(first_digit_pool[rand_index]);
            }
            else if (i == 1) {
                int rand_index_min = 1;
                int rand_index_max = second_digit_arr_size;
                int rand_index = time_rand(rand_index_min, rand_index_max);
                rand_str += std::to_string(second_digit_pool[rand_index]);
            }
            else if (i == 2) {
                int rand_index_min = 1;
                int rand_index_max = third_digit_arr_size;
                int rand_index = time_rand(rand_index_min, rand_index_max);
                rand_str += std::to_string(third_digit_pool[rand_index]);
            }
            else {
                int rand_index_min = 1;
                int rand_index_max = fourth_digit_arr_size;
                int rand_index = time_rand(rand_index_min, rand_index_max);
                rand_str += std::to_string(fourth_digit_pool[rand_index]);
            }

        }
        std::cout << rand_str << std::endl;
        int rand = std::stol(rand_str);
        return rand;
    }
};