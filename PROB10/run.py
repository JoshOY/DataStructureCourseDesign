__author__ = 'JoshOY'
import my_sort.bubbleSort as bubbleSort
import my_sort.selectionSort as selectionSort
import my_sort.insertionSort as insertionSort
import my_sort.shellSort as shellSort
import my_sort.quickSort as quickSort
import my_sort.heapSort as heapSort
import my_sort.mergeSort as mergeSort
import my_sort.radixSort as radixSort
import random
import datetime

def print_using_time(starttime, endtime):
    sec = endtime[0] - starttime[0]
    if sec < 0:
        sec += 60
    msec = endtime[1] - starttime[1]
    if msec < 0:
        msec += 1000
        sec -= 1
    print "Time used: " + str(sec) + "." + (str(msec) if msec >= 100 else '0' + str(msec)) + " second(s)."

#initialize the list
listnum = raw_input("Input how many random numbers you want to sort[Better less than 10000 :) ]: ")
l = []
try:
    for i in range(int(listnum)):
        l.append(random.randint(0, 1000))
except:
    print "Please input a integer!"
    exit(1)

#Bubble sort
print "Now using bubble sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(bubbleSort.bubble_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Selection sort
print "Now using selection sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(selectionSort.selection_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Insertion sort
print "Now using insertion sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(insertionSort.insertion_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Shell sort
print "Now using Shell sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(shellSort.shell_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Quick sort
print "Now using quick sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
_ = quickSort.quick_sort(l)
print "Taking steps: " + str(quickSort.qsort_step)
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Heap sort
print "Now using heap sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(heapSort.heap_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Merge sort
print "Now using merge sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
_ = mergeSort.merge_sort(l)
print "Taking steps: " + str(mergeSort.merge_step)
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""

#Radix sort
print "Now using radix sort..."
starttime = (datetime.datetime.now().second, datetime.datetime.now().microsecond/ 1000)
print "Taking steps: " + str(radixSort.radix_sort(l)[1])
endtime = (datetime.datetime.now().second, datetime.datetime.now().microsecond / 1000)
print_using_time(starttime, endtime)
print ""
