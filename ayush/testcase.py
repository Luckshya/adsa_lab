from random import randint
import sys

sys.stdout = open('inMat.txt',"a")

print(100)
for __ in range(1,100):
    print(__)
    for _ in range(2):
        for i in range(__):
            print(randint(1,1000),end="")
            for j in range(1,__):
                print("",randint(1,1000),end="")
            print()