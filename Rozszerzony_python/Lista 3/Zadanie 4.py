from word2number import w2n
from num2words import num2words

def sortowanie(l):
    new_list = list(map(lambda x: w2n.word_to_num(x),l))
    new_list.sort()
    last_list = list(map(lambda x: num2words(x),new_list))
    return last_list

test = ["thirty thousand two hundred","eight hundred fifteen","one hundred twenty three"]
print(sortowanie(test))