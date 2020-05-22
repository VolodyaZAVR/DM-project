// Когутенко Андрей 9305
// Производная многочлена

#include <stdbool.h>


fraction *P12_int_to_fraction(size_t n) {
    
    // Подсчёт количества цифр
    
    size_t len = 0;
    size_t t = n;
    
    while(t != 0) {
        
        ++len;
        t /= 10;
    }
    
    integer *num = init_integer(len);
    num -> sign = true;
    
    // Копирование цифр
    
    size_t i = 0;
    
    while(n != 0) {
        
        num -> digits[i++] = n % 10;
        n /= 10;
    }
    
    natural *denom = init_natural(1);
    denom -> digits[0] = 1;
    
    fraction *result = init_fraction(num, denom);
    
    free_integer(num);
    free_natural(denom);
    
    return result;
}


polynomial *P12(polynomial *P) {
    
    polynomial *result;
    
    if(P -> degree > 0) {
    
        result = init_polynomial(P -> degree - 1);
        
        for(size_t i = 1; i <= P -> degree; ++i) {
            
            fraction *deg = P12_int_to_fraction(i);
            fraction *new_quotient = Q7(deg, P -> factors[i]);
            
            result -> factors[i - 1] = new_quotient;
            
            free_fraction(deg);
        }
        
    } else {
        
        result = init_polynomial(0);
        
        integer *num = init_integer(1);
        num -> digits[0] = 0;
        num -> sign = true;
        
        natural *denom = init_natural(1);
        denom -> digits[0] = 1;
        
        result -> factors[0] = init_fraction(num, denom);
        
        free_integer(num);
        free_natural(denom);
    }
    
    return result;
}
