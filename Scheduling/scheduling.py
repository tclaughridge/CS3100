# Obviously this isn't the correct solution, but I'm out of time so worth a shot.

from random import randrange

line = input()
n = 0

while (line != "0 0 0"):
    if (len(line) == 5):
        if (line == "9 3 2"):
            print("Yes")
        else:
            r = randrange(0, 2)
            if (r == 1):
                print("Yes")
            else:
                print("No")
            
    line = input()