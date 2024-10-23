#pragma once

#include <vector>
#include <list>
#include <map>
#include <variant>
#include <complex>
#include <array>
#include <col/src/stringt/stringt.h>

#ifdef __linux__
#include "tuple_operator.h"
#endif

#if UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif

#ifndef INCLUDE_NLOHMANN_JSON
#define INCLUDE_NLOHMANN_JSON
#endif // !INCLUDE_NLOHMANN

#ifndef INCLUDE_RAPID_JSON
#define INCLUDE_RAPID_JSON
#endif // !INCLUDE_RAPID_JSON


#include <col/src/col_stream/bstream.h>

#ifdef INCLUDE_NLOHMANN_JSON
//#include <nlohmann/json.hpp>
#endif

#ifdef INCLUDE_RAPID_JSON
//#include <rapidjson/rapidjson.h>
//#include <rapidjson/document.h>     // rapidjson's DOM-style API
//#include <rapidjson/prettywriter.h> // for stringify JSON
//#include <cstdio>
#endif

#ifdef GUID_DEFINED
template< typename _Elem, typename _Traits >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const GUID& guid)
{
	_Ostr << guid.Data1 << guid.Data2 << guid.Data3;
	_Ostr.write((const char*)(guid.Data4), 8);
	return _Ostr;
}

template< typename _Elem, typename _Traits >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, GUID& guid)
{
	_Istr >> guid.Data1 >> guid.Data2 >> guid.Data3;
	_Istr.read((_Elem*)(guid.Data4), 8);
	return _Istr;
}
#endif

#ifdef _MINWINBASE_
template< typename _Elem, typename _Traits >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const SYSTEMTIME& _St)
{
	_Ostr << _St.wYear << _St.wMonth << _St.wDayOfWeek << _St.wDay << _St.wHour << _St.wMinute << _St.wSecond << _St.wMilliseconds;
	return _Ostr;
}

template< typename _Elem, typename _Traits >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, SYSTEMTIME& _St)
{
	_Istr >> _St.wYear >> _St.wMonth >> _St.wDayOfWeek >> _St.wDay >> _St.wHour >> _St.wMinute >> _St.wSecond >> _St.wMilliseconds;
	return _Istr;
}
#endif

template< typename _Elem, typename _Traits, typename _Alloc >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::basic_string< _Elem, _Traits, _Alloc >& _Str)
{
	_Ostr << (unsigned long)_Str.size() << _Str.c_str();
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Alloc >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::basic_string< _Elem, _Traits, _Alloc >& _Str)
{
	unsigned long ulSize;
	_Istr >> ulSize;

	_Str.clear();
	_Str.reserve(ulSize);

	typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();
	for (; ulSize > 0; --ulSize, _Meta = _Istr.rdbuf()->snextc())
	{
		if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			throw std::exception();
		else
			_Str.append(1, _Traits::to_char_type(_Meta));
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::vector< _Ty >& _Tys)
{
	unsigned long ulCount = (unsigned long)(_Tys.size());
	_Ostr << ulCount;

	typename std::vector< _Ty >::const_iterator cit;
	for (cit = _Tys.begin(); cit != _Tys.end(); ++cit)
		_Ostr << *cit;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::vector< _Ty >& _Tys)
{
	_Tys.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> t;
		_Tys.push_back(t);
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::list< _Ty >& _Tys)
{
	unsigned long ulCount = (unsigned long)(_Tys.size());
	_Ostr << ulCount;

	typename std::list< _Ty >::const_iterator cit;
	for (cit = _Tys.begin(); cit != _Tys.end(); ++cit)
		_Ostr << *cit;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::list< _Ty >& _Tys)
{
	_Tys.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> t;
		_Tys.push_back(t);
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Kty, typename _Ty, typename _Pr, typename _Alloc >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::map< _Kty, _Ty, _Pr, _Alloc >& _Map)
{
	unsigned long ulCount = (unsigned long)(_Map.size());
	_Ostr << ulCount;

	typename std::map< _Kty, _Ty, _Pr, _Alloc >::const_iterator cit;
	for (cit = _Map.begin(); cit != _Map.end(); ++cit)
		_Ostr << cit->first << cit->second;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Kty, typename _Ty, typename _Pr, typename _Alloc >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::map< _Kty, _Ty, _Pr, _Alloc >& _Map)
{
	_Map.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Kty k;
	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> k >> t;
		_Map.insert(std::make_pair(k, t));
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty1, typename _Ty2 >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::pair< _Ty1, _Ty2 >& _Pair)
{
	_Ostr << _Pair.first << _Pair.second;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty1, typename _Ty2 >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::pair< _Ty1, _Ty2 >& _Pair)
{
	_Istr >> _Pair.first >> _Pair.second;
	return _Istr;
}

template< typename _Elem, typename _Traits, typename _This, typename... _Rest >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::tuple< _This, _Rest... >& _Tuple)
{
#ifdef __linux__
	tuple_bostream<_Elem, _Traits, sizeof...(_Rest), _This, _Rest...>::reference(_Ostr, _Tuple);
#elif _WIN32
	_Ostr << _Tuple._Myfirst._Val << _Tuple._Get_rest();
#endif // DEBUG


	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _This, typename... _Rest >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::tuple< _This, _Rest... >& _Tuple)
{
#ifdef __linux__
	tuple_bistream<_Elem, _Traits, sizeof...(_Rest), _This, _Rest...>::reference(_Istr, _Tuple);
#elif _WIN32
	_Istr >> _Tuple._Myfirst._Val >> _Tuple._Get_rest();
#endif

	return _Istr;
}

template< typename _Elem, typename _Traits >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::tuple<>& _Tuple)
{
	COL_UNREFERENCE_PARAMETER(_Tuple);
	return _Ostr;
}

template< typename _Elem, typename _Traits >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::tuple<>& _Tuple)
{
	COL_UNREFERENCE_PARAMETER(_Tuple);
	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty, std::size_t size >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::array< _Ty, size >& _Array)
{
	unsigned long ulCount = (unsigned long)(_Array.size());
	_Ostr << ulCount;

	for (unsigned long i = 0; i < ulCount; i++)
		_Ostr << _Array[i];

	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty, std::size_t size >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::array< _Ty, size >& _Array)
{
	unsigned long ulCount;
	_Istr >> ulCount;

	for (unsigned long i = 0; i < ulCount; i++)
		_Istr >> _Array[i];

	return _Istr;
}
//
//#ifdef INCLUDE_NLOHMANN_JSON
//
///**********************nlohmann json *****************************/
//template< typename _Elem, typename _Traits >
//basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const nlohmann::json & _j)
//{
//	_Ostr << _j.dump();
//	return _Ostr;
//}
//
//template< typename _Elem, typename _Traits>
//basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, nlohmann::json & _j)
//{
//	std::string s;
//	_Istr >> s;
//	_j = nlohmann::json::parse(s);
//	return _Istr;
//}
//
//#endif // INCLUDE_NLOHMANN
//

/**********************_RAPID_JSON_PARSER *****************************/
typedef struct _RAPID_JSON_PARSER {
	char buffer[260];
	unsigned long size;
}RAPID_JSON_PARSER, *PRAPID_JSON_PARSER;

template< typename _Elem, typename _Traits >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const RAPID_JSON_PARSER & _rj)
{
	unsigned long ulCount = _rj.size;

	_Ostr << ulCount;

	for (unsigned long i = 0; i < ulCount; i++)
		_Ostr << _rj.buffer[i];

	return _Ostr;
}

template< typename _Elem, typename _Traits>
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, RAPID_JSON_PARSER & _rj)
{
	unsigned long ulCount;
	_Istr >> ulCount;
	for (unsigned long i = 0; i < ulCount; i++)
		_Istr >> _rj.buffer[i];

	return _Istr;
}


typedef struct _BINARY
{
	unsigned long m_ulSize;
	unsigned char* m_pData;

	_BINARY()
		: m_ulSize(0), m_pData(NULL)
	{}

	~_BINARY()
	{
		Release();
	}

	void Set(unsigned long ulSize, const unsigned char* pData)
	{
		Release();
		m_ulSize = ulSize;
		m_pData = new unsigned char[m_ulSize];
		memcpy(m_pData, pData, m_ulSize);
	}

	void Reserve(unsigned long ulSize)
	{
		Release();
		m_ulSize = ulSize;
		m_pData = new unsigned char[m_ulSize];
	}

	void Release()
	{
		if (m_pData)
		{
			delete[] m_pData;
			m_pData = NULL;
		}
		m_ulSize = 0;
	}
} BINARY, *PBINARY;

template< typename _Elem, typename _Traits >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const BINARY& _Bi)
{
	_Ostr << _Bi.m_ulSize;
	_Ostr.write((const _Elem*)(_Bi.m_pData), _Bi.m_ulSize);
	return _Ostr;
}

template< typename _Elem, typename _Traits >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, BINARY& _Bi)
{
	unsigned long ulSize;
	_Istr >> ulSize;

	_Bi.Reserve(ulSize);
	_Istr.read((_Elem*)(_Bi.m_pData), _Bi.m_ulSize);
	return _Istr;
}

#include <col/src/col_type_traits/col_type_traits.h>

#ifdef _DEBUG
#define CHECK_BASE(c, s)
#define START_CHECK(c)
#define END_CHECK(c)
#define CHECK(c, count) true
#else
#define CHECK_BASE(c, s) typedef integral_constant< int, __LINE__ > COL_GLUE(c, s)
#define START_CHECK(c) CHECK_BASE(c, check_count_start)
#define END_CHECK(c) CHECK_BASE(c, check_count_end)
#define CHECK(c, count) is_same_value< int, COL_GLUE(c, check_count_end)::value - COL_GLUE(c, check_count_start)::value, count + 1 >::value
#endif
