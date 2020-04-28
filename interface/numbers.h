/* Numbers manipulating functions */

#pragma once

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "system.h"
#include "io.h"
#include "locale.h"


/* Windows size_t printf fix */

#if defined(_WIN32)
    #define PR_SIZET "%" PRIuMAX
#else
    #define PR_SIZET "%zu"
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

void swap_natural(natural **A, natural **B);            /* Swap */

void free_natural(natural *N);                          /* Remove from memory */

natural *read_natural(const char *message);             /* Read from stdin */

void write_natural(natural *N);                         /* Write to stdout */


/* Integer numbers */

integer *init_integer(size_t length);                   /* Initialize */

integer *copy_integer(integer *N);                      /* Copy */

void resize_integer(integer *N, size_t new_length);     /* Resize */

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

void resize_polynomial(polynomial *P, size_t new_degree);  /* Change degree */

void free_polynomial(polynomial *P);                        /* Remove from memory */

polynomial *read_polynomial(const char *message);           /* Read */

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


void swap_natural(natural **A, natural **B) {
    
    natural *temp = *A;
    *A = *B;
    *B = temp;
}


void free_natural(natural *N) {
	
	/* TEMPORARY BUGFIX */
	
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == N) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
	
    
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


void swap_integer(integer **A, integer **B) {
    
    integer *temp = *A;
    *A = *B;
    *B = temp;
}


void free_integer(integer *N) {
	
	/* TEMPORARY BUGFIX */
	
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == N) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
	
    
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
	
	bool correct_address = false;
	
	for(size_t i = 0; i < pointers_offset; ++i) {
		
		if(pointers[i] == F) {
			correct_address = true;
			break;
		}
	}
	
	if(correct_address == false) return;
    
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
        result -> factors[i] = P -> factors[i];
    
    return result;
}


void resize_polynomial(polynomial *P, size_t new_degree) {
    
    if((P -> degree) > new_degree) {
        
        /* Freeing unnecessary factors */
        
        for(size_t i = new_degree + 1; i <= (P -> degree); ++i)
            free_fraction(P -> factors[i]);
    }
    
    P -> factors = reallocate(P, (new_degree) + 1 * sizeof(fraction), P -> offset_factors);
    P -> degree = new_degree;
}


void free_polynomial(polynomial *P) {
    
    for(size_t i = 0; i <= (P -> degree); ++i)
        free_fraction(P -> factors[i]);
    
    free_logged(P, P -> offset_struct);
}


polynomial *read_polynomial(const char *message) {
    
    /* Initializing polynomial */
    
    size_t offset;
    polynomial *P = mallocate(sizeof(*P), &offset);
    
    P -> offset_struct = offset;
    
    print(message);
    
    /* Reading polynomial */
    
    P -> degree = read_int(DEGREE);
    
    P -> factors = mallocate(((P -> degree) + 1) * sizeof(fraction), &offset);
    
    P -> offset_factors = offset;
    
    char hint[4 + 20 + strlen(DEG_FACTOR)];
    
    strcpy(hint, "    ");
    
    for(size_t i = P -> degree; i != SIZE_MAX; --i) {
        
        int length = sprintf(hint + 4, PR_SIZET, i);
        strcpy(hint + 4 + length, DEG_FACTOR);
        fraction *Q = read_fraction(hint);
        
        P -> factors[i] = Q;
    }
    
    print("\n");
    
    return P;
}


void write_polynomial(polynomial *P) {
    
    for(size_t i = (P -> degree); i != SIZE_MAX; --i) {
        
        fprintf(stderr, "    ");
        fprintf(stderr, PR_SIZET, i);
        fprintf(stderr, DEG_FACTOR_OUT);
        
        write_fraction(P -> factors[i]);
    }
}
