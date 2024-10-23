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
//
//USES_CONVERSION;
//std::string s1;
//std::wstring s2(A2W(s1.c_str())); // wstring <- string
//for (int i = 0; i < n; i++)
//{
//    rpt_nm[i] = array[i].at(U("rpt_nm")).as_string();
//    strStr = W2A(rpt_nm[i].c_str()); // string <- wstring 
//    cout << i + 1 << ". rpt_nam : " << strStr << endl;
//}
//cout << endl << "Total Count : " << n << endl;
//CString str = rpt_nm[0].c_str();
//AfxMessageBox(str);
//



void RESTTest4(string_t strCompanyCode)
{
    string_t strDartAuth = L"8c92...70...";
    string_t strURL = L"http://dart.fss.or.kr/api/search.json?auth=" + strDartAuth;
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
    CString str = rpt_nm[0].c_str();
    AfxMessageBox(str);
}

int main()
{
    _setmode(_fileno(stdout), _O_WTEXT); // io.h 와 fcntl.h 필요함.
    // 결과값이 콘솔창에 출력할 수 없는 유니코드 값이 포함되어 있어 이를 보여줄 수 있도록 모드를 바꾸는 함수
    RESTTest4(L"084180");
    _gettchar();
    return 0;
}


