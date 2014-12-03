import copy

def shell_sort(sorting_list):
    step = 0
    ls = copy.deepcopy(sorting_list)
    gap = int(len(ls) / 2)
    while gap > 0:
        for i in range(gap, len(ls)):
            key = ls[i]
            j = i - gap
            while j >= 0 and ls[j] > key:
                ls[j + gap] = ls[j]
                step += 1
                j -= gap
            ls[j+gap] = key
        gap /= 2
    return (ls, step)

if __name__ == "__main__":
    sList=[ 13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(shell_sort(sList))