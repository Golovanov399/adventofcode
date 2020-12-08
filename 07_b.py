#!/usr/bin/env python3

from collections import defaultdict

with open("in.in") as f:
	a = f.readlines()

g = defaultdict(list)

for rule in a:
	if not rule.strip():
		continue
	tokens = rule.strip().split()
	idx = tokens.index("bags")
	col = " ".join(tokens[:idx])
	assert idx == 2
	if tokens[idx + 2:] == ["no", "other", "bags."]:
		continue
	for i in range(idx + 2, len(tokens), 4):
		nc = tokens[i + 1] + " " + tokens[i + 2]
		g[col].append((nc, int(tokens[i])))

ans = 0
def rec(col, mult):
	global ans
	ans += mult
	for nc, m in g[col]:
		rec(nc, mult * m)

rec("shiny gold", 1)
ans -= 1
print(ans)