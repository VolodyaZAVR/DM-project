// Любаневич Роман 9305
// Умножение дробей

fraction *Q7(fraction *A, fraction *B) {
    
    integer *num   = Z8(A -> numerator, B -> numerator);        // Умножение числителей
    natural *denom = N8(A -> denominator, B -> denominator);    // Умножение знаменателей
    
    fraction *C = init_fraction(num, denom);
    
    free_integer(num);
    free_natural(denom);
    
    fraction *result = Q1(C);    // Сокращение дроби
    
    free_fraction(C);
    
    return result;
}
