#!/usr/bin/env python3

from itertools import permutations

d = dict()

with open("in.in") as f:
	for line in f:
		if not line.strip():
			break
		s = line[:line.index('(')]
		t = line[line.index('(')+1:line.index(')')]
		a = s.strip().split()
		b = t[t.index(' ') + 1:].split(", ")
		a = set(a)
		for x in b:
			if x not in d:
				d[x] = a
			else:
				d[x] = d[x].intersection(a)

bad = set()
for v in d.values():
	bad.update(v)

keys = sorted(d.keys())
vals = list(bad)

for p in permutations(range(len(bad))):
	ok = True
	for i in range(len(keys)):
		if vals[p[i]] not in d[keys[i]]:
			ok = False
	if ok:
		print(*[vals[p[i]] for i in range(len(keys))], sep=",")
