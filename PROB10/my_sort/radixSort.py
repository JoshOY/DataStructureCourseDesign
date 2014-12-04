import copy

def __getMaxBit(sorting_list):
    d = 1
    p = 10
    for i in sorting_list:
        while i > p:
            d += 1
            p *= 10
    return d

def radix_sort(sorting_list):
    step = 0
    d = __getMaxBit(sorting_list)
    ls = copy.deepcopy(sorting_list)
    tmp = [0] * len(ls)
    radix = 1
    for i in range(d):
        count = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        for j in range(len(ls)):
            k = int(ls[j] / radix) % 10
            count[k] += 1
            step += 1
        for j in range(1, 10):
            count[j] += count[j-1]
        for j in xrange(len(ls)-1, -1, -1):
            k = int(ls[j] / radix) % 10
            tmp[count[k] - 1] = ls[j]
            count[k] -= 1
            step += 1
        for j in range(len(ls)):
            ls[j] = tmp[j]
            step += 1
        radix *= 10
    return (ls, step)


if __name__ == "__main__":
    sList=[13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(radix_sort(sList))