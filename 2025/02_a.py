#!/usr/bin/env python3

rgs = input().split(',')
ans = 0
for s in rgs:
	l, r = map(int, s.split('-'))
	for i in range(l, r + 1):
		t = str(i)
		if len(t) % 2 == 0 and t[:len(t)//2] == t[len(t)//2:]:
			ans += i
print(ans)