import copy

def insertion_sort(sorting_list):
    step = 0
    ls = copy.deepcopy(sorting_list)
    for i in range(1, len(ls)):
        tmp = ls[i]
        j = i
        while j > 0 and ls[j-1] > tmp:
            ls[j] = ls[j-1]
            j -= 1
            step += 1
        ls[j] = tmp
    return (ls, step)

if __name__ == "__main__":
    sList=[ 13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(insertion_sort(sList))