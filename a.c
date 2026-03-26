long double ret(long double *p) {
	return *p;
}

_Float128 ret128(_Float128 *p) {
	return *p;
}

void passld(long double x, long double *p) {
	*p = x;
}

void pass128(_Float128 x, _Float128 *p) {
	*p = x;
}
