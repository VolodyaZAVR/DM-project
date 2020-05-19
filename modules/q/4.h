// Игнатьев Константин 9305
// Преобразование дробного в целое

integer *Q4(fraction *A) {
    
    integer *R;
    
    // Сокращение дроби
    
    fraction *reduced = Q1(A);
    
    // Проверка на целое
    
    if(reduced -> denominator -> length == 1 && reduced -> denominator -> digits[0] == 1) {
        
        R = copy_integer(reduced -> numerator);
        
    } else R = init_integer(0);
    
    free_fraction(reduced);
    
    return R;
}
