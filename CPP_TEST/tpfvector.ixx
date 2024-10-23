export module tpf.vctr;
export import std.core;
export import <vector>;
export namespace tpf
{
	template<typename T>
	class vctr
	{
	protected:
		T m_x{}, m_y{}, m_z{};

	public:
		vctr() = default;
		vctr(T x) : m_x{ x } { }
		vctr(T x, T y) : m_x{ x }, m_y{ y } {}
		vctr(T x, T y, T z) : m_x{ x }, m_y{ y }, m_z{ z } {}
		vctr(const vctr&) = default;
		vctr& operator=(const vctr&) = default;

		friend vctr operator+(vctr v1, vctr v2)
		{
			return { v1.m_x + v2.m_x,v1.m_y + v2.m_y ,v1.m_z + v2.m_z };
		}

		friend std::ostream& operator<< (std::ostream& os, const vctr& v)
		{
			os << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";
			return { os };
		}
	};
}