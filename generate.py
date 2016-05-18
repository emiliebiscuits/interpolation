#!/usr/bin/python3
#-*- coding:utf-8 -*

import sys
from random import *


if len(sys.argv) != 3:
	print("\033[1;31mUSAGE :\033[0m \n\t" + sys.argv[0] + " nbDimension nbPoint")
	sys.exit(1)

nbPoint = sys.argv[2]
dim = sys.argv[1]
liste = []

with open("points.txt", "w") as fichier:
	for i in range(int(nbPoint)):
		liste.insert(0, uniform(0, 50))
		for j in range(int(dim)):
			#liste.insert(0, uniform(-15, 15))
			liste.insert(0, randint(-15, 15))
		for val in liste:
			fichier.write(str(val) + " ")
		fichier.write("\n")
		liste = []

print("\033[1;32mLe fichier points.txt contient vos points !\033[0m")
sys.exit(0)

