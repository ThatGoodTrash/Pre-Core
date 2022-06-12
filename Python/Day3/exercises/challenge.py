#1406357289
#d1 is first digit, d2 is second digit, etc. 
#d2d3d4 = 406 is divisable by 2
#d3d4d5 = 063 is divisable by 3
#d4d5d6 = 635 is divisab le by 5
#d5d6d7 = 357 id divisable by 7
#d6d7d8 = 572 is divisable by 11
#d7d8d9 = 728 is divisable by 13
#d8d9d10 = 289 is divisable by 17

from itertools import permutations

perm = permutations(['0','1','2','3','4','5','6','7','8','9'])

sum = 0

for mutation in list(perm):
    pandigital = int(''.join(mutation))
    var1 = int(''.join(mutation[7:10]))
    var2 = int(''.join(mutation[6:9]))
    var3 = int(''.join(mutation[5:8]))
    var4 = int(''.join(mutation[4:7]))
    var5 = int(''.join(mutation[3:6]))
    var6 = int(''.join(mutation[2:5]))
    var7 = int(''.join(mutation[1:4]))
    if var1 % 17 == 0 and var2 % 13==0 and var3 % 11==0 and var4 % 7==0 and var5 % 5 ==0 and var6 % 3==0 and var7 % 2==0:
        print(pandigital)
        sum += pandigital

print("\nFinal Result")
print("=====================")
print(sum)
        

