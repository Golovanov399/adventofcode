#!/usr/bin/env python3

from collections import defaultdict

class Tile:
	def __init__(self, id, lines):
		self.a = lines[:]
		self.sides = [
			lines[0],
			"".join(x[-1] for x in lines),
			lines[-1][::-1],
			"".join(x[0] for x in lines[::-1])
		]
		self.id = id

	def flip(self):
		self.a = [x[::-1] for x in self.a]
		self.sides = [self.sides[-i][::-1] for i in range(4)]

	def rotate(self):
		self.a = ["".join([x[-1 - i] for x in self.a]) for i in range(len(self.a))]
		self.sides = self.sides[1:] + self.sides[:1]

	def __str__(self):
		return "\n".join(["Tile {}:".format(self.id)] + self.a)


with open("in.in") as f:
	n, m = 12, 12
	tiles = []
	for i in range(n * m):
		tile_id = int(f.readline().split()[1][:-1])
		tiles.append(Tile(tile_id, [f.readline().strip() for _ in range(10)]))
		f.readline()


def to_mask(s):
	return int(s.replace('.', '0').replace('#', '1'), 2)

d = defaultdict(int)
for tile in tiles:
	for s in tile.sides:
		d[to_mask(s)] += 1
		d[to_mask(s[::-1])] += 1

ids = []

for tile in tiles:
	cnt = 0
	for s in tile.sides:
		if d[to_mask(s)] == 1 and d[to_mask(s[::-1])] == 1:
			cnt += 1
	if cnt >= 2:
		print(tile.id, cnt)
		ids.append(tile.id)

prod = 1
for x in ids:
	prod *= x

print(prod)