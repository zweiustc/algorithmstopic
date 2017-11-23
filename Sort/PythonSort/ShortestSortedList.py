#!/bin/python
# aList is a list of numbers, eg, [3,2,5,8,4]
# Find the shortest sublist which is sorted will lead to aList sorted.

import copy
import random


def generate_list(length=5, max_num=100):
	return random.sample(range(0, max_num), length)	


def find_pre_index(aList):
	for i in range(0, len(aList)):
		min_value = find_min_in_list(aList[i:])		
		if aList[i] > min_value:
			break;

	return i

def find_pre_index_large_order(aList):
	for i in range(0, len(aList)):
		max_value = find_max_in_list(aList[i:])		
		if aList[i] < max_value:
			break;

	return i

def find_after_index(aList):
	reversed_list = reverse_list(copy.deepcopy(aList))
	print "reverse list {0}".format(reversed_list)
	index = find_pre_index_large_order(reversed_list)
	return len(aList) - index - 1

def find_min_in_list(aList):
	min_value = aList[0]
	for i in aList:
		if i < min_value:
			min_value = i

	return min_value
	
def find_max_in_list(aList):
	max_value = aList[0]
	for i in aList:
		if i > max_value:
			max_value = i

	return max_value
	

def reverse_list(aList):
	list_len = len(aList)
	for i in range(0, list_len/2):
		temp = aList[i]
		aList[i] = aList[list_len-1-i]
		aList[list_len-1-i] = temp
	return aList

if __name__ == "__main__":
	max_num = 20
	aList = generate_list()
	print aList

	start_index = find_pre_index(aList)
	end_index = find_after_index(aList)
	
	if start_index < end_index:
		shortest_sorted_substring = aList[start_index:end_index+1]
	else:
		shortest_sorted_substring = []


	print "Shortest substring {0}".format(shortest_sorted_substring)
