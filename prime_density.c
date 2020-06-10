/*
    This project aims to find the density of primes 
    as we tend to infinity, with efficiency.
*/

#include <stdio.h>
#define boolean unsigned char
#define PRIME 1
#define EOF "\n"

const int SAMPLE_LENGTH = 10;
const unsigned long long int MAX_BOUND = 40000000;
unsigned long long int length = MAX_BOUND >> 1;

void find_primes( boolean* odd_nums );                                      // uses Eratosthenes sieve to find primes in the range
void _increment(int* i, int i_inc, int* j, int j_inc, int* k,
                int k_inc, int* m, int m_inc, int* n, int n_inc);
int _get_odd(int idx);

int main() {
    // array of booleans to show if odds[i] = 2i + 1 is prime or not
    // if even, don't include one, since we know its not prime, and if odd,
    // include the odd number at the end so length + 1 - 1 = length 
    if (MAX_BOUND % 2 == 0) length --;
    // initialize every slot to PRIME
    boolean odds[length];
    for (int i = 0; i < length; ++ i) {
        odds[i] = PRIME;
    }

    find_primes(odds);

    // write out in binary mode to conserve space; 1 = PRIME
    FILE* fptr = fopen("primes.txt", "wb");
    if (fptr) {
        for (int i = 0; i < length; ++ i)
            fprintf(fptr, "%d", odds[i]);
        fprintf(fptr, EOF);
    } else {
        fclose(fptr);
        printf("Failure in writing out.\n");
        exit(1);
    }

    fclose(fptr);
    return 0;
}

void debug(boolean* ptr) {
    printf("Prime array:\n");
    for (int i = 0; i < length; ++ i) 
        if (ptr[i])                 // display only the primes
            printf("%d ", _get_odd(i));
    printf("\n");
}

// no worries about aliasing
void _increment(int* i, int i_inc, int* j, int j_inc, int* k, 
                int k_inc, int* m, int m_inc, int* n, int n_inc) {
    *i += i_inc;
    *j += j_inc;
    *k += k_inc;
    *m += m_inc;
    *n += n_inc;
}

// convert odd number to index
int _get_odd(int idx) {
    // ith odd = 2i + 1
    return (2 * ++idx) + 1;
}

// marks non-primes as !PRIME and primes are left marked as PRIME
void find_primes( boolean* odd_nums ) {
    // numbers to mark off all their multiples, narrowing down potential primes
    int i, j, k, m, n;
    int i_inc, j_inc, k_inc, m_inc, n_inc;
    // the highest n to filter out nonprimes has be in the form 3n = m, where m <= MAX_BOUND
    // since we start by checking for primes by multiplying number by 3, 4, 5, so on...
    int iterate_to = ( (2 * length) - 1 ) / 3;

    // if non-prime mark as long i
    for (int ctr = 0; ctr <= iterate_to - 5; ctr += 5) {
        // efficiency: do this in parallel by loop unrolling
        // also, efficieny: 1*i cant be marked off as 'non prime' since it divides itself
        // 2*i is even and not in the list for optimization, so start by 3*i
        i = ctr; 
        j = i + 1; 
        k = i + 2;
        m = i + 3;
        n = i + 4;

        // efficiency: only primes can filter out non-primes further, avoiding redundancy
        if (odd_nums[i] || odd_nums[j] || odd_nums[k] || odd_nums[m] || odd_nums[n]) {
            i_inc = _get_odd(i); 
            j_inc = _get_odd(j); 
            k_inc = _get_odd(k);
            m_inc = _get_odd(m);
            n_inc = _get_odd(n);
            _increment(&i, i_inc, &j, j_inc, &k, k_inc, &m, m_inc, &n, n_inc);

            // we know that (odd) multiples of i, j, k are located at offsets i, j, k
            while (i < length) {
                if (j < length) 
                    odd_nums[j] = !PRIME;
                if (k < length) 
                    odd_nums[k] = !PRIME;
                if (m < length) 
                    odd_nums[m] = !PRIME;
                if (n < length)
                    odd_nums[n] = !PRIME;
                // we know i is the smallest, will take the most time to reach length
                // will always be in-bounds of length
                odd_nums[i] = !PRIME;
                _increment(&i, i_inc, &j, j_inc, &k, k_inc, &m, m_inc, &n, n_inc);
            }
        }
    }
}
