#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

from random import seed
from random import random
from random import randint
from random import choice
from random import sample

seed(random())

n = randint(1, 5)

seq = [i for i in range(1,n+1)]
#print (seq)

print(n)

for i in range(n):
	p = randint(0, 10)
	c = randint(0, 10)
	print(p,c)

w = randint(1,5)

print(w)

for i in range(w):
	l = randint(0, 10)
	ni = randint(1,n)
	print(l,ni,end="")
	vals = sample(seq, ni)
	for j in vals:
		print(" " + str(j), end = "")
	print("")