#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace std;
using namespace web::http;
using namespace web::http::client;
using namespace utility;

void RESTTest3(string_t strCompanyCode)
{
    string_t strDartAuthKey = L"8c92==========================850d13"; // 본인의 전자공시 인증키
    //string_t strURL = L"http://dart.fss.or.kr/api/search.json?auth=" + strDart인증키;
    string_t strURL = L" http://opendart.fss.or.kr/api/search.json?auth=" + strDartAuthKey;
    strURL += L"&crp_cd=" + strCompanyCode + L"&start_dt=19990101&dsp_tp=";
    uri_builder b;
    http_client client(strURL);
    auto requestTask = client.request(methods::GET);
    requestTask.wait();
    http_response response = requestTask.get();
    string_t contents = U("페이지가 없습니다.");
    auto v1 = response.extract_json().get(); // JSON 포맷으로 정보 받음
    auto array = v1[U("list")].as_array(); // list 객체가 반복되어 배열로 저장
    int n = array.size();
    string_t* rpt_nm = new string_t[n];
    for (int i = 0; i < n; i++)
    {
        rpt_nm[i] = array[i].at(U("rpt_nm")).as_string();
        ucout << i + 1 << U(". rpt_nam : ") << rpt_nm[i] << endl; // U(" ") 로 해야 한다. U" " 로하면 숫자로 표시됨.
    }
    ucout << endl << U("Total Count : ") << n << endl;
}

int main()
{
    _setmode(_fileno(stdout), _O_WTEXT); // io.h 와 fcntl.h 필요함.
    // 결과값이 콘솔창에 출력할 수 없는 유니코드 값이 포함되어 있어 이를 보여줄 수 있도록 모드를 바꾸는 함수
    RESTTest3(L"084180");
   
    return 0;
}


