// Николаенко Константин 9305
// Деление дробей

fraction *Q8(fraction *A, fraction *B) {
    
    natural *B_num   = Z1(B -> numerator);
    integer *B_denom = Z4(B -> denominator);
    
    integer *num   = Z8(A -> numerator, B_denom);
    natural *denom = N8(A -> denominator, B_num);
    
    free_natural(B_num);
    free_integer(B_denom);
    
    fraction *C = init_fraction(num, denom);
    
    free_integer(num);
    free_natural(denom);
    
    fraction *result = Q1(C);    // Сокращение дроби
    
    free_fraction(C);
    
    // Установка знака
    
    bool sign;
    
    if(A -> numerator -> sign == B -> numerator -> sign)
        sign = true;
    else sign = false;
    
    result -> numerator -> sign = sign;
    
    return result;
}
