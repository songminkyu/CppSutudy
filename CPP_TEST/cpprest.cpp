// cpprest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <windows.h>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <nlohmann/json.hpp>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;
using nljson = nlohmann::json;

void GetHttp()
{	
	http_client client(U("https://ethgasstation.info/json/ethgasAPI.json"));
	auto resp = client.request(U("GET")).get();

	wcout << U("STATUS : ") << resp.status_code() << endl;
	wcout << "content-type : " << resp.headers().content_type() << endl;
	wcout << resp.extract_string(true).get() << endl;	
	
}
void GetJsonHttp()
{
	http_client client(U("https://ethgasstation.info/json/ethgasAPI.json"));
	auto resp = client.request(U("GET")).get();
	wcout << U("STATUS : ") << resp.status_code() << endl;
	wcout << "content-type : " << resp.headers().content_type() << endl;	
	auto value = resp.extract_json().get();

	std::wcout << value[U("fast")].as_integer() << std::endl;
}
void GetHttpAsync()
{
	http_client client(U("https://ethgasstation.info/json/predictTable.json"));
	nljson j;
	client.request(U("GET")).then([&](http_response resp) {
		wcout << U("STATUS : ") << resp.status_code() << endl;
		wcout << "content-type : " << resp.headers().content_type() << endl;
		resp.extract_string(true).then([&](string_t sBoby) {
			wcout << sBoby << endl;
			j = nljson::parse(sBoby);					
		}).wait();	
	}).wait();

	/*int fast = j["fast"];
	std::cout << fast << std::endl;*/

}

nljson GetHttpAsync(std::wstring url)
{
	http_client client(url.c_str());
	nljson j;
	client.request(U("GET")).then([&](http_response resp) {
		wcout << U("STATUS : ") << resp.status_code() << endl;
		wcout << "content-type : " << resp.headers().content_type() << endl;
		resp.extract_string(true).then([&](string_t sBoby) {
			//wcout << sBoby << endl;
			j = nljson::parse(sBoby);
		}).wait();
	}).wait();

	return j;		
}


double EthToCon(double eth)
{
	double ConCount;
	double EthCount;
	nljson ConTransactionHistory;
	nljson EthTransactionHistory;
	ConTransactionHistory = GetHttpAsync(U("https://api.bithumb.com/public/transaction_history/CON"));
	EthTransactionHistory = GetHttpAsync(U("https://api.bithumb.com/public/transaction_history/ETH"));

	std::string ConPrice = ConTransactionHistory["data"][19]["price"];
	std::string EthPrice = EthTransactionHistory["data"][19]["price"];

	EthCount = std::stod(EthPrice) * eth;
	ConCount = EthCount / std::stod(ConPrice);

	return ConCount;
}

double ConToEth(double Con)
{
	double ConCount;
	double EthCount;
	nljson ConTransactionHistory;
	nljson EthTransactionHistory;
	ConTransactionHistory = GetHttpAsync(U("https://api.bithumb.com/public/transaction_history/CON"));
	EthTransactionHistory = GetHttpAsync(U("https://api.bithumb.com/public/transaction_history/ETH"));

	std::string ConPrice = ConTransactionHistory["data"][19]["price"];
	std::string EthPrice = EthTransactionHistory["data"][19]["price"];

	ConCount = std::stod(ConPrice) * Con;
	EthCount = ConCount / std::stod(EthPrice);
		
	return EthCount;
}


double GetKrwToUsd()
{
	double ExchangeRate = 0;
	nljson CON_Price = GetHttpAsync(U("https://api.bithumb.com/public/transaction_history/CON"));
	nljson KrwToUsdExchangeRate = GetHttpAsync(U("https://earthquake.kr:23490/query/KRWUSD"));

	std::string ConPrice = CON_Price["data"][19]["price"];
	double KrwToUsd = KrwToUsdExchangeRate["KRWUSD"][6];
	
	ExchangeRate = std::stod(ConPrice) * KrwToUsd;
	return ExchangeRate;
}

int main(int argc, char* argv[])
{
	wcout.imbue(locale("kor"));  // windows only

	GetJsonHttp();

	double r = ConToEth(5000);
	std::cout << "Con To Eth : " << r << std::endl;

	r = GetKrwToUsd();
	std::cout << "GetKrwToUsd : " << r << std::endl;
	
	
/*
	for (int i = 0; i < 20; i++)
	{
		std::cout << "transaction_date : " << ConTransactionHistory["data"][i]["transaction_date"] << std::endl;
		std::cout << "type : " << ConTransactionHistory["data"][i]["type"] << std::endl;
		std::cout << "units_traded : " << ConTransactionHistory["data"][i]["units_traded"] << std::endl;
		std::cout << "price : " << ConTransactionHistory["data"][i]["price"] << std::endl;
		std::cout << "total : " << ConTransactionHistory["data"][i]["total"] << std::endl;
		std::cout << "*******************************************" << std::endl;
	}
*/



	return 0;
}