import string
numbers1 = []
numbers2 = []

def BubbleSort (numbers1, length):
	swapped = True;
	while(swapped):
		swapped = False;
		for i in xrange(1, length):
			temp = 0
			if(numbers1[i-1] > numbers1[i]):
				temp = numbers1[i-1]
				numbers1[i-1] = numbers1[i]
				numbers1[i] = temp
				swapped = True
	return numbers1

def SelectionSort(numbers2):
	for i in range(len(numbers2)):
		min_val = min(numbers2[i:])
		min_index = numbers2[i:].index(min_val)
		numbers2[i+min_index] = numbers2[i]
		numbers2[i] = min_val
	return numbers2

def MergeSort(numbers1, numbers2):
	firstIndex = 0
	secondIndex = 0
	merged = []

	while (firstIndex < len(numbers1) and secondIndex < len(numbers2)):
		if (numbers1[firstIndex] < numbers2[secondIndex]):
			merged.append(numbers1[firstIndex])
			firstIndex = firstIndex + 1
		else:
			merged.append(numbers2[secondIndex])
			secondIndex = secondIndex + 1
	while(firstIndex < len(numbers1)):
		merged.append(numbers1[firstIndex])
		firstIndex = firstIndex + 1
	while(secondIndex < len(numbers2)):
		merged.append(numbers2[secondIndex])
		secondIndex = secondIndex + 1
	return merged

def BinarySearch(merged):
	sc = input("Enter number you would like to search for: ")

	key = sc
	low = 0
	max_val = len(merged)

	while(max_val >= low):
		middle = (low + max_val) / 2
		if(merged[middle] == key):
			return merged.index(key)
		if(merged[middle] < key):
			low = middle + 1
		if(merged[middle] > key):
			max_val = middle - 1
	return -1

def LinearSearch(merged):
	sc = input("Enter a number you would like to search for: ")

	count = 0
	notFound = True
	while (count < len(merged) and notFound == True):
		if merged[count] == sc:
			return count
		count = count + 1

numbers1_len = 1
while (numbers1_len < 8):
	sc = input("Enter numbers for first array a letter to stop: ")
	if(sc.isalpha())
		break;
	numbers1.insert(numbers1_len,sc)
	numbers1_len = numbers1_len + 1

print("First Array")
print(numbers1)
print("\n")

numbers2_len = 1
while (numbers2_len < 7):
	sc = input("Enter numbers for second array a letter to stop: ")
	if(sc.isalpha())
		break;
	numbers2.insert(numbers2_len,sc)
	numbers2_len = numbers2_len + 1

print("Second Array")
print(numbers2)
print("\n")

numbers1 = BubbleSort(numbers1, numbers1_len-1)
j = 0
print("First Array Sorted");
print(numbers1)
print("\n")

numbers2 = SelectionSort(numbers2)
j = 0
print("Second Array Sorted")
print(numbers2)
print("\n")

merged = [];
merged = MergeSort(numbers1, numbers2);
print("Merged Array Sorted")
print(merged)

print("\n")
print("Binary Array Search")
print(BinarySearch(merged))
print("Linear Array Search")
print(LinearSearch(merged))
