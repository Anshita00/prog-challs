#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

from random import seed
from random import random
from random import randint
from random import choice

seed(random())

n = randint(1, 30000)
q = randint(1, 30000)

print(n, q)

for i in range(n):
	temp = randint(0, 1000000000)
	print(temp, end = " ")

print("")
ops = ['U', 'Q']

for i in range(q):
	cur = choice(ops)
	l = randint(0,n-1)
	r = randint(l +1, n)
	if (cur == 'U'):
		v = randint(-1000000000, 1000000000)
		print(cur, l, r, v)
	else:
		print(cur, l, r)
