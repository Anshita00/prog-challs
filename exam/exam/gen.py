#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

from random import seed
from random import random
from random import randint
from random import choice
from random import sample

seed(random())

n = randint(1, 1000)
m = randint(1, 1000)

seq = [i for i in range(1,m+1)]
#print (seq)

print(n,m)

for i in range(n):
	ni = randint(0, m)
	print(ni, end = " ")
print("")

for i in range(m):
	mi = randint(0, n)
	print(mi, end = " ")
print("")


for i in range(n):
	k = randint(0,m)
	print(k, end = " ")
	vals = sample(seq, k)
	for j in vals:
		print(j, end = " ")
	print("")
