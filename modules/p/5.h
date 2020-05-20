// Чугуй Владимир 9305
// Старший коэффициент многочлена

fraction *P5(polynomial *A)
{
	fraction *res = copy_fraction(A -> factors[A -> degree]);
	return res;
}
