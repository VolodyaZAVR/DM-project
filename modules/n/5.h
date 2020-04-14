// Nikolaenko and Kacer
natural *N5(natural *A, natural *B) {
	natural *C, *D;
    int q;
    C = init_natural(A -> length);
    D = init_natural(B -> length);
    C -> length = A -> length;
    D -> length = B -> length;
    for(int i = 0; i < (C -> length); i++) C -> digits[i] = (A -> digits[i]);
    for(int i = 0; i < (D -> length); i++) D -> digits[i] = (B -> digits[i]);
	// compare the numbers
    q = N1(A,B);

    if(q == 2){
        for(int i = 0; i < (D -> length); i++){
            if((C -> digits[i]) >= (D -> digits[i])) C -> digits[i] -= (D -> digits[i]); // subtraction
            else{ // take a ten
                int k = i + 1;
                while((C -> digits[k]) == 0) k++;
                
                C -> digits[k--] -= 1; // subtract one from whom we borrow
                while(k != i) C -> digits[k--] = 9; // if there are zeros between who is being borrowed and who is being borrowed for, then we replace them with nines
                
                C -> digits[i] += (10 - (D -> digits[i])); 
            } 
        }
        while(C -> digits[(C -> length) - 1] == 0) resize_natural(C, (C -> length) - 1);
    }else if(q == 1){
	    for(int i = 0; i < (C -> length); i++){
            if((D -> digits[i]) >= (C -> digits[i])) D -> digits[i] -= (C -> digits[i]); // subtraction
            else{ // take a ten
                int k = i + 1;
                while((D -> digits[k]) == 0) k++;
                
                D -> digits[k--] -= 1; // subtract one from whom we borrow
                while(k != i) D -> digits[k--] = 9; // if there are zeros between who is being borrowed and who is being borrowed for, then we replace them with nines
                
                D -> digits[i] += (10 - (C -> digits[i])); 
            } 
        } 
        while(D -> digits[(D -> length) - 1] == 0) resize_natural(D, (D -> length) - 1);
    }else if(q == 0){ // when the numbers are equal
    	C -> digits[0] = 0;
    	resize_natural(C, 1);
    	C -> length = 1;
	}
    
    if((q == 2) || (q == 0)) return C;
    else return D;
}
