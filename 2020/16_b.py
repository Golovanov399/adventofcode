#!/usr/bin/env python3

def is_good(num, rgs):
	for l, r in rgs:
		if l <= num <= r:
			return True
	return False

with open("in.in") as f:
	ranges = []
	fields = []
	while True:
		line = f.readline().strip()
		if not line:
			break
		s = line[line.index(':') + 2:].split(" or ")
		fields.append([])
		for x in s:
			fields[-1].append(tuple(map(int, x.split('-'))))
		ranges.extend(fields[-1])
	assert f.readline().strip() == "your ticket:"
	line = f.readline().strip()
	my_ticket = list(map(int, line.split(',')))
	line = f.readline().strip()
	assert f.readline().strip() == "nearby tickets:"
	tickets = []
	while True:
		line = f.readline().strip()
		if not line:
			break
		good = True
		a = list(map(int, line.split(',')))
		for x in a:
			ok = False
			for l, r in ranges:
				if l <= x <= r:
					ok = True
			if not ok:
				good = False
		if good:
			tickets.append(a)
	sz = len(fields)
	mat = [[True] * sz for i in range(sz)]
	for i in range(sz):
		for j in range(sz):
			for t in tickets:
				if not is_good(t[j], fields[i]):
					mat[i][j] = False
	perm = [-1] * sz
	while True:
		idx = -1
		for i in range(len(mat)):
			if perm[i] > -1:
				continue
			if len(list(filter(lambda x: x, mat[i]))) == 1:
				idx = i
		if idx == -1:
			break
		perm[idx] = mat[idx].index(True)
		for i in range(sz):
			mat[i][perm[idx]] = i == idx
	ans = 1
	for i in perm[:6]:
		ans *= my_ticket[i]
	print(ans)
