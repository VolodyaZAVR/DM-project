polynomial *P3(polynomial *A, fraction *B)
{
	polynomial *res = NULL;
	fraction *temp = NULL, *temp1 = NULL;
	res = copy_polynomial(A);
	temp = copy_fraction (B);
	for (size_t i = 0; i <= A -> degree; i++)
	{
		temp1 = Q7 (A -> factors[i], temp);
		res -> factors[i] = copy_fraction(temp1);
		free_fraction(temp1);
	}
	free_fraction(temp);
	return res;
}
