#!/usr/bin/env python3

from collections import defaultdict

lines = open(0).readlines()
lines = [x.strip() for x in lines]

idx = lines.index("")
orders, cands = lines[:idx], lines[idx+1:]

d = defaultdict(set)
for line in orders:
	v = line.strip().split('|')
	v = [int(x) for x in v]
	d[v[0]].add(v[1])

def topsort(d):
	cnt = dict()
	def rec(x, s):
		s.add(x)
		for y in d[x]:
			if y not in s:
				rec(y, s)
	for x in d:
		s = set()
		rec(x, s)
		cnt[x] = len(s)
	return sorted(d, key=cnt.get)

ans = 0
for c in cands:
	v = c.split(',')
	v = [int(x) for x in v]
	if not v:
		break
	ok = True
	for i in range(len(v)):
		for j in range(i):
			if v[j] in d[v[i]]:
				ok = False
				break
	if ok:
		continue
	local = {x: set(y for y in d[x] if y in v) for x in v}
	v = topsort(local)
	ans += v[len(v) // 2]

print(ans)