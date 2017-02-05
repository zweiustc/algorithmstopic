import random

def generate_list(n=5, max_num=100):
    #result = []
    return random.sample(range(1, max_num), n)

def select_sort(test_list):
    n = len(test_list)
    for i in range(0, n):
        mindex = i
        for j in range(i, n):
            if test_list[mindex] > test_list[j]:
                mindex = j
        temp = test_list[i]
        test_list[i] = test_list[mindex]
        test_list[mindex] = temp
    return test_list

if __name__ == '__main__':
    test_list = generate_list(5, 100)
    print "test list : %s" % test_list
    result = select_sort(test_list)
    print "Sorted list: %s" % result
