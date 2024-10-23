namespace N {
	struct X{};
	int d();
	int e();
	inline int f(X, int = d()) { return e(); }
	int g(X);
	int h(X);
}