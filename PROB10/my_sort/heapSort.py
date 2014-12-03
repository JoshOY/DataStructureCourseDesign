import copy

def heap_sort(sorting_list):
    step = 0
    ls = copy.deepcopy(sorting_list)

    def sift_down(start, end, step):
        root = start
        while True:
            child = 2 * root + 1
            if child > end:
                break
            if child + 1 <= end and ls[child] < ls[child+1]:
                child += 1
            if ls[root] < ls[child]:
                step += 1
                (ls[root], ls[child]) = (ls[child], ls[root])
                root = child
            else:
                break

    #create heap
    for start in xrange((len(ls)-2)/2, -1, -1):
        sift_down(start, len(ls) - 1, step)

    #sort
    for end in xrange(len(ls)-1, 0, -1):
        (ls[0], ls[end]) = (ls[end], ls[0])
        step += 1
        sift_down(0, end-1, step)
    return (ls, step)

if __name__ == "__main__":
    sList=[ 13, 14, 94, 33, 82, 25, 59, 94, 65, 23, 45, 27, 73, 25, 39, 10 ]
    print(heap_sort(sList))