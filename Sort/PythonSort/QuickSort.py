import random

def generate_list(n=5, max_num=100):
    #result = []
    return random.sample(range(1, max_num), n)

def quick_sort(test_list):
    n = len(test_list)
    if n <= 1:
        return test_list

    greater = list()
    less = list()
    temp = test_list.pop(random.randint(0, n-1))
    for item in test_list:
        if item < temp:
            less.append(item)
        else:
            greater.append(item)
    return quick_sort(less) + [temp] + quick_sort(greater)

if __name__ == '__main__':
    test_list = generate_list(5, 100)
    print "test list : %s" % test_list
    result = quick_sort(test_list)
    print "Sorted list: %s" % result
