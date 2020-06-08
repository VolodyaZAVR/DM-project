/* Numbers manipulating functions */

#pragma once

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "system.h"
#include "io.h"
#include "locale.h"


/* Windows size_t fix */

#ifdef _WIN32
	#define PR_SIZET "%I64u"
#else
	#define PR_SIZET "%llu"
#endif

/* STRUCTURES */

/* Natural number */

typedef struct {
    
    signed char *digits;
    size_t length;
    size_t offset_digits;       /* Service */
    size_t offset_struct;       /* Service */
    
} natural;


/* Integer number */

typedef struct {
    
    signed char *digits;
    size_t length;
    size_t offset_digits;       /* Service */
    size_t offset_struct;       /* Service */
    bool sign;
    
} integer;


/* Fraction */

typedef struct {
    
    integer *numerator;
    natural *denominator;
    size_t offset_struct;       /* Service */
    
} fraction;


/* Polynomial */

typedef struct {
    
    fraction **factors;
    size_t degree;
    size_t offset_factors;      /* Service */
    size_t offset_struct;       /* Service */
    
} polynomial;


/* FUNCTIONS */

int read_int(const char *message);                      /* Read from stdin */

void write_int(int n);                                  /* Write to stdout */

void write_bool(bool value);                            /* Write to stdout */


/* Natural numbers */

natural *init_natural(size_t length);                   /* Initialize */

natural *copy_natural(natural *N);                      /* Copy */

void resize_natural(natural *N, size_t new_length);     /* Resize */

void normalize_natural(natural *N);                     /* Remove leading zeros */

void swap_natural(natural **A, natural **B);            /* Swap */

void free_natural(natural *N);                          /* Remove from memory */

natural *read_natural(const char *message);             /* Read from stdin */

void write_natural(natural *N);                         /* Write to stdout */


/* Integer numbers */

integer *init_integer(size_t length);                   /* Initialize */

integer *copy_integer(integer *N);                      /* Copy */

void resize_integer(integer *N, size_t new_length);     /* Resize */

void normalize_integer(integer *N);                     /* Remove leading zeros */

void swap_integer(integer **A, integer **B);            /* Swap */

void free_integer(integer *N);                          /* Remove from memory */

integer *read_integer(const char *message);             /* Read from stdin */

void write_integer(integer *N);                         /* Write to stdout */


/* Fractions */

fraction *init_fraction(integer *A, natural *B);        /* Initialize */

fraction *copy_fraction(fraction *F);                   /* Copy */

void free_fraction(fraction *F);                        /* Remove from memory */

fraction *read_fraction(const char *message);           /* Read */

void write_fraction(fraction *F);                       /* Write to stdout */


/* Polynomials */

polynomial *init_polynomial(size_t degree);                 /* Initialize */

polynomial *copy_polynomial(polynomial *P);                 /* Copy */

void resize_polynomial(polynomial *P, size_t new_degree);   /* Change degree */

void normalize_polynomial(polynomial *P);                   /* Remove unnecessary zero factors */

void expand_polynomial(polynomial *P, size_t new_degree);   /* Expand with zero filling */

void free_polynomial(polynomial *P);                        /* Remove from memory */

polynomial *read_polynomial(const char *message);           /* Read */

void write_quotient(fraction *Q, size_t degree, bool first);    /* Write quotient */

void write_polynomial(polynomial *P);                       /* Write to stdout */



/* FUNCTIONS IMPLEMENTATIONS */


int read_int(const char *message) {
	
    int result;
    bool success = false;
	bool sign = true;
    
    while(success == false) {
        
        success = true;
        result = 0;
        
        print(message);
        
        char current = skip_spaces();   /* Reading first non-space symbol */
        
        if(current == '-') {
            
            sign = false;
            current = skip_spaces();
        }
        
        /* Skipping leading zeros */
        
        bool was_zero = false;
        
        while(!feof(stdin) && current == '0') {
            
            was_zero = true;
            current = skip_spaces();
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(current == '\n' && was_zero == false) {
            
            if(was_zero == false) {
                
                success = false;
                continue;
            }
        }
        
        while(!feof(stdin) && current != '\n') {
            
            if(isdigit(current) && result <= 100000000) {
                
                result *= 10;
                result += current - '0';
                current = skip_spaces();
                
            } else {
                
                /* Unexpected symbol */
                
                success = false;
                print(UNEXP_SYMBOL "\n\n");
                
                while(!feof(stdin) && current != '\n') current = getchar();
            }
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
    }
    
    if(sign == false) result = -result;
    
    return result;
}


void write_int(int n) {
	
	printf("%d\n", n);
    
    fflush(stdout);
}

void write_bool(bool value) {
	
	if(value == true)
		printf(TRUE "\n");
	else
		printf(FALSE "\n");
    
    fflush(stdout);
}


natural *init_natural(size_t length) {
    
    size_t offset;
    
    natural *N = mallocate(sizeof(*N), &offset);
    
    N -> offset_struct = offset;
    
    N -> digits = mallocate(length * sizeof(*(N -> digits)), &offset);
    
    N -> offset_digits = offset;
    
    N -> length = length;
    
    return N;
}


natural *copy_natural(natural *N) {
	
	natural *result = init_natural(N -> length);
	
	for(size_t i = 0; i < (N -> length); ++i)
		result -> digits[i] = N -> digits[i];
	
	return result;
}


void resize_natural(natural *N, size_t new_length) {
    
    N -> digits = reallocate(N -> digits, new_length * sizeof(*(N -> digits)), N -> offset_digits);
    N -> length = new_length;
}


void normalize_natural(natural *N) {
    
    size_t i;
    
    for(i = N -> length - 1; i != 0; --i)
        if(N -> digits[i] != 0)
            break;
    
    resize_natural(N, i + 1);
}


void swap_natural(natural **A, natural **B) {
    
    natural *temp = *A;
    *A = *B;
    *B = temp;
}


void free_natural(natural *N) {
	
	/* TEMPORARY BUGFIX */
	
    /*
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == N) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
    */
    
    free_logged(N -> digits, N -> offset_digits);
    
    free_logged(N, N -> offset_struct);
}


natural *read_natural(const char *message) {
    
    /* Reading number to string */
    
    size_t offset;
    size_t str_offset;
    size_t str_size = 2;
    
    bool success = false;
    
    char *str = mallocate(str_size * sizeof(*str), &offset);
    
    while(success == false) {
        
        success = true;
		str_offset = 0;
        
        print(message);
        
        char current = skip_spaces();   /* Reading first non-space symbol */
        
        /* Skipping leading zeros */
        
        bool was_zero = false;
        
        while(!feof(stdin) && current == '0') {
			
			was_zero = true;
			current = skip_spaces();
		}
        
        /* Handling possible errors */
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(current == '\n') {
			
			if(was_zero == true) {
				
				str[0] = '0';
				str_offset = 1;
				
			} else success = false;		/* Non-digital symbol */
		}
        
        while(!feof(stdin) && current != '\n') {
            
            if(isdigit(current)) {
                
                if(str_offset == str_size) {
                    
                    str_size *= 2;
                    str = reallocate(str, str_size * sizeof(*str), offset);
                }
                
                str[str_offset++] = current;
                current = skip_spaces();
                
            } else {
                
                /* Unexpected symbol */
                
                success = false;
                
                print(UNEXP_SYMBOL "\n\n");
                
                while(!feof(stdin) && current != '\n') current = getchar();
            }
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
    }
    
    /* Initializing number */
    
    natural *result = init_natural(str_offset);
    
    /* Copying */
    
    size_t j = 0;
    
    for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
        result -> digits[j++] = str[i] - '0';
    
    free_logged(str, offset);
    
    return result;
}


void write_natural(natural *N) {
    
    for(size_t i = N -> length - 1; i != SIZE_MAX; --i)
        putchar(N -> digits[i] + '0');
    
    putchar('\n');
    
    fflush(stdout);
}


integer *init_integer(size_t length) {
    
    size_t offset;
    
    integer *N = mallocate(sizeof(*N), &offset);
    
    N -> offset_struct = offset;
    
    N -> digits = mallocate(length * sizeof(*(N -> digits)), &offset);
    
    N -> offset_digits = offset;
    
    N -> length = length;
    
    return N;
}


integer *copy_integer(integer *N) {
	
	integer *result = init_integer(N -> length);
	
	result -> sign = N -> sign;
	
	for(size_t i = 0; i < (N -> length); ++i)
		result -> digits[i] = N -> digits[i];
	
	return result;
}


void resize_integer(integer *N, size_t new_length) {
    
    N -> digits = reallocate(N -> digits, new_length * sizeof(*(N -> digits)), N -> offset_digits);
    N -> length = new_length;
}

void normalize_integer(integer *N) {
    
    size_t i;
    
    for(i = N -> length - 1; i != 0; --i)
        if(N -> digits[i] != 0)
            break;
    
    resize_integer(N, i + 1);
}


void swap_integer(integer **A, integer **B) {
    
    integer *temp = *A;
    *A = *B;
    *B = temp;
}


void free_integer(integer *N) {
	
	/* TEMPORARY BUGFIX */
	
    /*
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == N) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
    */
    
    free_logged(N -> digits, N -> offset_digits);
    
    free_logged(N, N -> offset_struct);
}


integer *read_integer(const char *message) {
    
    /* Reading number to string */
    
    size_t offset;
    
    size_t str_size = 2;
    size_t str_offset;
    bool sign = true;
    
    bool success = false;
    
    char *str = mallocate(str_size * sizeof(*str), &offset);
    
    while(success == false) {
        
        success = true;
        str_offset = 0;
        
        print(message);
        
        char current = skip_spaces();   /* Reading first non-space symbol */
        
        if(current == '-') {
            
            sign = false;
            current = skip_spaces();
        }
        
        /* Skipping leading zeros */
        
        bool was_zero = false;
        
        while(!feof(stdin) && current == '0') {
			
			was_zero = true;
			current = skip_spaces();
		}
        
        /* Handling possible errors */
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(current == '\n') {
			
			if(was_zero == true) {
				
				str[0] = '0';
				str_offset = 1;
				
			} else success = false;		/* Non-digital symbol */
		}
        
        while(!feof(stdin) && current != '\n') {
            
            if(isdigit(current)) {
                
                if(str_offset == str_size) {
                    
                    str_size *= 2;
                    str = reallocate(str, str_size * sizeof(*str), offset);
                }
                
                str[str_offset++] = current;
                current = skip_spaces();
                
            } else {
                
                /* Unexpected symbol */
                
                success = false;
                
                print(UNEXP_SYMBOL "\n\n");
                
                while(!feof(stdin) && current != '\n') current = getchar();
            }
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
    }
    
    /* Initializing number */
    
    integer *result = init_integer(str_offset);
    
    result -> sign = sign;
    
    /* Copying */
    
    size_t j = 0;
    
    for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
        result -> digits[j++] = str[i] - '0';
    
    free_logged(str, offset);
    
    return result;
}


void write_integer(integer *N) {
    
    if((N -> length) == 0) {
        printf(INV_MOD_INPUT "\n");
        return;
    }
    
    if(N -> sign == false) putchar('-');
    
    for(size_t i = N -> length - 1; i != SIZE_MAX; --i)
        putchar(N -> digits[i] + '0');
    
    putchar('\n');
    
    fflush(stdout);
}


fraction *init_fraction(integer *A, natural *B) {
    
    size_t offset;
    
    fraction *F = mallocate(sizeof(*F), &offset);
    
    F -> numerator = copy_integer(A);
    F -> denominator = copy_natural(B);
    F -> offset_struct = offset;
    
    return F;
}


fraction *copy_fraction(fraction *F) {
    
    return init_fraction(F -> numerator, F -> denominator);
}


void free_fraction(fraction *F) {
    
	/* TEMPORARY BUGFIX */
	
    /*
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == F) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
    */
    
    free_integer(F -> numerator);
    free_natural(F -> denominator);
    
    free_logged(F, F -> offset_struct);
}


fraction *read_fraction(const char *message) {
    
    /* Reading every number to string */
    
    size_t offset;
    size_t str_offset;
    size_t str_size = 2;
    
    bool success = false;
    
    fraction *F = mallocate(sizeof(*F), &offset);
    F -> offset_struct = offset;
    
    integer *numerator;
    natural *denominator = NULL;
    
    char *str = mallocate(str_size * sizeof(*str), &offset);
    
    while(success == false) {
        
        success = true;
        str_offset = 0;
        
        print(message);
        
        bool numerator_read = false;
        
        /* Reading sign */
        
        bool sign = true;
        
        char current = skip_spaces();
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(current == '-') {
            
            sign = false;
            current = skip_spaces();
        }
        
        /* Skipping leading zeros */
        
        bool was_zero = false;
        
        while(!feof(stdin) && current == '0') {
            
            was_zero = true;
            current = skip_spaces();
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(current == '\n') {
            
            if(was_zero == true) {
                
                /* Zero */
                
                numerator = init_integer(1);
                numerator -> digits[0] = 0;
                numerator -> sign = sign;
                
                continue;
                
            } else success = false;
            
        } else if(current == '/') success = was_zero;
        
        if(success == false) {
            
            print(UNEXP_SYMBOL "\n\n");
            
            while(!feof(stdin) && current != '\n') current = getchar();
            
            continue;
        }
        
        if(numerator_read == false) {
            
            /* Reading numerator */
            
            while(!feof(stdin) && current != '\n' && current != '/') {
                
                if(isdigit(current)) {
                    
                    if(str_offset == str_size) {
                        
                        str_size *= 2;
                        str = reallocate(str, str_size * sizeof(*str), offset);
                    }
                    
                    str[str_offset++] = current;
                    current = skip_spaces();
                    
                } else {
                    
                    success = false;
                    
                    while(!feof(stdin) && current != '\n') current = getchar();
                }
            }
            
            if(feof(stdin)) terminate(RCODE_EOF);
            
            if(success == false) {
                
                print(UNEXP_SYMBOL "\n\n");
                
                while(!feof(stdin) && current != '\n') current = getchar();
                
                continue;
            }
            
            /* Initializing numerator */
            
            if(str_offset == 0) {
                
                numerator = init_integer(1);
                numerator -> sign = sign;
                numerator -> digits[0] = 0;
                
            } else {
            
                numerator = init_integer(str_offset);
                numerator -> sign = sign;
                
                size_t j = 0;
                
                for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                    numerator -> digits[j++] = str[i] - '0';
            }
            
            if(current == '\n') {
                
                /* Integer */
                
                continue;
            }
        }
        
        current = skip_spaces();
        
        /* Reading denominator */
        
        /* Skipping leading zeros */
        
        was_zero = false;
        
        while(!feof(stdin) && current == '0') {
            
            was_zero = true;
            current = skip_spaces();
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        str_offset = 0;
        
        while(!feof(stdin) && current != '\n') {
            
            if(isdigit(current)) {
                
                if(str_offset == str_size) {
                    
                    str_size *= 2;
                    str = reallocate(str, str_size * sizeof(*str), offset);
                }
                
                str[str_offset++] = current;
                current = skip_spaces();
                
            } else {
                
                success = false;
                
                while(!feof(stdin) && current != '\n') current = getchar();
            }
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(success == false) {
            
            print(UNEXP_SYMBOL "\n\n");
            
            while(!feof(stdin) && current != '\n') current = getchar();
            
            continue;
        }
        
        /* Initializing denominator */
        
        if(str_offset == 0) {
            
            if(was_zero == true) {
                
                denominator = init_natural(1);
                denominator -> digits[0] = 0;
                
            } else success = false;
            
        } else {
        
            denominator = init_natural(str_offset);
            
            size_t j = 0;
            
            for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                denominator -> digits[j++] = str[i] - '0';
        }
    }
    
    free_logged(str, offset);
    
    F -> numerator = numerator;
    
    if(denominator == NULL) {
        
        /* Integer */
        
        denominator = init_natural(1);
        denominator -> digits[0] = 1;
    }
    
    F -> denominator = denominator;
    
    return F;
}


void write_fraction(fraction *F) {
    
    if(F -> numerator -> sign == false)
        putchar('-');
    
    for(size_t i = (F -> numerator -> length) - 1; i != SIZE_MAX; --i)
        putchar(F -> numerator -> digits[i] + '0');
    
    printf(" / ");
    
    for(size_t i = (F -> denominator -> length) - 1; i != SIZE_MAX; --i)
        putchar(F -> denominator -> digits[i] + '0');
    
    putchar('\n');
    
    fflush(stdout);
}


polynomial *init_polynomial(size_t degree) {
    
    size_t offset;
    
    polynomial *P = mallocate(sizeof(*P), &offset);
    P -> offset_struct = offset;
    P -> degree = degree;
    
    P -> factors = mallocate((degree + 1) * sizeof(fraction), &offset);
    P -> offset_factors = offset;
    
    return P;
}


polynomial *copy_polynomial(polynomial *P) {
    
    polynomial *result = init_polynomial(P -> degree);
    
    for(size_t i = 0; i <= (P -> degree); ++i)
        result -> factors[i] = copy_fraction(P -> factors[i]);
    
    return result;
}


void resize_polynomial(polynomial *P, size_t new_degree) {
    
    if((P -> degree) > new_degree) {
        
        /* Freeing unnecessary factors */
        
        for(size_t i = new_degree + 1; i <= (P -> degree); ++i)
            free_fraction(P -> factors[i]);
    }
    
    P -> factors = reallocate(P -> factors, (new_degree + 1) * sizeof(fraction), P -> offset_factors);
    P -> degree = new_degree;
}


void normalize_polynomial(polynomial *P) {
    
    size_t real_deg = P -> degree;
    
    while(real_deg != 0) {
        
        if(P -> factors[real_deg] -> numerator -> length != 1 || 
           P -> factors[real_deg] -> numerator -> digits[0] != 0)
           break;
        
        --real_deg;
    }
    
    resize_polynomial(P, real_deg);
}


void expand_polynomial(polynomial *P, size_t new_degree) {
    
    if(P -> degree >= new_degree) return;
    
    size_t old_degree = P -> degree;
    
    integer *num = init_integer(1);
    num -> sign = true;
    num -> digits[0] = 0;
    
    natural *denom = init_natural(1);
    denom -> digits[0] = 1;
    
    fraction *zero = init_fraction(num, denom);
    
    free_integer(num);
    free_natural(denom);
    
    resize_polynomial(P, new_degree);
    
    P -> factors[old_degree + 1] = zero;
    
    for(size_t i = old_degree + 2; i <= P -> degree; ++i)
        P -> factors[i] = copy_fraction(zero);
}


void free_polynomial(polynomial *P) {
    
    for(size_t i = 0; i <= (P -> degree); ++i)
        free_fraction(P -> factors[i]);
    
    free_logged(P, P -> offset_struct);
}


polynomial *read_polynomial(const char *message) {
    
    polynomial *P;
    
    bool success = false;
    
    while(success == false) {
        
        success = true;
        print(message);
        
        P = init_polynomial(0);
        
        /* 0 - numerator, sign not read             */
        /* 1 - numerator, sign read, no digits read */
        /* 2 - numerator, sign read, digit read     */
        /* 3 - denominator, no digits read          */
        /* 4 - denominator, digit read              */
        /* 5 - x symbol                             */
        /* 6 - degree, no digits read               */
        /* 7 - degree, digit read                   */
        
        unsigned char mode = 0;
        unsigned char last = 0;
        
        size_t offset;
        size_t allocated = 1;
        size_t str_offset = 0;
        char *str = mallocate(allocated * sizeof(*str), &offset);
        
        bool sign = true;
        
        integer *num = NULL;
        natural *denom = NULL;
        fraction *quotient = NULL;
        size_t degree = 0;
        size_t degree_length = 0;
        
        integer *one_num = init_integer(1);
        one_num -> digits[0] = 0;
        one_num -> sign = true;
        
        natural *one_denom = init_natural(1);
        one_denom -> digits[0] = 1;
        
        P -> factors[0] = init_fraction(one_num, one_denom);
        
        one_num -> digits[0] = 1;
        
        char symbol = skip_spaces();
        
        while(!feof(stdin) && symbol != '\n' && success == true) {
            
            if(mode == 0) {
                
                /* Reading numerator, sign not read */
                
                if(isdigit(symbol)) {
                    
                    if(str_offset == allocated) {
                        
                        allocated *= 2;
                        str = reallocate(str, allocated, offset);
                    }
                    
                    str[str_offset++] = symbol;
                    mode = 2;
                    
                } else if(symbol == '+') {
                    
                    sign = true;
                    mode = 1;
                    
                } else if(symbol == '-') {
                    
                    sign = false;
                    mode = 1;
                    
                } else if(symbol == 'x') {
                    
                    quotient = init_fraction(one_num, one_denom);
                    mode = 5;
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else if(mode == 1) {
                
                /* Reading numerator, sign known, no digits read */
                
                if(isdigit(symbol)) {
                    
                    if(str_offset == allocated) {
                        
                        allocated *= 2;
                        str = reallocate(str, allocated, offset);
                    }
                    
                    str[str_offset++] = symbol;
                    mode = 2;
                    last = 1;
                    
                } else if(symbol == 'x') {
                    
                    quotient = init_fraction(one_num, one_denom);
                    quotient -> numerator -> sign = sign;
                    
                    mode = 5;
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else if(mode == 2) {
                
                /* Reading numerator, digit read */
                
                if(isdigit(symbol)) {
                    
                    if(str_offset == allocated) {
                        
                        allocated *= 2;
                        str = reallocate(str, allocated, offset);
                    }
                    
                    str[str_offset++] = symbol;
                    
                } else if(symbol == '/' || symbol == 'x' ||
                          symbol == '+' || symbol == '-')
                {
                    num = init_integer(str_offset);
                    num -> sign = sign;
                    
                    for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                        num -> digits[str_offset - i - 1] = str[i] - '0';
                    
                    normalize_integer(num);
                    
                    str_offset = 0;
                    allocated = 1;
                    str = reallocate(str, allocated, offset);
                    
                    if(symbol == '/') {
                        
                        mode = 3;
                        last = 2;
                        
                    }  else if(symbol == 'x') {
                        
                        quotient = init_fraction(num, one_denom);
                        free_integer(num);
                        num = NULL;
                        
                        mode = 5;
                        last = 2;
                        
                    } else if(symbol == '+' || symbol == '-') {
                        
                        quotient = init_fraction(num, one_denom);
                        free_integer(num);
                        num = NULL;
                        
                        free_fraction(P -> factors[0]);
                        P -> factors[0] = quotient;
                        quotient = NULL;
                        
                        mode = 1;
                        last = 2;
                        
                        if(symbol == '+')
                            sign = true;
                        else
                            sign = false;
                    }
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else if(mode == 3) {
                
                /* Reading denominator, no digits read */
                
                if(isdigit(symbol)) {
                    
                    if(str_offset == allocated) {
                        
                        allocated *= 2;
                        str = reallocate(str, allocated, offset);
                    }
                    
                    str[str_offset++] = symbol;
                    mode = 4;
                    last = 3;
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else if(mode == 4) {
                
                /* Reading denominator, digit read */
                
                if(isdigit(symbol)) {
                    
                    if(str_offset == allocated) {
                        
                        allocated *= 2;
                        str = reallocate(str, allocated, offset);
                    }
                    
                    str[str_offset++] = symbol;
                    
                } else if(symbol == 'x' || symbol == '+' ||
                          symbol == '-')
                {
                    denom = init_natural(str_offset);
                    
                    for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                        denom -> digits[str_offset - i - 1] = str[i] - '0';
                    
                    normalize_natural(denom);
                    
                    str_offset = 0;
                    allocated = 1;
                    str = reallocate(str, allocated, offset);
                    
                    if(symbol == 'x') {
                        
                        quotient = init_fraction(num, denom);
                        free_integer(num);
                        free_natural(denom);
                        num = NULL;
                        denom = NULL;
                        
                        mode = 5;
                        last = 4;
                        
                    } else if(symbol == '+' || symbol == '-') {
                        
                        quotient = init_fraction(num, denom);
                        free_integer(num);
                        free_natural(denom);
                        num = NULL;
                        denom = NULL;
                        
                        free_fraction(P -> factors[0]);
                        P -> factors[0] = quotient;
                        quotient = NULL;
                        
                        mode = 1;
                        last = 4;
                        
                        if(symbol == '+')
                            sign = true;
                        else
                            sign = false;
                    }
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
            
            } else if(mode == 5) {
                
                /* "x" */
                
                if(symbol == '^') {
                    
                    mode = 6;
                    
                } else if(symbol == '+' || symbol == '-') {
                        
                    expand_polynomial(P, 1);
                    free_fraction(P -> factors[1]);
                    
                    if(last == 0) {
                        
                        P -> factors[1] = init_fraction(one_num, one_denom);
                        P -> factors[1] -> numerator -> sign = sign;
                        quotient = NULL;
                        
                    } else {
                        
                        P -> factors[1] = quotient;
                        quotient = NULL;
                    }
                    
                    mode = 1;
                    last = 5;
                    
                    if(symbol == '+')
                        sign = true;
                    else
                        sign = false;
                        
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else if(mode == 6) {
                
                /* Reading degree, no digit read */
                
                if(isdigit(symbol)) {
                    
                    degree *= 10;
                    degree += symbol - '0';
                    ++degree_length;
                    
                    mode = 7;
                    last = 6;
                    
                } else {
                    
                    /* Unexpected symbol */
                    
                    success = false;
                }
                
            } else {
                
                /* Reading degree, digit read */
                
                if(degree_length > 9) {
                    
                    /* Too big degree */
                    
                    success = false;
                
                } else {
                    
                    if(isdigit(symbol)) {
                        
                        degree *= 10;
                        degree += symbol - '0';
                        ++degree_length;
                        
                    } else if(symbol == '+' || symbol == '-') {
                        
                        expand_polynomial(P, degree);
                        
                        free_fraction(P -> factors[degree]);
                        P -> factors[degree] = quotient;
                        quotient = NULL;
                        
                        degree = 0;
                        
                        mode = 1;
                        last = 7;
                        
                        if(symbol == '+')
                            sign = true;
                        else
                            sign = false;
                        
                    } else {
                        
                        /* Unexpected symbol */
                        
                        success = false;
                    }
                }
            }
            
            symbol = skip_spaces();
        }
        
        if(feof(stdin)) terminate(RCODE_EOF);
        
        if(success == true) {
            
            if(mode == 0) {
                
                /* Numerator, sign not read */
                
                success = false;
                
            } else if(mode == 1) {
               
                /* Numerator, sign read, no digit */
                
                success = false;
                
            } else if(mode == 2) {
                
                /* Numerator, digit read */
                
                num = init_integer(str_offset);
                num -> sign = sign;
                
                for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                    num -> digits[str_offset - i - 1] = str[i] - '0';
                
                normalize_integer(num);
                
                free_fraction(P -> factors[0]);
                P -> factors[0] = init_fraction(num, one_denom);
                
            } else if(mode == 3) {
                
                /* Denominator, no digit read */
                
                success = false;
                
            } else if(mode == 4) {
                
                /* Denominator, digit read */
                
                denom = init_natural(str_offset);
                
                for(size_t i = str_offset - 1; i != SIZE_MAX; --i)
                    denom -> digits[str_offset - i - 1] = str[i] - '0';
                
                normalize_natural(denom);
                
                free_fraction(P -> factors[0]);
                P -> factors[0] = init_fraction(num, denom);
                
            } else if(mode == 5) {
                
                /* "x" */
                
                expand_polynomial(P, 1);
                free_fraction(P -> factors[1]);
                
                if(last == 0) {
                    
                    P -> factors[1] = init_fraction(one_num, one_denom);
                    
                } else {
                    
                    P -> factors[1] = quotient;
                    quotient = NULL;
                }
                
            } else if(mode == 6) {
                
                /* Degree, no digit read */
                
                success = false;
                
            } else {
                
                /* Degree, digit read */
                
                expand_polynomial(P, degree);
                
                free_fraction(P -> factors[degree]);
                P -> factors[degree] = quotient;
                quotient = NULL;
            }
        }
        
        if(success == false) {
            
            /* Skipping to newline */
            
            while(!feof(stdin) && symbol != '\n')
                symbol = getchar();
            
            printf(UNEXP_SYMBOL "\n\n");
            
            free_polynomial(P);
        }
        
        free_integer(one_num);
        free_natural(one_denom);
        if(num != NULL) free_integer(num);
        if(denom != NULL) free_natural(denom);
        if(quotient != NULL) free_fraction(quotient);
        free_logged(str, offset);
    }
    
    normalize_polynomial(P);
    
    return P;
}


void write_quotient(fraction *Q, size_t degree, bool first) {
    
    if(Q -> numerator -> length > 1 || Q -> numerator -> digits[0] != 0 ||
       first == true)
    {
        if(Q -> numerator -> sign == true) {
            
            if(first == false)
                printf(" + ");
            
        } else {
            
            if(first == false)
                printf(" - ");
            else
                putchar('-');
        }
        
        if(Q -> numerator -> length > 1 || Q -> numerator -> digits[0] != 1 ||
           Q -> denominator -> length > 1 || Q -> denominator -> digits[0] != 1 ||
           degree == 0)
        {
            for(size_t i = Q -> numerator -> length - 1; i != SIZE_MAX; --i)
                putchar(Q -> numerator -> digits[i] + '0');
            
            if(Q -> denominator -> length > 1 || Q -> denominator -> digits[0] != 1) {
                
                putchar('/');
                
                for(size_t i = Q -> denominator -> length - 1; i != SIZE_MAX; --i)
                    putchar(Q -> denominator -> digits[i] + '0');
            }
        }
        
        if(degree > 1) {
            
            printf("x^" PR_SIZET, (unsigned long long)degree);
            
        } else if(degree == 1) {
            
            putchar('x');
        }
    }
}


void write_polynomial(polynomial *P) {
    
    write_quotient(P -> factors[P -> degree], P -> degree, true);
    
    for(size_t i = P -> degree - 1; i != SIZE_MAX; --i)
        write_quotient(P -> factors[i], i, false);
    
    fflush(stdout);
    
    print("\n"); fflush(stderr);
}
