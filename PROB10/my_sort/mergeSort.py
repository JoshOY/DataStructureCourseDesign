import copy

merge_step = 0

def merge_sort(sorting_list):
    global merge_step
    if(len(sorting_list) <= 1):
        return sorting_list
    def merge(left, right):
        global merge_step
        rtn = []
        while len(left) != 0 and len(right) != 0:
            rtn.append(left.pop(0) if left[0] <= right[0] else right.pop(0))
            merge_step += 1
        while len(left) != 0:
            merge_step += 1
            rtn.append(left.pop(0))
        while len(right) != 0:
            merge_step += 1
            rtn.append(right.pop(0))
        return rtn
    ls = copy.deepcopy(sorting_list)
    middle_index = int(len(ls) / 2)
    left = merge_sort(ls[0:middle_index])
    right = merge_sort(ls[middle_index:])
    return merge(left, right)

if __name__ == "__main__":
    sList=[13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(merge_sort(sList), merge_step)