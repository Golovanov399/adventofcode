#!/usr/bin/env python3

lines = []
while True:
	s = input()
	lines.append(s)
	if s.strip()[0] in '+*':
		break
op = ''
n = len(lines) - 1
mx = max(len(s) for s in lines)
ans = 0
cur = 0
for i in range(mx):
	if i < len(lines[-1]) and lines[-1][i] in '+*':
		op = lines[-1][i]
		if op == '+':
			cur = 0
		else:
			cur = 1
	digits = [lines[j][i] for j in range(n) if i < len(lines[j]) and lines[j][i].isdigit()]
	if not digits:
		ans += cur
		cur = 0
		op = ''
		continue
	num = int(''.join(digits))
	if op == '+':
		cur += num
	else:
		cur *= num
print(ans + cur)