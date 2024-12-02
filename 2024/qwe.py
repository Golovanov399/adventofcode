#!/usr/bin/env python3

def is_inc(a):
	last = -1
	for x in a:
		if last == -1:
			last = x
		elif not (last + 1 <= x <= last + 3):
			return False
		else:
			last = x
	return True

def is_ok(a):
	return is_inc(a) or is_inc(a[::-1])

cnt = 0
while True:
	line = input().split()
	if not line:
		break
	a = list(map(int, line))
	ok = is_ok(a)
	for i in range(len(a)):
		if is_ok(a[:i] + a[i+1:]):
			ok = True
			break
	if ok:
		cnt += 1

print(cnt)