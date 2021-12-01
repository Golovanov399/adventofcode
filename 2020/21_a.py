#!/usr/bin/env python3

from collections import defaultdict

d = dict()
cnt = defaultdict(int)

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
		for x in a:
			cnt[x] += 1

safe = set(cnt.keys())
for v in d.values():
	for x in v:
		if x in safe:
			safe.remove(x)

ans = 0
for x in safe:
	ans += cnt[x]

print(ans)
