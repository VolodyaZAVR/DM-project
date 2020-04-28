polynomial *P4(polynomial *A, size_t B)
{
	polynomial *res = NULL;
    res = init_polynomial(A -> degree + B);
    for(size_t i = 0; i <= A -> degree; i++)
    {
        res -> factors[i + B] = copy_fraction(A -> factors[i]);
    }
	return res;
}
