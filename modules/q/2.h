// Китаев Иван 9305
// Проверка, является ли дробь целым числом

#include <stdbool.h>

bool Q2(fraction *A) {
    
    bool result = false;
    
    // Сокращаем дробь
    
    fraction *reduced = Q1(A);
    
    // Проверяем знаменатель
    
    if(reduced -> denominator -> length == 1 && reduced -> denominator -> digits[0] == 1)
        result = true;
    
    free_fraction(reduced);
    
    return result;
}
