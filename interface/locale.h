/* English locale */

#pragma once

#define TITLE           "Discrete math colloquium project"

#define USAGE           "Print L to get list of available modules.\n" \
                        "Print E to exit.\n" \
                        "\n" \
                        "To call module, print it name in [BLOCK][NUMBER] or [BLOCK]-[NUMBER] format.\n" \
                        "Examples: N-12, P3.\n"
                        
#define CMD_WAIT        "Command: "

#define UNEXP_SYMBOL    "Error: unexpected symbol"
#define UNEXP_EOF       "Error: unexpected end of input"
#define UNKN_CMD        "Error: unknown command or block"

#define FIRST_ARG_LN    "First argument (long natural): "
#define SECOND_ARG_LN   "Second argument (long natural): "

#define FIRST_ARG_LI    "First argument (long integer): "
#define SECOND_ARG_LI   "Second argument (long integer): "

#define FIRST_ARG_INT   "First argument (int): "
#define SECOND_ARG_INT  "Second argument (int): "
#define THIRD_ARG_INT   "Third argument (int): "

#define FIRST_FRACT     "First fraction (e.g. -123 / 456): "
#define SECOND_FRACT    "Second fraction (e.g. -123 / 456): "

#define FIRST_POLY      "First argument (polynomial)\n"
#define SECOND_POLY     "Second argument (polynomial)\n"

#define DEGREE          "    Degree: "

#define DEG_FACTOR      " degree factor: "
#define DEG_FACTOR_OUT  " degree: "

#define NUMERATOR       "    Numerator (natural): "
#define DENOMINATOR     "    Denominator (integer): "

#define RESULT          "Result: "

#define TRUE            "True"
#define FALSE           "False"

#define INV_MOD_INPUT   "invalid module input"


/* LIST */

#define LIST_TITLE      "                           List of available modules"
#define BLOCK_N         "                           Natural numbers with zero"
#define BLOCK_Z         "                                    Integers"
#define BLOCK_Q         "                                Rational numbers"
#define BLOCK_P         "                                   Polynomials"


/* Block N */

#define N_1_DESCR   "    N-1      COMM_NN_D      Compare numbers"
#define N_2_DESCR   "    N-2      NZER_N_B       Check for zero equality"
#define N_3_DESCR   "    N-3      ADD_1N_N       Add 1"
#define N_4_DESCR   "    N-4      ADD_NN_N       Addition of numbers"
#define N_5_DESCR   "    N-5      SUB_NN_N       Subtraction second from first"
#define N_6_DESCR   "    N-6      MUL_ND_N       Multiplying number by a digit"
#define N_7_DESCR   "    N-7      MUL_Nk_N       Multiplying by 10^k"
#define N_8_DESCR   "    N-8      MUL_NN_N       Product of two numbers"
#define N_9_DESCR   "    N-9      SUB_NDN_N      Subtraction second multiplied by digit from first"
#define N_10_DESCR  "    N-10     DIV_NN_Dk      First number of division"
#define N_11_DESCR  "    N-11     DIV_NN_N       Quotient from division"
#define N_12_DESCR  "    N-12     MOD_NN_N       Remainder from division"
#define N_13_DESCR  "    N-13     GCF_NN_N       Greatest common factor"
#define N_14_DESCR  "    N-14     LCM_NN_N       Least common multiple"


/* Block Z */

#define Z_1_DESCR   "    Z-1      ABS_Z_N        Absolute value"
#define Z_2_DESCR   "    Z-2      POZ_Z_D        Check if positive"
#define Z_3_DESCR   "    Z-3      MUL_ZM_Z       Multiple by (-1)"
#define Z_4_DESCR   "    Z-4      TRANS_N_Z      Transform from natural to integer"
#define Z_5_DESCR   "    Z-5      TRANS_Z_N      Transform from integer to natural"
#define Z_6_DESCR   "    Z-6      ADD_ZZ_Z       Addition of numbers"
#define Z_7_DESCR   "    Z-7      SUB_ZZ_Z       Subtraction of numbers"
#define Z_8_DESCR   "    Z-8      MUL_ZZ_Z       Product of numbers"
#define Z_9_DESCR   "    Z-9      DIV_ZZ_Z       Quotient of dividing"
#define Z_10_DESCR  "    Z-10     MOD_ZZ_Z       Remainder of dividing"


/* Block Q */

#define Q_1_DESCR   "    Q-1      RED_Q_Q        Fraction reduction"
#define Q_2_DESCR   "    Q-2      INT_Q_B        Check if rational is integer"
#define Q_3_DESCR   "    Q-3      TRANS_Z_Q      Transform from integer to fraction"
#define Q_4_DESCR   "    Q-4      TRANS_Q_Z      Transform from fraction to integer"
#define Q_5_DESCR   "    Q-5      ADD_QQ_Q       Adding fractions"
#define Q_6_DESCR   "    Q-6      SUB_QQ_Q       Subtracting fractions"
#define Q_7_DESCR   "    Q-7      MUL_QQ_Q       Multiplying fractions"
#define Q_8_DESCR   "    Q-8      DIV_QQ_Q       Dividing fractions"


/* Block P */

#define P_1_DESCR   "    P-1      ADD_PP_P       Addition"
#define P_2_DESCR   "    P-2      SUB_PP_P       Subtraction"
#define P_3_DESCR   "    P-3      MUL_PQ_P       Multiplying by digit"
#define P_4_DESCR   "    P-4      MUL_Pxk_P      Multiplying by x^k"
#define P_5_DESCR   "    P-5      LED_P_Q        Highest coefficient"
#define P_6_DESCR   "    P-6      DEG_P_N        Degree"
#define P_7_DESCR   "    P-7      FAC_P_Q        GCD of numerators and LCM of denominators"
#define P_8_DESCR   "    P-8      MUL_PP_P       Multiplying"
#define P_9_DESCR   "    P-9      DIV_PP_P       Quotient of division"
#define P_10_DESCR  "    P-10     MOD_PP_P       Remainder of division"
#define P_11_DESCR  "    P-11     GCF_PP_P       GCD"
#define P_12_DESCR  "    P-12     DER_PP_P       Derivative"
#define P_13_DESCR  "    P-13     NMR_PP_P       Multiple roots to simple"
