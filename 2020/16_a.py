#!/usr/bin/env python3

with open("in.in") as f:
	ranges = []
	while True:
		line = f.readline().strip()
		if not line:
			break
		s = line[line.index(':') + 2:].split(" or ")
		for x in s:
			ranges.append(tuple(map(int, x.split('-'))))
	assert f.readline().strip() == "your ticket:"
	line = f.readline().strip()
	line = f.readline().strip()
	assert f.readline().strip() == "nearby tickets:"
	ans = 0
	while True:
		line = f.readline().strip()
		if not line:
			break
		a = list(map(int, line.split(',')))
		for x in a:
			ok = False
			for l, r in ranges:
				if l <= x <= r:
					ok = True
			if not ok:
				ans += x
	print(ans)
