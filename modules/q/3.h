// Кацер Евгений 9307
// Преобразование целого в дробное

fraction *Q3(integer *A) {
    
    natural *B = init_natural(1);
    B -> digits[0] = 1;
    
    // Преобразование в дробь
    
    fraction *R = init_fraction(A, B);
    free_natural(B);
    
    return R;
}
