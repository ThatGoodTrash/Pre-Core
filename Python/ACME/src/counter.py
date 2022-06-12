#one, two, three, four, five = 3+3+5+4+4=19

#1 through 1000

number_list = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", 
"seventeen", "eighteen", "nineteen", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety", "thousand" ]

sum = 0

for num in range(1000):
    count = 1
    if num < 21:
        sum += len(number_list[count])
        count +=1
    elif num > 20 and num < 100:
        tens_iter = 20
        single_iter = 0
        sum += len(number_list[tens_iter] + number_list[single_iter])
        single_iter += 1
        if single_iter == 9:
            single_iter = 0
            tens_iter += 1

print(sum)

