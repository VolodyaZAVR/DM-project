// Есин Артём 9305
// НОД многочленов

polynomial *P11(polynomial *A, polynomial *B)
{
    polynomial *X;
    polynomial *Y;
    
    if(A -> degree >= B -> degree) {
        
        X = copy_polynomial(A);
        Y = copy_polynomial(B);
        
    } else {
        
        X = copy_polynomial(B);
        Y = copy_polynomial(A);
    }
    
    polynomial *remainder = P10(X, Y);
    
    while(remainder -> degree != 0 ||
          remainder -> factors[0] -> numerator -> digits[0] != 0)
    {
        free_polynomial(X);
        
        X = Y;
        
        Y = remainder;
        
        remainder = P10(X, Y);
    }
    
    free_polynomial(X);
    free_polynomial(remainder);
    
    fraction *GCD_LCM = P7(Y);
    
    for(size_t i = 0; i <= Y -> degree; ++i) {
        
        integer *new_num = Z9(Y -> factors[i] -> numerator, GCD_LCM -> numerator);
        natural *new_denom = N11(GCD_LCM -> denominator, Y -> factors[i] -> denominator);
        
        free_integer(Y -> factors[i] -> numerator);
        free_natural(Y -> factors[i] -> denominator);
        
        Y -> factors[i] -> numerator = new_num;
        Y -> factors[i] -> denominator = new_denom;
    }
    
    normalize_polynomial(Y);
    
    return Y;
}
