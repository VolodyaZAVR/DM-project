/* Description of available structures and functions */


/* Natural number */

typedef struct {
    
    signed char *digits;
    size_t length;
    
} natural;


/* Integer number */

typedef struct {
    
    signed char *digits;
    size_t length;
    bool sign;          /* True - plus, otherwise minus */
    
} integer;


/* Fraction */

typedef struct {
    
    integer *numerator;
    natural *denominator;
    
} fraction;


/* Polynomial */

typedef struct {
    
    fraction *factors;
    size_t degree;
    
} polynomial;



/* Natural numbers */

natural *init_natural(size_t length);                   /* Initialize */

natural *copy_natural(natural *N);                      /* Copy */

void resize_natural(natural *N, size_t new_length);     /* Resize */

void swap_natural(natural **A, natural **B);            /* Swap */

void free_natural(natural *N);                          /* Remove from memory */


/* Integer numbers */

integer *init_integer(size_t length);                   /* Initialize */

integer *copy_integer(integer *N);                      /* Copy */

void resize_integer(integer *N, size_t new_length);     /* Resize */

void swap_integer(integer **A, integer **B);            /* Swap */

void free_integer(integer *N);                          /* Remove from memory */


/* Fractions */

fraction *init_fraction(integer *A, natural *B);        /* Initialize */

fraction *copy_fraction(fraction *F);                   /* Copy */

void free_fraction(fraction *F);                        /* Remove from memory */


/* Polynomials */

polynomial *init_polynomial(size_t degree);                 /* Initialize */

polynomial *copy_polynomial(polynomial *P);                 /* Copy */

void resize_polynomial(polynomial *P, size_t new_degree);   /* Change degree */

void free_polynomial(polynomial *P);                        /* Remove from memory */



/* For debugging only */

void write_natural(natural *N);                         /* Write to stdout */

void write_integer(integer *N);                         /* Write to stdout */

void write_fraction(fraction *F);                       /* Write to stdout */

void write_polynomial(polynomial *P);                   /* Write to stdout */
