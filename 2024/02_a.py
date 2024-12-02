#!/usr/bin/env python3

cnt = 0
while True:
	line = input().split()
	if not line:
		break
	a = list(map(int, line))
	inc = True
	dec = True
	last = -1
	for x in a:
		if last == -1:
			last = x
		else:
			if not (last + 1 <= x <= last + 3):
				inc = False
			if not (x + 1 <= last <= x + 3):
				dec = False
			last = x
	if inc or dec:
		cnt += 1

print(cnt)