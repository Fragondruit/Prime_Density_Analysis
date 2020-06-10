# Prime_Density_Analysis
A repository for viewing Utkarsh Nigam's sample code. Implements a highly optimized Eratosthenes Sieve algorithm to find primes in C and displaying their densities using Python's MatplotLib library.

# C File
Optimizations applied (comments in file included):
- Loop unrolling (leads to fewer loop condition checks)
- Stopping iteration at a THIRD of the size of the search space
- Only including odd numbers in the search space as even numbers (> 2) are for sure NOT prime; cutting search space in half
- Skipping sequences of composite numbers since only prime numbers are needed to filter out non-primes

Result interpretation: resulting binary string of '1110110' => 3 prime, 5 prime, 7 prime, 9 NOT prime, 11 prime, 13 prime, 15 NOT prime

The primes are written out as chars '1' or '0'; '1' = prime and '0' = non-prime. Writing the results out as 1s and 0s is done for purposes of clarity (really, bad for space efficiency), and is written out to primes.txt in a directory of choice.

# Python File
A scatterplot obeying the theoretical decay of prime number density (per Prime Number Theorem) is observed graphically.
