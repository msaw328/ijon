#!/usr/bin/env python3

# This script generates constants C1, C2 and C3 used by the key expansion algorithm of IJON

from struct import pack as p, unpack as up
from math import sqrt

# All three constants are inferred from the name of the algorithm
name = "IJON"

# 4 bytes of the name are reinterpreted as a 32-bit float value
name_as_float = up('f', name.encode())[0]

# 3 seeds are generated based on the float
seeds = [0, 0, 0]
seeds[0] = sqrt(name_as_float)
seeds[1] = name_as_float
seeds[2] = pow(name_as_float, 2)

# seeds are converted to bytes again
seeds[0] = p('f', seeds[0])
seeds[1] = p('f', seeds[1])
seeds[2] = p('f', seeds[2])

# seeds reinterpreted as 32-bit integers
seeds[0] = int(seeds[0].hex(), 16)
seeds[1] = int(seeds[1].hex(), 16)
seeds[2] = int(seeds[2].hex(), 16)

print([ hex(s) for s in seeds ])

# 128 applications of the "second power -> xor 32-bit halves" procedure
for _ in range(0, 128):
    for j in [0, 1, 2]:
        tmp = seeds[j] * seeds[j]
        seeds[j] = (tmp & 0xffffffff) ^ (tmp >> 32)

b_one = bin(seeds[0])[2:].zfill(32)
b_two = bin(seeds[1])[2:].zfill(32)
b_three = bin(seeds[2])[2:].zfill(32)

# display the constants
print('C1 =', hex(seeds[0]), '->', b_one, '-> ones:', b_one.count('1'), 'zeroes:', b_one.count('0'))
print('C2 =', hex(seeds[1]), '->', b_two, '-> ones:', b_two.count('1'), 'zeroes:', b_two.count('0'))
print('C3 =', hex(seeds[2]), '->', b_three, '-> ones:', b_three.count('1'), 'zeroes:', b_three.count('0'))
