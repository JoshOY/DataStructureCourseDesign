import copy

qsort_step = 0

def quick_sort(sorting_list):
    global qsort_step
    ls = copy.deepcopy(sorting_list)
    if len(sorting_list) == 0:
        return []
    elif len(sorting_list) == 1:
        return sorting_list
    else:
        pivot = ls[0]
        qsort_step += 1
        left = quick_sort([x for x in ls[1:] if x < pivot])
        right = quick_sort([x for x in ls[1:] if x >= pivot])
        return left + [pivot] + right

if __name__ == "__main__":
    sList=[ 13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print([quick_sort(sList), qsort_step])