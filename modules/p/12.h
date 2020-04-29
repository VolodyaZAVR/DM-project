//Когутенко Андрей 9305
//Производная многочлена
polynomial *P12(polynomial *input)
{
    polynomial *res = NULL;
    size_t temp;

    //temp = input -> degree;
    temp = P6(input);
    res = init_polynomial(temp - 1);

    while (temp != 0) {
        res -> factors[temp - 1] = input->factors[temp];
        temp--;
    }

    return res;
}
