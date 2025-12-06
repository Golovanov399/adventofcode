#!/usr/bin/env python3

def f(nums, op):
	if op == '+':
		return sum(nums)
	else:
		res = 1
		for x in nums:
			res *= x
		return res

nums = []
while True:
	s = input().strip().split()
	if s[0].isdigit():
		for i in range(len(s)):
			if i >= len(nums):
				nums.append([])
			nums[i].append(int(s[i]))
	else:
		for i in range(len(s)):
			nums[i] = f(nums[i], s[i])
		break
print(sum(nums))