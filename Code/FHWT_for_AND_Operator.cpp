void FWHT(vector<int> &P, bool inverse){
   //note size of v must be a power of 2 mandatorily.
   int len, i, j, u, v;
   for (len = 1; 2 * len <= M; len <<= 1) {
     for (i = 0; i < M; i += 2 * len) {
         for (j = 0; j < len; j++) {
             u = P[i + j];
             v = P[i + len + j];
             if (!inverse) {
                 P[i + j] = v;
                 P[i + len + j] = (u + v) % mod;
             } else {
                 P[i + j] = (-u + v + mod) % mod;
                 P[i + len + j] = u;
             }
         }
     }
   }
}

/**********************

Ref :- https://www.hackerearth.com/problem/algorithm/submatrix-queries-7e459f97/editorial/
If you have a hard time understanding the editorial, this may help you.

Let's talk a little about FFT (Fast Fourier Transform) first. FFT aims to multiply two n-degree polynomials A and B in nlogn using these steps:
1) Calculate FFT of A and B, let them be A' and B'.
2) Calculate array C' where C'[i] = A'[i]*B'[i].
3) Calculate inverse FFT of C' to get the answer (A*B)=C.

Assuming that C[i] = coefficient of of x^i in A*B, then the procedure above adds A[j]*B[k] to C[j+k] for every j and k.

Now returning to the question, if we observe carefully, we notice that we want to modify the procedure above to add Cnt[j]*Cnt[k]*Cnt[m] to C[j AND k AND m] for every j, k, m, where Cnt[i] = count of value i in range from l to r. So basically we can imagine Cnt as a polynomial where Cnt[i] is coefficient of x^i which is the count of value i in range from l to r.

Fast Walsh–Hadamard transform is a variation of FFT which can be used with two polynomials A and B to add A[j]*B[k] to C[j AND k] for every j and k. So what we want to do with Cnt, is to calculate Cnt^3, which adds Cnt[j]*Cnt[k]*Cnt[m] to C[j AND k AND m] for every j, k, m. That is, C[i] = number of all triplets which have bitwise AND = i. So our answer is obviously C[X]. The steps to do this are very close to FFT:
1) Calculate Fast Walsh–Hadamard transform of Cnt, let it be Cnt'.
2) Calculate array C' where C'[i] = Cnt'[i]^3.
3) Calculate inverse Fast Walsh–Hadamard transform of C' to get C.

**********************/
