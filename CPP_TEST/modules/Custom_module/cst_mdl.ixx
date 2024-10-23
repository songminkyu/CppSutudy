export module util;
export import std.core;

export template<typename T, typename... Types>
T sum(T f, Types&&... args)
{
	return (f + ... + args);
}