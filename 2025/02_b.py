#!/usr/bin/env python3

divs = [[]]
for i in range(1, 30):
	divs.append([j for j in range(1, i) if i % j == 0])

def is_invalid(n):
	s = str(n)
	l = len(s)
	for d in divs[l]:
		if s[:l-d] == s[d:]:
			return True
	return False

rgs = input().split(',')
ans = 0
for s in rgs:
	l, r = map(int, s.split('-'))
	for i in range(l, r + 1):
		if is_invalid(i):
			ans += i
print(ans)