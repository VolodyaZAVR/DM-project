integer *Z6(integer *A, integer *B)
{
    integer *R;
    natural *aN, *bN;
    aN = Z1(A);
    bN = Z1(B);
    R = init_integer(aN -> length);
    R = init_integer(bN -> length);
    R = NULL;

    if (Z2(A) == 2 && Z2(B) == 2) {
        R = Z4(N4(aN, bN));
        R -> sign = true;
    }
    else if (Z2(A) == 1 && Z2(B) == 1) {
        R = Z4(N4(aN, bN));
        R -> sign = false;
    }
    else if (Z2(A) == 2 && Z2(B) == 1) {
        if ((N1(aN, bN) == 2) || (N1(aN, bN) == 0)) {
            R = Z4(N5(aN, bN));
            R -> sign = true;
        }
        else if (N1(aN, bN) == 1) {
            R = Z4(N5(bN, aN));
            R -> sign = false;
        }
    }
    else if (Z2(A) == 1 && Z2(B) == 2) {
        if (N1(aN, bN) == 2) {
            R = Z4(N5(aN, bN));
            R -> sign = false;
        }
        else if ((N1(aN, bN) == 1) || (N1(aN, bN) == 0)) {
            R = Z4(N5(bN, aN));
            R -> sign = true;
        }
    }
    else if (Z2(A) == 0) {
        if (Z2(B) == 2) {
            B -> sign = true;
        }
        else if (Z2(B) == 1) {
            B -> sign = false;
        }
        R = init_integer(B -> length);
        R = B;
    }
    else if (Z2(B) == 0) {
        if (Z2(A) == 2) {
            A -> sign = true;
        }
        else if (Z2(A) == 1) {
            A -> sign = false;
        }
        R = init_integer(A -> length);
        R = A;
    }
    return(R);
}
