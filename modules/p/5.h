fraction *P5(polynomial *A)
{
	fraction *res = NULL;
	res = copy_fraction(A -> factors[A -> degree]);
	return res;
}
