// Бессонов Никита 9305
// Вычитание дробей

fraction *Q6(fraction *A, fraction *B) {
    
    integer *A_int_denom = Z4(A -> denominator);
    integer *B_int_denom = Z4(B -> denominator);
    
    integer *first  = Z8(A -> numerator, B_int_denom);  // Первый операнд
    integer *second = Z8(B -> numerator, A_int_denom);  // Второй операнд
    
    free_integer(A_int_denom);
    free_integer(B_int_denom);
    
    integer *numerator_sum = Z7(first, second); // Вычитание
    
    free_integer(first);
    free_integer(second);
    
    natural *common_denom = N8(A -> denominator, B -> denominator); // Общий знаменатель
    
    fraction *C = init_fraction(numerator_sum, common_denom);       // Преобразование в дробь
    
    free_natural(common_denom);
    
    fraction *result = Q1(C);   // Сокращение полученной дроби
    
    free_fraction(C);
    
    return result;
}

