#!/usr/bin/env python3

with open("in.in") as f:
	a = [[] for i in range(200)]
	for line in f:
		if not line.strip():
			break
		x = int(line.strip().split()[0][:-1])
		t = line[line.index(' '):].strip()
		t = t.split(' | ')
		if len(t) == 1 and t[0][0] == '"':
			a[x] = [t[0].strip('"')]
			continue
		for v in t:
			a[x].append(list(map(int, v.split())))
		assert len(set(len(y) for y in a[x])) == 1

	S = set()
	order = []
	def find_order(x):
		if x in S:
			return
		if isinstance(a[x][0][0], int):
			for v in a[x]:
				for y in v:
					find_order(y)
		S.add(x)
		order.append(x)

	find_order(0)
	# print(order)

	a[8].append([42, 8])
	a[11].append([42, 11, 31])

	def check(s):
		dp = [None] * len(a)
		for x in order:
			dp[x] = set()
			if isinstance(a[x][0][0], int):
				for i in range(len(s) - 1, -1, -1):
					for v in a[x]:
						can = [False] * (len(s) - i + 1)
						can[0] = True
						for idx in v:
							ncan = [False] * (len(s) - i + 1)
							for i1 in range(len(s) - i):
								if not can[i1]:
									continue
								for j1 in range(i1 + 1, len(s) - i + 1):
									if (i + i1, i + j1) in dp[idx]:
										ncan[j1] = True
							can = ncan
						for j in range(1, len(s) - i + 1):
							if can[j]:
								dp[x].add((i, i + j))
			else:
				for j in range(1, len(s) + 1):
					for i in range(j):
						if s[i:j] == a[x][0]:
							dp[x].add((i, j))
		return (0, len(s)) in dp[0]

	ans = 0
	for s in f:
		if not s.strip():
			break
		ans += int(check(s.strip()))
	print(ans)
