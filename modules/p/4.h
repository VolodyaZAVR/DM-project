//Гришин Илья 9305
//Умножение многочлена на x^k
polynomial *P4(polynomial *A, size_t B)
{
	polynomial *res = NULL;
    res = init_polynomial(A -> degree + B);
    
    integer *numerator = init_integer(1);
    numerator -> sign = true;
    numerator -> digits[0] = 0;
    
    natural *denominator = init_natural(1);
    denominator -> digits[0] = 0;
    
    fraction *zero = init_fraction(numerator, denominator);
    
    for(size_t i = 0; i < B; i++)
    {
        res -> factors[i] = copy_fraction(zero);
    }
    
    free_fraction(zero);
    
    for(size_t i = 0; i <= (A -> degree); i++)
    {
        res -> factors[i + B] = copy_fraction(A -> factors[i]);
    }
    
	return res;
}
