import copy

def selection_sort(sorting_list):
    step = 0
    ls = copy.deepcopy(sorting_list)
    for i in range(len(ls) - 1):
        min = i                         #which index is current min
        for j in range(i+1, len(ls)):   #search for smaller number
            if ls[j] < ls[min]:
                min = j
        if min != i:                    #if found a smaller one then swap them
            (ls[i], ls[min]) = (ls[min], ls[i])
            step += 1
    return (ls, step)

if __name__ == "__main__":
    sList=[3,4,1,2,5,8,0,-1,12,22]
    print(selection_sort(sList))