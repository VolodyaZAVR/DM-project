polynomial *P1(polynomial *A, polynomial *B)// модуль сложения двух многочленов
{
  size_t i = 0;//переменная для прохождения по массиву
    polynomial *C = copy_polynomial(A);
  
  if(A -> degree > B -> degree){//определяем степень какого многочлена больше
    for(i = 0; i < B -> degree+1; i++){
      C -> factors[i] = Q5(A -> factors[i], B -> factors[i]);//вызов функции сложения рациональных дробей
    }
  }
  else{//все действия происходят аналогично но многочлены меняются местами 
    for(i = 0; i < A -> degree+1; i++){
      C -> factors[i] = Q5(B -> factors[i], A -> factors[i]);//вызов функции сложения рациональных дробей
    }
  }
  return C;
}
