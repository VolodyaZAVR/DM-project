// Салауров Евгений 9305
// Сложение полиномов

polynomial *P1(polynomial *A, polynomial *B)
{
    size_t i, deg;
    polynomial *C;
    
    if(A -> degree > B -> degree) {
        
        C = copy_polynomial(A);
        deg = B -> degree;
        
    } else {
        
        C = copy_polynomial(B);
        deg = A -> degree;
    }
    
    for(i = 0; i <= deg; i++)
    {
        fraction *old = C -> factors[i];
        C -> factors[i] = Q5(A -> factors[i], B -> factors[i]);
        free_fraction(old);
    }
    
    normalize_polynomial(C);
    
    return C;
}
