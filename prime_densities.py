"""
    Borrows from the output of the C script that generates whether or
    not an odd number is a prime.
"""

import matplotlib.pyplot as plt

SAMPLE_LENGTH = 30_000
PRIME = 1
FILE_TO_READ = 'primes.txt'
EOF = '\n'

# read in prime status for odd numbers from text file
reader = open(FILE_TO_READ, 'r')
READ_LENGTH = int( SAMPLE_LENGTH/2 + (SAMPLE_LENGTH % 2) )
has_more = True
y = []

# private routine to fetch a sample of odd numbers straight from the file
def _fetch_sample():
    global reader, has_more

    total = 0.0
    for _ in range(READ_LENGTH):
        ch = reader.read(1)
        if ch != EOF: total += int(ch)
        else: 
            has_more = False
            reader.close()
            return

    y.append( total / (2 * SAMPLE_LENGTH) )
    return

# the first sample contains an even prime, handle this case separately
while has_more:
    _fetch_sample()
    
# finally plot the scatterplot of prime number densities within the natural numbers
plt.scatter(x=range(1, len(y) + 1), y=y)
plt.show()
