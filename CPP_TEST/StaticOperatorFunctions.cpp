#include "StaticOperatorFunctions.h"

#if _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#endif
#endif

CStaticOperatorFunctions::CStaticOperatorFunctions()
{
}

CStaticOperatorFunctions::~CStaticOperatorFunctions()
{
}

std::wstring CStaticOperatorFunctions::replace_all(const std::wstring & message, const std::wstring & pattern, const std::wstring & replace)
{
	std::wstring result = message;
	std::wstring::size_type pos = 0;
	std::wstring::size_type offset = 0;
	while ((pos = result.find(pattern, offset)) != std::wstring::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
		offset = pos + replace.size();
	}
	return result;
}

std::string CStaticOperatorFunctions::replace_all(const std::string & message, const std::string & pattern, const std::string & replace)
{
	std::string result = message;
	std::string::size_type pos = 0;
	std::string::size_type offset = 0;
	while ((pos = result.find(pattern, offset)) != std::string::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
		offset = pos + replace.size();
	}
	return result;
}