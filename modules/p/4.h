// Гришин Илья 9305
// Умножение многочлена на x^k

polynomial *P4(polynomial *A, size_t B)
{
	polynomial *res = init_polynomial(A -> degree + B);
    
    integer *num = init_integer(1);
    num -> sign = true;
    num -> digits[0] = 0;
    
    natural *denom = init_natural(1);
    denom -> digits[0] = 1;
    
    fraction *zero = init_fraction(num, denom);
    
    for(size_t i = 0; i < B; i++)
        res -> factors[i] = copy_fraction(zero);
    
    free_fraction(zero);
    
    for(size_t i = 0; i <= (A -> degree); i++)
        res -> factors[i + B] = copy_fraction(A -> factors[i]);
    
    normalize_polynomial(res);
    
	return res;
}
