#!/bin/python
import random
import time

class rainDrop(object):

    def __init__(self, center_pos, radius):
        super(rainDrop, self).__init__()
        self.center_pos = center_pos
        self.radius = radius
        self.left = min(center_pos - radius, 0)
        self.right = max(center_pos + radius, 1)
        self.length = 2*radius

    def merge_rain_drop(self, new_rain_drop):
        if new_rain_drop.left > self.right or \
                new_rain_drop.right < self.left:
            return False
        else:
            self.left = min(new_rain_drop.left, self.left)
            self.right = max(new_rain_drop.right, self.right)
            self.center_pos = (self.right + self.left) / 2
            self.length = (self.right - self.left)
            self.radius = self.length / 2
            return True

def binary_search(value, value_list):
    low = 0
    high = len(value_list) - 1
    while(low <= high):
        mid = (low + high)/2
        midval = value_list[mid]

        if midval < value:
            low = mid + 1
        elif midval > value:
            high = mid - 1
        else:
            return mid
    return low


class wetArea(object):

    def __init__(self, *args, **kwargs):
        super(wetArea, self).__init__()
        self.drops_pos = []
        self.drops_map = dict()

    def add_rain_drop(self, new_rain_drop):
        if self.drops_pos == []:
            self.drops_pos.append(new_rain_drop.center_pos)
            self.drops_map[new_rain_drop.center_pos] = new_rain_drop
        else:
            self.drops_pos = self.drops_pos.sort()
            new_drop_floor = self.binary_search(new_rain_drop.center_pos,
                                                self.drops_pos)
            arrive_end = True if new_drop_floor >= len(self.drops_pos) else False

            merged_drop = self.drops_map[self.drops_pos[new_drop_floor]].merge_rain_drop(new_rain_drop)
            if merged_drop:
                # pop the olds rain drop
                del self.drops_map[self.drops_pos[new_drop_floor]]
                del self.drops_pos[new_drop_floor]

                #self.drops_pos.append(merged_drop.center_pos)
                #self.drops_map[merged_drop.center_pos] = merged_drop
            else:
                #self.drops_map[new_rain_drop]
                #self.drops_pos[new_rain_drop.center_pos]
                merged_drop = new_rain_drop

            # check the ceiling one
            if not arrive_end:
                merged_drop = self.drops_map[self.drops_pos[new_drop_floor+1]].merge_rain_drop(merged_drop)
                if merged_drop:
                    del self.drops_map[self.drops_pos[new_drop_floor+1]]
                    del self.drops_pos[new_drop_floor+1]

            self.drops_pos.append(merged_drop.center_pos)
            self.drops_map[merged_drop.center_pos] = merged_drop

    def all_wet(self):
        if not self.drops_pos:
            return Flase
        if len(self.drops_pos) == 1:
            return self.drops_map[self.drops_pos[0]].length == 1

        return False

    def binary_search(self, value, value_list):
        low = 0
        high = len(value_list) - 1
        while(low <= high):
            mid = (low + high)/2
            midval = value_list[mid]

            if midval < value:
                low = mid + 1
            elif midval > value:
                high = mid - 1
            else:
                return mid
        return low


def rain_drop_expr():

    expr = wetArea()
    count = 0
    while True:
        

