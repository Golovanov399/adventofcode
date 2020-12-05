#!/usr/bin/env python3

with open("in.in") as f:
	a = f.read().strip().split()

nums = set()
for s in a:
	t = s
	t = t.replace('F', '0')
	t = t.replace('B', '1')
	t = t.replace('L', '0')
	t = t.replace('R', '1')
	nums.add(int(t, 2))

for i in range(1, 1023):
	if i - 1 in nums and i + 1 in nums and i not in nums:
		print(i)
