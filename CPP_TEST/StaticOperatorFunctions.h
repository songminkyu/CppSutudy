#pragma once

#include <boost/tokenizer.hpp>
#include <boost/range/combine.hpp>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
template< typename _Elem >
static std::ofstream& operator << (std::ofstream& _Ostr, const std::vector< _Elem >& _Tys)
{
	for (const auto & cit : _Tys)
		_Ostr << cit << std::endl;

	_Ostr.close();

	return _Ostr;
}


template< typename _Elem >
static std::ifstream& operator >> (std::ifstream& _Istr, std::vector< _Elem >& _Tys)
{
	_Tys.clear();
	_Elem t;
	while (std::getline(_Istr, t))
	{
		_Tys.push_back(t);
	}
	return _Istr;
}


template< typename _Elem >
std::ofstream& operator << (std::ofstream& _Ostr, const std::list< _Elem >& _Tys)
{
	for (const auto & cit : _Tys)
		_Ostr << cit << std::endl;

	_Ostr.close();

	return _Ostr;
}
template< typename _Elem >
std::ifstream& operator >> (std::ifstream& _Istr, std::list< _Elem >& _Tys)
{
	_Tys.clear();
	_Elem t;
	while (std::getline(_Istr, t))
	{
		_Tys.push_back(t);
	}
	return _Istr;
}
template< typename _Elem >
std::wofstream& operator << (std::wofstream& _Ostr, const std::vector< _Elem >& _Tys)
{
	for (const auto & cit : _Tys)
		_Ostr << cit << std::endl;

	_Ostr.close();

	return _Ostr;
}
template< typename _Elem >
std::wifstream& operator >> (std::wifstream& _Istr, std::vector< _Elem >& _Tys)
{
	_Tys.clear();
	_Elem t;
	while (std::getline(_Istr, t))
	{
		_Tys.push_back(t);
	}
	return _Istr;
}
template< typename _Elem >
std::wofstream& operator << (std::wofstream& _Ostr, const std::list< _Elem >& _Tys)
{
	for (const auto & cit : _Tys)
		_Ostr << cit << std::endl;

	_Ostr.close();

	return _Ostr;
}
template< typename _Elem >
std::wifstream& operator >> (std::wifstream& _Istr, std::list< _Elem >& _Tys)
{
	_Tys.clear();
	_Elem t;
	while (std::getline(_Istr, t))
	{
		_Tys.push_back(t);
	}
	return _Istr;
}

struct do_init_order {
	template<typename _Elem > do_init_order(std::initializer_list<_Elem >&&) { }
	do_init_order() = default;
	~do_init_order() = default;
};
namespace details {
	template<typename V> void container_zip_helper(V& l, const V& r) {
		l.insert(l.end(), r.begin(), r.end());
	}
	template<typename V> void container_zip_helper(V& l, V&& r) {
		l.insert(l.end(), std::make_move_iterator(r.begin()),
			std::make_move_iterator(r.end()));
	}
} // namespace details

namespace detail
{
	template <typename Iterator>
	void advance_all(Iterator & iterator) {
		++iterator;
	}
	template <typename Iterator, typename ... Iterators>
	void advance_all(Iterator & iterator, Iterators& ... iterators) {
		++iterator;
		advance_all(iterators...);
	}

	template <typename Iter, typename... Iters>
	class zip_iterator {
	public:
		using value_type = std::tuple<const typename Iter::value_type&,
			const typename Iters::value_type&...>;

		zip_iterator() = default;
		zip_iterator(const Iter &head, const Iters&... tail)
			: head_(head), tail_(tail...) { }

		virtual ~zip_iterator() = default;

		value_type operator*() const {
			return std::tuple_cat(std::tuple<const typename Iter::value_type&>(*head_), *tail_);
		}

		zip_iterator& operator++() {
			++head_; ++tail_;
			return *this;
		}

		bool operator==(const zip_iterator &rhs) const {
			return head_ == rhs.head_ && tail_ == rhs.tail_;
		}

		bool operator!=(const zip_iterator &rhs) const {
			return !(*this == rhs);
		}

	private:
		Iter head_;
		zip_iterator<Iters...> tail_;
	};

	template <typename Iter>
	class zip_iterator<Iter> {
	public:
		using value_type = std::tuple<const typename Iter::value_type&>;

		zip_iterator() = default;
		zip_iterator(const Iter &head) : head_(head) { }

		virtual ~zip_iterator() = default;

		value_type operator*() const {
			return value_type(*head_);
		}

		zip_iterator& operator++() { ++head_; return *this; }

		bool operator==(const zip_iterator &rhs) const { return head_ == rhs.head_; }

		bool operator!=(const zip_iterator &rhs) const { return !(*this == rhs); }

	private:
		Iter head_;
	};

	template <typename Iter>
	class seq {
	public:
		using iterator = Iter;
		seq() = default;
		seq(const Iter &begin, const Iter &end) : begin_(begin), end_(end) { }
		virtual ~seq() = default;
		iterator begin() const { return begin_; }
		iterator end() const { return end_; }
	private:
		Iter begin_, end_;
	};
}

class CStaticOperatorFunctions
{
public:
	CStaticOperatorFunctions();
	~CStaticOperatorFunctions();
	
public:
#ifdef BOOST_TOKENIZER_JRB070303_HPP_
	template<typename _Elem, typename _ChangeElem, typename _Container>
	static auto Tokenizer_v_l(_Elem str, const _ChangeElem *separator) -> _Container
	{
		using Tok = boost::tokenizer<boost::char_separator<_ChangeElem>, typename _Elem::const_iterator, _Elem>;
		_Container getstrPath;
		boost::char_separator<_ChangeElem> sep(separator);
		Tok tok(str, sep);
		for (typename Tok::const_iterator beg = tok.begin(); beg != tok.end(); ++beg) {
			getstrPath.push_back(*beg);
		}
		return getstrPath;
	}

	template<typename _Elem, typename _ChangeElem >
	static auto TokenizerS(_Elem str, const _ChangeElem *separator,int TokPos) -> _Elem
	{
		using Tok = boost::tokenizer<boost::char_separator<_ChangeElem>, typename _Elem::const_iterator, _Elem>;		
		int i = 0;		
		boost::char_separator<_ChangeElem> sep(separator); // list of separator characters
		_Elem _str;
		Tok tok(str, sep);
		for (typename Tok::iterator beg = tok.begin(); beg != tok.end(); ++beg, ++i) 
		{
			if (TokPos == i)
				_str = *beg;				
		}
		return _str;
	}

	template<typename _Elem, typename... _Elems>
	static std::vector<_Elem> container_multi_zip_pack(std::vector<_Elem> v1, _Elems&&... vr) {
		std::size_t s = v1.size();
		do_init_order{ s += vr.size()... };
		v1.reserve(s);
		do_init_order{ (details::container_zip_helper(v1, std::forward<_Elems>(vr)), 0)... };
		return std::move(v1); 
	}

	template<typename _Elem, typename... _Elems>
	static std::list<_Elem> container_multi_zip_pack(std::list<_Elem> l1, _Elems&&... lr) {
		do_init_order{ (details::container_zip_helper(l1, std::forward<_Elems>(lr)), 0)... };
		return std::move(l1); 
	}
#endif

#ifdef BOOST_RANGE_COMBINE_HPP

	template<class... _Elems>
	static auto multi_zip_range(_Elems&... conts) -> decltype(boost::make_iterator_range(
		boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
		boost::make_zip_iterator(boost::make_tuple(conts.end()...))
	))
	{
		return{
			boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
			boost::make_zip_iterator(boost::make_tuple(conts.end()...))
		};
	}
#else
	template <typename... Seqs>
	static detail::seq<typename detail::zip_iterator<typename Seqs::const_iterator...>>
		multi_zip_range(const Seqs&... seqs)
	{
		return detail::seq<typename detail::zip_iterator<typename Seqs::const_iterator...>>(
			detail::zip_iterator<typename Seqs::const_iterator...>(std::begin(seqs)...),
			detail::zip_iterator<typename Seqs::const_iterator...>(std::end(seqs)...));
	}

	template <typename Function, typename Iterator, typename ... Iterators>
	static Function function_multi_zip_range(Function func, Iterator begin, Iterator end, Iterators ... iterators)
	{
		for (; begin != end; ++begin, advance_all(iterators...))
			func(*begin, *(iterators)...);
		//could also make this a tuple
		return func;
	}
#endif

public:
	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::wstring, _Elem>::value, _Elem>::type
		istrcompair(const std::vector<_Elem> & r, _Elem & l)
	{
		std::wstring str;

		for (const auto & cit : r)
		{
			if (_wcsicmp(cit.c_str(), l.c_str()) == 0)
			{
				str = l;
				break;
			}
		}
		return str;
	}


	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::string, _Elem>::value, _Elem>::type
		istrcompair(const std::vector<_Elem> & r, _Elem & l)
	{
		std::string str;

		for (const auto & cit : r)
		{
			if (_stricmp(cit.c_str(), l.c_str()) == 0)
			{
				str = l;
				break;
			}
		}
		return str;
	}

	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::wstring, _Elem>::value, _Elem>::type
		istrcompair(const std::list<_Elem> & r, _Elem & l)
	{
		std::wstring str;

		for (const auto & cit : r)
		{
			if (_wcsicmp(cit.c_str(), l.c_str()) == 0)
			{
				str = l;
				break;
			}
		}
		return str;
	}


	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::string, _Elem>::value, _Elem>::type
		istrcompair(const std::list<_Elem> & r, _Elem & l)
	{
		std::string str;

		for (const auto & cit : r)
		{
			if (_stricmp(cit.c_str(), l.c_str()) == 0)
			{
				str = l;
				break;
			}
		}
		return str;
	}

	template<typename _Elem>
	static _Elem ifind_str(const std::vector<_Elem> & r, _Elem & l)
	{
		return istrcompair(r, l).c_str();
	}

	template<typename _Elem>
	static _Elem ifind_str(const std::list<_Elem> & r, _Elem & l)
	{
		return istrcompair(r, l).c_str();
	}
public:

	typedef enum _DELLINEOP {
		DELETE_SPECIFIED_PAIR_TYPE_ITEM = 1,
		HOLD_SPECIFIED_PAIR_TYPE_ITEM,
		DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM,
		HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM
	} DELLINEOP;


	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::wstring, _Elem>::value, _Elem>::type
		_DeleteLine(std::wstring &wpath, const std::vector<_Elem> & deleteLinestring, const int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{		

		std::wifstream ifs;
		std::wofstream ofs;
		
		int getseperatorSize;
		int heapSize = 0;

		ifs.open(wpath, std::ios::in);		
		while (ifs)
		{
			std::wstring temp;
			if (std::getline(ifs, temp))
				heapSize++;
		}
		ifs.close();

		std::wstring *data = new std::wstring[heapSize];
		heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::wstring temp;
			if (std::getline(ifs, temp))
			{
				data[heapSize] = temp;
				heapSize++;
			}
		}
		ifs.close();

		ofs.open(wpath, std::ios::out);
		if (ofs.fail())
		{
			
			std::wcout << " File Open Error =  " << wpath << std::endl;
		}
		else
		{

			std::wcout << " File Open Succeeded =  " << wpath << std::endl;

			if (seperator != nullptr)
				getseperatorSize = seperator->length();
			else
				getseperatorSize = 0;

			for (int i = 0; i < heapSize; i++)
			{
				std::wstring temp;
				if ((policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM) ||
					(policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM))
				{
					temp = ifind_str(deleteLinestring, TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex));
				}
				else
				{
					temp = ifind_str(deleteLinestring, data[i]);
				}


				if (policy == DELLINEOP::DELETE_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp != data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp == data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp != TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex))
						{
							ofs << data[i] << std::endl;
						}
					}
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp == TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex))
						{

							std::wcout << " DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITE " << std::endl;
							std::wcout << data[i] << std::endl;

							ofs << data[i] << std::endl;
						}
					}
				}
				else
				{
					continue;
				}
			}
			ofs.close();
		}

		delete[]data;

		return L"";
	}



	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::wstring, _Elem>::value, _Elem>::type
		_DeleteLine(std::wstring &wpath, const std::list<_Elem> & deleteLinestring, const int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{
		std::wifstream ifs;
		std::wofstream ofs;

		int getseperatorSize;
		int heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::wstring temp;
			if (std::getline(ifs, temp))
				heapSize++;
		}
		ifs.close();

		std::wstring *data = new std::wstring[heapSize];
		heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::wstring temp;
			if (std::getline(ifs, temp))
			{
				data[heapSize] = temp;
				heapSize++;
			}
		}
		ifs.close();

		ofs.open(wpath, std::ios::out);
		if (ofs.fail())
		{
			std::wcout << " File Open Error =  " << wpath << std::endl;
		}
		else
		{

			std::wcout << " File Open Succeeded =  " << wpath << std::endl;

			if (seperator != nullptr)
				getseperatorSize = seperator->length();
			else
				getseperatorSize = 0;

			for (int i = 0; i < heapSize; i++)
			{
				std::wstring temp;
				if ((policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM) ||
					(policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM))
				{
					temp = ifind_str(deleteLinestring, TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex));
				}
				else
				{
					temp = ifind_str(deleteLinestring, data[i]);
				}


				if (policy == DELLINEOP::DELETE_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp != data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp == data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp != TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex))
						{
							ofs << data[i] << std::endl;
						}
					}
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp == TokenizerS<std::wstring, wchar_t>(data[i], seperator->c_str(), seperatorIndex))
						{				
							ofs << data[i] << std::endl;
						}
					}
				}
				else
				{
					continue;
				}
			}
			ofs.close();
		}

		delete[]data;

		return L"";
	}


	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::string, _Elem>::value, _Elem>::type
		_DeleteLine(std::string &wpath, const std::list<_Elem> & deleteLinestring, const int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{
		std::ifstream ifs;
		std::ofstream ofs;

		int getseperatorSize;
		int heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::string temp;
			if (std::getline(ifs, temp))
				heapSize++;
		}
		ifs.close();

		std::string *data = new std::string[heapSize];
		heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::string temp;
			if (std::getline(ifs, temp))
			{
				data[heapSize] = temp;
				heapSize++;
			}
		}
		ifs.close();

		ofs.open(wpath, std::ios::out);
		if (ofs.fail())
		{
			std::cout << " File Open Error =  " << wpath << std::endl;
		}
		else
		{

			std::cout << " File Open Succeeded =  " << wpath << std::endl;

			if (seperator != nullptr)
				getseperatorSize = seperator->length();
			else
				getseperatorSize = 0;

			for (int i = 0; i < heapSize; i++)
			{
				std::string temp;
				if ((policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM) ||
					(policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM))
				{
					temp = ifind_str(deleteLinestring, TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex));
				}
				else
				{
					temp = ifind_str(deleteLinestring, data[i]);
				}


				if (policy == DELLINEOP::DELETE_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp != data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp == data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp != TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex))
						{
							ofs << data[i] << std::endl;
						}
					}
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp == TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex))
						{

							std::cout << " DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITE " << std::endl;
							std::cout << data[i] << std::endl;

							ofs << data[i] << std::endl;
						}
					}
				}
				else
				{
					continue;
				}
			}
			ofs.close();
		}

		delete[]data;

		return L"";
	}

	template<typename _Elem>
	static typename std::enable_if<std::is_same<std::string, _Elem>::value, _Elem>::type
		_DeleteLine(std::string &wpath, const std::vector<_Elem> & deleteLinestring, const int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{
		std::ifstream ifs;
		std::ofstream ofs;

		int getseperatorSize;
		int heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::string temp;
			if (std::getline(ifs, temp))
				heapSize++;
		}
		ifs.close();

		std::string *data = new std::string[heapSize];
		heapSize = 0;

		ifs.open(wpath, std::ios::in);
		while (ifs)
		{
			std::string temp;
			if (std::getline(ifs, temp))
			{
				data[heapSize] = temp;
				heapSize++;
			}
		}
		ifs.close();

		ofs.open(wpath, std::ios::out);
		if (ofs.fail())
		{
			std::cout << " File Open Error =  " << wpath << std::endl;
		}
		else
		{

			std::cout << " File Open Succeeded =  " << wpath << std::endl;

			if (seperator != nullptr)
				getseperatorSize = seperator->length();
			else
				getseperatorSize = 0;

			for (int i = 0; i < heapSize; i++)
			{
				std::string temp;
				if ((policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM) ||
					(policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM))
				{
					temp = ifind_str(deleteLinestring, TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex));
				}
				else
				{
					temp = ifind_str(deleteLinestring, data[i]);
				}


				if (policy == DELLINEOP::DELETE_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp != data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_PAIR_TYPE_ITEM)
				{
					if (temp == data[i])
						ofs << data[i] << std::endl;
				}
				else if (policy == DELLINEOP::DELETE_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp != TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex))
						{
							ofs << data[i] << std::endl;
						}
					}
				}
				else if (policy == DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITEM)
				{
					if (getseperatorSize != 0)
					{
						if (temp == TokenizerS<std::string, char>(data[i], seperator->c_str(), seperatorIndex))
						{

							std::cout << " DELLINEOP::HOLD_SPECIFIED_NON_PAIR_TYPE_ITE " << std::endl;
							std::cout << data[i] << std::endl;

							ofs << data[i] << std::endl;
						}
					}
				}
				else
				{
					continue;
				}
			}
			ofs.close();
		}

		delete[]data;

		return L"";
	}



	template< typename _Elem>
	static void DeleteLine(_Elem & wpath, std::vector<_Elem> &deleteLinestring, int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{
		_DeleteLine(wpath, deleteLinestring, policy, seperator, seperatorIndex);
	}

	template< typename _Elem>
	static void DeleteLine(_Elem & wpath, std::list<_Elem> &deleteLinestring, int policy = 0, _Elem *seperator = nullptr, int seperatorIndex = 0)
	{
		_DeleteLine(wpath, deleteLinestring, policy, seperator, seperatorIndex);
	}

	static std::basic_string<char> _dirnameOf(const std::basic_string<char>& fname)
	{
		size_t pos = fname.find_last_of("\\/");
		return (std::string::npos == pos)
			? "path combine error"
			: fname.substr(0, pos);
	}

	static std::basic_string<wchar_t> _dirnameOf(const std::basic_string<wchar_t>& fname)
	{
		size_t pos = fname.find_last_of(L"\\/");
		return (std::wstring::npos == pos)
			? L"path combine error"
			: fname.substr(0, pos);
	}

	template<typename _Elem>
	static std::basic_string<_Elem> dirnameOf(const std::basic_string<_Elem>& fullpath)
	{
		return _dirnameOf(fullpath);
	}



public:
	static std::wstring replace_all(const std::wstring & message, const std::wstring & pattern, const std::wstring & replace);
	static std::string replace_all(const std::string & message, const std::string & pattern, const std::string & replace);

};