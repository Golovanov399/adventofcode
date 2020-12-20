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

	def crop(self):
		self.a = [x[1:-1] for x in self.a[1:-1]]

	def __str__(self):
		return "\n".join(["Tile {}:".format(self.id)] + self.a)

	def fits(self, s, t):
		for i in range(len(s)):
			if s[i] == '#' and t[i] == '.':
				return False
		return True

	def count_gays(self):
		bitches = [[self.a[i][j] == '#' for j in range(len(self.a[i]))] for i in range(len(self.a))]
		pattern = """                  # 
#    ##    ##    ###
 #  #  #  #  #  #   """.split('\n')
		for i in range(len(self.a) - len(pattern) + 1):
			for j in range(len(self.a[i]) - len(pattern[0]) + 1):
				ok = True
				for l in range(len(pattern)):
					ok = ok and self.fits(pattern[l], self.a[i + l][j:])
				if ok:
					for l in range(len(pattern)):
						for m in range(len(pattern[l])):
							if pattern[l][m] == '#':
								bitches[i + l][j + m] = False
		return sum(v.count(True) for v in bitches)


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

corner = -1

for tile in tiles:
	cnt = 0
	for s in tile.sides:
		if d[to_mask(s)] == 1 and d[to_mask(s[::-1])] == 1:
			cnt += 1
	if cnt >= 2:
		corner = tile.id
		break

image = [[None] * m for i in range(n)]
i = 0
while tiles[i].id != corner:
	i += 1

while d[to_mask(tiles[i].sides[0])] != 1 or d[to_mask(tiles[i].sides[0][::-1])] != 1 or d[to_mask(tiles[i].sides[-1])] != 1 or d[to_mask(tiles[i].sides[-1][::-1])] != 1:
	tiles[i].rotate()
image[0][0] = tiles[i]
for s in tiles[i].sides:
	d[to_mask(s)] -= 1
	d[to_mask(s[::-1])] -= 1
tiles.pop(i)

x, y = 0, 1
while x < n:
	need = []
	if x > 0:
		need.append(image[x - 1][y].sides[2])
	if y > 0:
		need.append(image[x][y - 1].sides[1])
	need = [s[::-1] for s in need[::-1]]
	cand = set()
	for i in range(len(tiles)):
		for j in range(2):
			for k in range(4):
				ok = True
				for l in range(len(need)):
					if tiles[i].sides[l] != need[l]:
						ok = False
						break
				if ok:
					cand.add(i)
				tiles[i].rotate()
			tiles[i].flip()
	assert len(cand) == 1
	i = list(cand)[0]
	found = False
	for j in range(2):
		if found:
			break
		for k in range(4):
			if found:
				break
			ok = True
			for l in range(len(need)):
				if tiles[i].sides[l] != need[l]:
					ok = False
					break
			if ok:
				found = True
				break
			tiles[i].rotate()
		tiles[i].flip()
	tiles[i].flip()
	if x > 0:
		while tiles[i].sides[0] != need[-1]:
			tiles[i].rotate()
	else:
		while tiles[i].sides[-1] != need[0]:
			tiles[i].rotate()
	image[x][y] = tiles[i]
	tiles.pop(i)

	y += 1
	if y == m:
		x, y = x + 1, 0

for i in range(n):
	for j in range(m):
		image[i][j].crop()

img = []

for i in range(n):
	lns = ["" for _ in range(len(image[i][0].a))]
	for j in range(m):
		for k in range(len(image[i][j].a)):
			lns[k] += image[i][j].a[k]
			# lns[k] += image[i][j].a[k] + " "
	print(*lns, sep='\n')
	# print()
	img += lns

img = Tile(0, img)
print(img.count_gays())