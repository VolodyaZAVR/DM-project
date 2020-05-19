// Чугуй Владимир 9305
// Сложение дробных чисел

fraction *Q5(fraction *A, fraction *B) {
    
    integer *A_int_denom = Z4(A -> denominator);
    integer *B_int_denom = Z4(B -> denominator);
    
    integer *first  = Z8(A -> numerator, B_int_denom);  // Первое слагаемое
    integer *second = Z8(B -> numerator, A_int_denom);  // Второе слагаемое
    
    free_integer(A_int_denom);
    free_integer(B_int_denom);
    
    integer *numerator_sum = Z6(first, second);         // Суммирование домноженных частей
    
    free_integer(first);
    free_integer(second);
    
    natural *common_denom = N8(A -> denominator, B -> denominator); // Общий знаменатель
    
    fraction *C = init_fraction(numerator_sum, common_denom);       // Преобразование в дробь
    
    free_natural(common_denom);
    
    fraction *result = Q1(C);   // Сокращение полученной дроби
    
    free_fraction(C);
    
    return result;
}
