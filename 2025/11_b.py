#!/usr/bin/env python3

from collections import defaultdict

a = defaultdict(list)
for line in open(0).readlines():
	if not line.strip():
		break
	nodes = line.split()
	nodes[0] = nodes[0][:-1]
	a[nodes[0]] = nodes[1:]

nodes = set()
for v, to in a.items():
	nodes.add(v)
	for x in to:
		nodes.add(x)
nodes = list(nodes)

in_deg = defaultdict(int)
for v in a.values():
	for s in v:
		in_deg[s] += 1
order = [x for x in nodes if in_deg[x] == 0]
for v in order:
	for u in a[v]:
		in_deg[u] -= 1
		if in_deg[u] == 0:
			order.append(u)

ans = 0
for start, finish in [("fft", "dac"), ("dac", "fft")]:
	res = 1
	req = ["svr", start, finish, "out"]
	for i in range(len(req) - 1):
		cnt = {k: 0 for k in nodes}
		cnt[req[i]] = 1
		for v in order:
			for u in a[v]:
				cnt[u] += cnt[v]
		res *= cnt[req[i + 1]]
	ans += res
print(ans)