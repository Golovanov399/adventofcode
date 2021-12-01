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
	for i in range(idx + 2, len(tokens), 4):
		nc = tokens[i + 1] + " " + tokens[i + 2]
		g[nc].append(col)

st = ["shiny gold"]
S = set(st)
i = 0
while i < len(st):
	col = st[i]
	for nc in g[col]:
		if nc not in S:
			S.add(nc)
			st.append(nc)
	i += 1

print(len(S) - 1)
