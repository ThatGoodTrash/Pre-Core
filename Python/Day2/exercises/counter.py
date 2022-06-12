#one, two, three, four, five = 3+3+5+4+4=19

#1 through 1000

number_list = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", 
"seventeen", "eighteen", "nineteen", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred", "thousand" ]

sum = 0

for num in range(1, 1001):
    count = 1
    if num < 21:
        sum += len(number_list[count])
        count +=1
    elif num > 20 and num < 100:
        tens_iter = 20
        single_iter = 0
        sum += (len(number_list[tens_iter]) + len(number_list[single_iter]))
        single_iter += 1
        if single_iter == 9:
            single_iter = 0
            tens_iter += 1
    elif num > 99 and num < 1000:
        hundreds_iter = 1
        tens_iter = 0
        single_iter = 0
        
        
        if single_iter == 19:
            single_iter = 0
            tens_iter = 20
            #tens_iter += 1
        elif tens_iter != 0 and single_iter == 9:
            single_iter = 0
            tens_iter += 1
        elif tens_iter == 9 and single_iter == 9:
            tens_iter = 0
            single_iter = 0
            hundreds_iter += 1
        sum += (len(number_list[hundreds_iter]) + len(number_list[-2]) + len(number_list[tens_iter]) + len(number_list[single_iter]))
        single_iter += 1
    else:
        sum += len(number_list[1] + number_list[-1])

        # list[1] + list[-2] + list[20] + list [1]


print(sum)

