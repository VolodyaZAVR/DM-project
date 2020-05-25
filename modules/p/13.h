// Кашин Андрей 9305
// Кратные корни в простые

polynomial *P13(polynomial *P)
{
    polynomial *derivative = P12(P);
    
    polynomial *GCD = P11(P, derivative);
    
    free_polynomial(derivative);
    
    polynomial *result = P9(P, GCD);
    
    free_polynomial(GCD);
    
    fraction *GCD_LCM = P7(result);
    
    for(size_t i = 0; i <= result -> degree; ++i) {
        
        integer *new_num = Z9(result -> factors[i] -> numerator, GCD_LCM -> numerator);
        natural *new_denom = N11(GCD_LCM -> denominator, result -> factors[i] -> denominator);
        
        free_integer(result -> factors[i] -> numerator);
        free_natural(result -> factors[i] -> denominator);
        
        result -> factors[i] -> numerator = new_num;
        result -> factors[i] -> denominator = new_denom;
    }
    
    normalize_polynomial(result);
    
    return result;
}
