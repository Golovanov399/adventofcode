#!/usr/bin/env python3

from collections import defaultdict

with open("in.in") as f:
	n = int(f.readline())
	a = map(int, filter(lambda x: x != 'x', f.readline().split(',')))

opt = (n, 0)
for d in a:
	opt = min(opt, ((n + d - 1) // d * d - n, d))

print(opt[0] * opt[1])