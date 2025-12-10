#!/usr/bin/env python3

inf = 10**9

lines = []
while True:
	try:
		s = input()
	except EOFError:
		break
	if not s.strip():
		break
	lines.append(s)
ans = 0
for line in lines:
	a = line.split()
	need = a[0][1:-1]
	n = len(a[0]) - 2
	need = sum(2**i for i in range(len(need)) if need[i] == '#')
	buttons = [sum(2**i for i in map(int, t[1:-1].split(','))) for t in a[1:-1]]
	dst = [inf] * (2**n)
	dst[0] = 0
	for b in buttons:
		if not b:
			continue
		for i in range(2**n):
			dst[i] = min(dst[i], dst[i ^ b] + 1)
	ans += dst[need]
print(ans)