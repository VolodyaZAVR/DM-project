// Лялина Анастасия 9307
// Сокращение дроби

fraction *Q1(fraction *A)
{
    fraction *result;
    
    // Проверка на нулевой числитель
    
    if(Z2(A -> numerator) == 0) {
        
        // Инициализация единичного знаменателя
        
        natural *denom = init_natural(1);
        denom -> digits[0] = 1;
        
        result = init_fraction(A -> numerator, denom);
        
        free_natural(denom);
        
    } else {
    
        natural *P = Z1(A -> numerator);
        natural *Q = A -> denominator;
        
        natural *GCD = N13(P, Q);
        
        natural *P_divided = N11(P, GCD);
        natural *Q_divided = N11(Q, GCD);
        
        free_natural(P);
        
        integer *numerator = Z4(P_divided);
        
        if(A -> numerator -> sign == false) numerator -> sign = false;
        
        result = init_fraction(numerator, Q_divided);
        
        free_integer(numerator);
        free_natural(P_divided);
        free_natural(Q_divided);
    }
    
    return result;
}
