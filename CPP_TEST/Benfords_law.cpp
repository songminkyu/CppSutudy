
#include <vector>
#include <Benford_rand.hpp>

/*
벤포드의 법칙(Benford's law)은 실세계에서 존재하는 많은 수치 데이터의 10진법 값에서 수의 첫째 자리의 확률 분포를 관찰한 결과, 
첫째 자리 숫자가 작을 확률이 크다는 법칙이다. 벤포드의 법칙을 따르는 데이터 집합에 등장하는 수들의 첫째 자리가 1일 확률은 약 
30%인 데 반해, 9가 첫째 자리로 등장할 확률은 5% 정도밖에 되지 않는다. 만약 1부터 9까지의 숫자가 수의 맨 앞자리에 등장할 확률이
균등분포를 따른다면, 각 숫자는 약 11.1%의 확률로 맨 앞자리에 등장하여야 할 것이다. 벤포드의 법칙은 또한 수의 둘째 이후 자리의
확률 분포나 숫자 조합에 대한 확률 분포도 예측할 수 있다.

벤포드의 법칙은 굉장히 다양한 종류의 데이터에 적용된다. 예를 들어, 전기요금 고지서, 도로명 주소, 주식 가격, 주택 가격, 인구수,
사망률, 강의 길이, 물리 상수와 수학 상수 등 다양한 데이터에 등장하는 수들이 벤포드의 법칙을 따른다.

이 법칙의 이름은 물리학자 프랭크 벤포드의 이름을 따서 지어졌다. 벤포드는 1938년에 "이례적인 숫자들에 관한 법칙"(The Law of 
Anomalous Numbers)이라는 논문에서 처음 벤포드의 법칙을 언급했다. 그러나 사실 1881년에 사이먼 뉴컴도 같은 법칙을 이야기한 적이 있다.

P(d) = log10(d + 1) - log10(d)
     = log10( d / d + 1 )
     = log10( 1 + d / 1 )


Benford 법칙의 제약에 기반한 C ++ 난수 생성기

간단히 말해, Newcomb-Benford의 법칙에 따르면 숫자의 첫 번째 숫자는 2보다 1로 시작할 가능성이 더 높고 3보다 2로 시작할 가능성이 더 높습니다. 
Newcomb이 로그 테이블 책의 페이지가 결과가 1로 시작하는 페이지에서 더 많이 마모되었음을 발견했을 때.

이 C ++ 코드는 Benford의 법칙에 따라 주어진 숫자가 존재해야 할 확률을 기반으로 난수 생성을 수행합니다.

*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <map>

int count_digit(int n) {

    unsigned int number_of_digits = 0;

    do {
        ++number_of_digits;
        n /= 10;

    } while (n);
    return number_of_digits;

    return 1;
}



int main(int argc, const char* argv[]) {

    int seed = 10000;
    benford_rand b_rand;
    std::map<int, int> int_map;

    for (int i = 0; i < 10; i++) {
        int_map[i] = 0;
    }

    for (int i = 0; i < 10; i++) {
        int ran_num = b_rand.rand(seed);

        for (int p = 0; p < count_digit(ran_num); p++) {
            int div_num = pow(10, p);
            int n = (ran_num / div_num) % 10;
            int_map[n] += 1;
        }
    }

    for (int i = 0; i < 10; i++) {
        std::cout << "Digit: " << i << " Count: " << int_map[i] << std::endl;
    }

    return 0;
}