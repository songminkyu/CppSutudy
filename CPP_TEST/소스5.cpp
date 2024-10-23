#include <iostream>
#include <string>
#include <locale>
#include <cvt/8859_1>
#include <cvt/utf8>

template<typename ISO_ICE>
std::wstring _Convert_stringoid_with_locale_to_wide(const std::string_view _Input)
{		
	ISO_ICE _Facet;

	std::wstring _Output(_Input.size(), L'\0');

	for (;;)
	{
		mbstate_t _State{};
		const char* const _From_begin = _Input.data();
		const char* const _From_end = _From_begin + _Input.size();
		const char* _From_next = nullptr;
		wchar_t* const _To_begin = _Output.data();
		wchar_t* const _To_end = _To_begin + _Output.size();
		wchar_t* _To_next = nullptr;

		const auto _Result = _Facet.in(_State, _From_begin, _From_end, _From_next, _To_begin, _To_end, _To_next);
		
		if (_From_next < _From_begin || _From_next > _From_end || _To_next < _To_begin || _To_next > _To_end)
		{
			throw std::system_error(std::make_error_code(std::errc::invalid_argument));
		}

		switch (_Result)
		{
		case std::codecvt_base::ok:
			_Output.resize(static_cast<size_t>(_To_next - _To_begin));
			return _Output;
		case std::codecvt_base::partial:
			if ((_From_next == _From_end && _To_next != _To_end) || _Output.size() > _Output.max_size() / 2)
			{
				throw std::system_error(std::make_error_code(std::errc::invalid_argument));
			}

			_Output.resize(_Output.size() * 2);

			break;
		case std::codecvt_base::error:
		case std::codecvt_base::noconv:
		default:
			throw std::system_error(std::make_error_code(std::errc::invalid_argument));

		}
	}
}

std::string iso_8859_1_to_utf8(std::string& str)
{
	std::string strOut;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		uint8_t ch = *it;
		if (ch < 0x80) {
			strOut.push_back(ch);
		}
		else {
			strOut.push_back(0xc0 | ch >> 6);
			strOut.push_back(0x80 | (ch & 0x3f));
		}
	}
	return strOut;
}

int main()
{
	 
	std::wstring ws = _Convert_stringoid_with_locale_to_wide<stdext::cvt::codecvt_8859_1<wchar_t>>("songminkyu");
	std::size_t sz = ws.length();
	std::cout << sz << std::endl;
	std::wcout << ws.c_str() << std::endl;

}