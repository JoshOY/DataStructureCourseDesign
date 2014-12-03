import copy

def bubble_sort(sorting_list):
    step = 0
    ls = copy.deepcopy(sorting_list)
    list_length = len(ls)
    while list_length > 0:
        for i in range(list_length - 1):
            if ls[i+1] < ls[i]:
                (ls[i], ls[i+1]) = (ls[i+1], ls[i])
                step += 1
        list_length -= 1
    return (ls, step)

if __name__ == "__main__":
    sList=[3,4,1,2,5,8,0,-1,12,22]
    print(bubble_sort(sList))