integer *Z6(integer *A, integer *B)
{
    integer *R;
    natural *aN, *bN, A1, B1;
    aN = Z1(A);
    bN = Z1(B);

    if (Z2(A) == 2 && Z2(B) == 2) {
        R = N4(A, B);
        R -> sign = true;
    }
    else if (Z2(A) == 1 && Z2(B) == 1) {
        R = N4(aN, bN);
        R -> sign = false;
    }
    else if (Z2(A) == 2 && Z2(B) == 1) {
        if (N1(aN, bN) == 2) {
            R = N5(A, bN);
            R -> sign = true;
        }
        else if (N1(aN, bN) == 1) {
            R = N5(bN, A);
            R -> sign = false;
        }
    }
    else if (Z2(A) == 1 && Z2(B) == 2) {
        if (N1(aN, bN) == 2) {
            R = N5(aN, B);
            R -> sign = false;
        }
        else if (N1(aN, bN) == 1) {
            R = N5(B, aN);
            R -> sign = true;
        }
    }
    else if (Z2(A) == 0) {
        if (Z2(B) == 2) {
            B -> sign = true;
        }
        else if (Z2(B) == 2) {
            B -> sign = false;
        }
        R = B;
    }
    else if (Z1(B) == 0) {
        if (Z2(A) == 2) {
            A -> sign = true;
        }
        else if (Z2(B) == 2) {
            A -> sign = false;
        }
        R = A;
    }
    return(R);
}
