natural *Z1(integer *A){
    natural ANS;
      if(A.A){
        ANS.length = A.length;
        ANS.digits = (int*) malloc(ANS.n*sizeof(int));
        for (int i = 0; i < A.n; ++i){
         *(ANS.digits+i) = *(A.digits+i);
        }
      }
      else printf("ERROR\n");
      return *ANS;
}
