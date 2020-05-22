// Салауров Евгений 9305
// Модуль умножения двух многочленов

#include <stdbool.h>


polynomial *P8(polynomial *A, polynomial *B)
{
    polynomial *C = init_polynomial(A -> degree + B -> degree);
    
    
    // Инициализация нуля
    
    integer *zero_num = init_integer(1);
    zero_num -> digits[0] = 0;
    zero_num -> sign = true;
    
    natural *zero_denom = init_natural(1);
    zero_denom -> digits[0] = 1;
    
    
    // Инициализация нулями
    
    for(size_t i = 0; i <= C -> degree; ++i)
        C -> factors[i] = init_fraction(zero_num, zero_denom);
    
    
    free_integer(zero_num);
    free_natural(zero_denom);
    
    
    // Вычисление коэффициентов получившегося многочлена
    
    for(size_t i = 0; i <= A -> degree; i++) {
        
        for(size_t j = 0; j <= B -> degree; j++) {
            
            // Умножение коэффициентов
            
            fraction *multiply = Q7(A -> factors[i], B -> factors[j]);
            
            // Суммирование
            
            fraction *old = C -> factors[i + j];
            
            C -> factors[i + j] = Q5(C -> factors[i + j], multiply);
            
            free_fraction(old);
            free_fraction(multiply);
        }
    }
    
    return C;
}
