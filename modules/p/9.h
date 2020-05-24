// Кашин Андрей 9305
// Частное от деления многочлена на многочлен при делении с остатком

polynomial *P9(polynomial *A, polynomial *B) 
{
    polynomial *C;
    
    if(B -> degree == 0) {
        
        // Почленное деление
        
        fraction *divisor = B -> factors[0];
        
        C = copy_polynomial(A);
        
        for(size_t i = 0; i <= C -> degree; ++i) {
            
            fraction *old = C -> factors[i];
            C -> factors[i] = Q8(old, divisor);
            free_fraction(old);
        }
        
    } else {
        
        // Деление "столбиком"
        
        polynomial *dividend = copy_polynomial(A);
        
        C = init_polynomial(A -> degree - B -> degree);
        
        // Изначально коэффициенты частного - нули
        
        integer *num = init_integer(1);
        num -> sign = true;
        num -> digits[0] = 0;
        
        natural *denom = init_natural(1);
        denom -> digits[0] = 1;
        
        fraction *zero = init_fraction(num, denom);
        
        for(size_t i = 0; i <= C -> degree; ++i)
            C -> factors[i] = copy_fraction(zero);
        
        free_fraction(zero);
        
        while(dividend -> degree >= B -> degree) {
            
            // Пока степень делимого больше или равна степени делителя
            
            // Делим старший коэффициент
            
            fraction *quotient = Q8(dividend -> factors[dividend -> degree], B -> factors[B -> degree]);
            
            // Записываем результат
            
            size_t deg = dividend -> degree - B -> degree;
            
            C -> factors[deg] = quotient;
            
            // Вычитаем домноженный делитель
            
            polynomial *old = dividend;
            polynomial *sub = P4(B, deg);
            
            dividend = P2(dividend, sub);
            
            free_polynomial(old);
            free_polynomial(sub);
        }
    }
    
    normalize_polynomial(C);
    
    return C;
}
