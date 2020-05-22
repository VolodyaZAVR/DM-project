// Гришин Илья 9305
// Вынесение НОД числителей и НОК знаменателей

fraction *P7(polynomial *P) {
    
    natural *GCD = Z1(P -> factors[0] -> numerator);
    natural *LCM = P -> factors[0] -> denominator;
    
    for(size_t i = 1; i <= P -> degree; ++i) {
        
        natural *num = Z1(P -> factors[i] -> numerator);
        natural *temp_GCD = GCD;
        
        GCD = N13(GCD, num);
        
        free_natural(temp_GCD);
        free_natural(num);
        
        natural *denom = P -> factors[i] -> denominator;
        natural *temp_LCM = LCM;
        
        LCM = N14(LCM, denom);
        
        free_natural(temp_LCM);
        free_natural(denom);
    }
    
    integer *GCD_integer = Z4(GCD);
    fraction *result = init_fraction(GCD_integer, LCM);
    
    free_integer(GCD_integer);
    free_natural(GCD);
    free_natural(LCM);
    
    return result;
}
