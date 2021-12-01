#!/usr/bin/env python3

with open("in.in") as f:
	n = int(f.readline())
	a = list(f.readline().split(','))

mod = 1
rem = 0
for i in range(len(a)):
	if a[i] == 'x':
		continue
	m = int(a[i])
	while (rem + i) % m:
		rem += mod
	mod *= m

print(rem)