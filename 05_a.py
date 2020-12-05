#!/usr/bin/env python3

with open("in.in") as f:
	a = f.read().strip().split()

ans = 0
for s in a:
	t = s
	t = t.replace('F', '0')
	t = t.replace('B', '1')
	t = t.replace('L', '0')
	t = t.replace('R', '1')
	ans = max(ans, int(t, 2))

print(ans)