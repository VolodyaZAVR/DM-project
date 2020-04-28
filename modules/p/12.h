polynomial *P12(polynomial *input)
{
    polynomial *res = NULL;
    size_t temp;

    temp = input -> degree;
    res -> degree = temp - 1;

    while (temp != 0) {
        res -> factors[temp - 1] = (fraction *) ((long long unsigned int) input->factors[temp] * temp);
        temp--;
    }

    return res;
}
