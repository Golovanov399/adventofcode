#!/usr/bin/env python3

def hash(a, b):
	return sum(x * y for x, y in zip(a, b))

def subrec(a, need, cur, bases, res, i, taken):
	if i == len(a):
		return
	subrec(a, need, cur, bases, res, i + 1, taken)
	c = 0
	while True:
		c += 1
		ok = True
		for j in a[i]:
			cur[j] += 1
			if cur[j] > need[j]:
				ok = False
		if ok:
			h = hash(cur, bases)
			if h not in res or res[h] > taken + c:
				res[h] = taken + c
			subrec(a, need, cur, bases, res, i + 1, taken + c)
		else:
			break
	for j in a[i]:
		cur[j] -= c

def rec(a, need, bases):
	cur = [0] * len(need)
	res = dict()
	res[0] = 0
	subrec(a, need, cur, bases, res, 0, 0)
	return res

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
	need = list(map(int, a[-1][1:-1].split(',')))
	n = len(a[0]) - 2
	buttons = [list(map(int, t[1:-1].split(','))) for t in a[1:-1]]
	# bases = [1]
	# for x in need:
	# 	y = bases[-1] * (x + 1)
	# 	bases.append(y)
	# left = rec(buttons[:len(buttons)//2], need, bases)
	# right = rec(buttons[len(buttons)//2:], need, bases)
	# tmp = inf
	# for half in left:
	# 	rest = bases[-1] - half - 1
	# 	if rest in right:
	# 		tmp = min(tmp, left[half] + right[rest])
	# ans += tmp
print(ans)