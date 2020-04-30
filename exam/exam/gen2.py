#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

from random import seed
from random import random
from random import randint
from random import choice
from random import sample

seed(random())

n = randint(1, 1000)
print(n)

for i in range(n):
	num = randint(1,20)
	print(num, end = " ")
print("")