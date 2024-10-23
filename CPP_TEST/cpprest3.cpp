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

void RESTTest(string_t words)
{
    string_t pathString = U(R"(format=json&action=query&prop=revisions&titles=)");
    pathString += uri::encode_uri(words);
    pathString += U(R"(&rvprop=content)");
    uri_builder b;
    b.set_scheme(U("http"));
    b.set_host(U("en.wikipedia.org"));
    b.set_path(U("w/api.php"));
    b.set_query(pathString);
    http_client client(b.to_string());
    auto requestTask = client.request(methods::GET);
    requestTask.wait();
    http_response response = requestTask.get();
    string_t title;
    string_t contents = U("페이지가 없습니다.");
    auto v1 = response.extract_json().get();
    auto v2 = v1[U("query")];
    auto v3 = v2[U("pages")];
    auto v4 = v3.as_object().begin();
    title = (v4->second)[U("title")].as_string();
    auto v5 = (v4->second)[U("revisions")];
    if (!v5.is_null()) {
        auto v6 = v5.as_array()[0];
        contents = v6[U("*")].as_string();
    }
    //ucout << endl << contents.c_str() << endl << endl;
    //ucout << U("제목 : ") << title << endl;
    //ucout << U("컨텐츠 사이즈 : ") << contents.size() << U(" bytes") << endl;
    //ucout << endl << endl;

    string str = "";
    str.assign(title.begin(), title.end()); // wstring -> string 변환
    cout << "제목 : " << str << endl;
    cout << "컨텐츠 사이즈 : " << contents.size() << " bytes" << endl;
}

int main()
{
    //_setmode(_fileno(stdout), _O_WTEXT); // io.h 와 fcntl.h 필요함.
    // 위키피디아 결과값이 콘솔창에 출력할 수 없는 유니코드 값이 포함되어 있어 이를 보여줄 수 있도록 모드를 바꾸는 함수

    RESTTest(L"keyboard"); // keyboard 로 검색
   // _gettchar();
    return 0;
}


