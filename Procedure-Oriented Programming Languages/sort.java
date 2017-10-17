import java.util.Scanner;
import java.util.Arrays;

public class sort{ public static void main(String[] args) {
		int[] numbers1 = new int[30];
		int[] numbers2 = new int[30];
		int numbers1_len = 0;
		while (numbers1_len < 30)
		{
			System.out.println("Enter numbers for first array a letter to stop: ");
    	Scanner sc = new Scanner(System.in);
			try {
				int elt = sc.nextInt();
				numbers1[numbers1_len] = elt;
				numbers1_len++;
			}
			catch (Exception ex)
			{
				break;
			}
		}
		System.out.println("First Array");
		int j = 0;
		while(j < numbers1_len)
		{
			System.out.print(numbers1[j] + ", ");
			j++;
		}
		System.out.println("\n");
	  int numbers2_len = 0;
		while (numbers2_len < 30)
		{
			System.out.println("Enter numbers for second array a letter to stop: ");
    	Scanner sc = new Scanner(System.in);
    	// Put arg in guess
			try {
				int elt = sc.nextInt();
				numbers2[numbers2_len] = elt;
				numbers2_len++;
			}
			catch (Exception ex)
			{
				break;
			}
		}
		System.out.println("Second Array");
		j = 0;
		while(j < numbers2_len)
		{
			System.out.print(numbers2[j] + ", ");
			j++;
		}
		System.out.println("\n");

		numbers1 = BubbleSort(numbers1, numbers1_len);
		j = 0;
		System.out.println("First Array Sorted");
		while(j < numbers1_len)
		{
			System.out.print(numbers1[j] + ", ");
			j++;
		}
		System.out.println("\n");

		numbers2 = SelectionSort(numbers2, numbers2_len);
		j = 0;
		System.out.println("Second Array Sorted");
		while(j < numbers2_len)
		{
			System.out.print(numbers2[j] + ", ");
			j++;
		}
		System.out.println("\n");

		int[] merged = new int[30];
		merged = MergeSort(numbers1, numbers2, numbers1_len, numbers2_len);
		j = 0;
		System.out.println("Merged Array Sorted");
		int merged_len = numbers1_len + numbers2_len;
		while(j < merged_len)
		{
			System.out.print(merged[j] + ", ");
			j++;
		}
		System.out.println("\n");
		System.out.println("Binary Array Search");
		System.out.println(BinarySearch(merged, merged_len));
		System.out.println("Linear Array Search");
		System.out.println(LinearSearch(merged, merged_len));
  }

	public static int[] BubbleSort(int[] numbers1, int length)
	{
		boolean swapped = true;
		while(swapped) {
			swapped = false;
			for(int i = 1; i < length; i++) {
				int temp = 0;
				if(numbers1[i-1] > numbers1[i]) {
					temp = numbers1[i-1];
					numbers1[i-1] = numbers1[i];
					numbers1[i] = temp;
					swapped = true;
				}
			}
		}
		return numbers1;
	}

	public static int[] SelectionSort(int[] numbers2, int length)
	{
		for (int i = 0; i < length; i++)
		{
			int index = i;
			for (int j = i + 1; j < length; j++)
			{
				if (numbers2[j] < numbers2[index])
					index = j;
			}
			int small = numbers2[index];
			numbers2[index] = numbers2[i];
			numbers2[i] = small;
		}
		return numbers2;
	}

	public static int[] MergeSort(int[] numbers1, int[] numbers2, int num1_len, int num2_len)
	{
		int firstIndex = 0;
		int secondIndex = 0;
		int mergedIndex = 0;
		int[] merged = new int[30];

		while (firstIndex < num1_len && secondIndex < num2_len)
		{
			if (numbers1[firstIndex] < numbers2[secondIndex])
			{
				merged[mergedIndex] = numbers1[firstIndex];
				firstIndex++;
			}
			else
			{
				merged[mergedIndex] = numbers2[secondIndex];
				secondIndex++;
			}
			mergedIndex++;
		}

		while (firstIndex <= num1_len)
		{
			merged[mergedIndex] = numbers1[firstIndex];
			firstIndex++;
			mergedIndex++;
		}
		while (secondIndex <= num2_len)
		{
			merged[mergedIndex] = numbers2[secondIndex];
			secondIndex++;
			mergedIndex++;
		}
		return merged;
	}

	public static int BinarySearch(int[] merged, int merged_len)
	{
			System.out.println("Enter number you would like to search for: ");
    	Scanner sc = new Scanner(System.in);
			try {
				int key = sc.nextInt();
				int low = 0;
				int max = merged_len;

				while(max >= low) {
					int middle = (low + max) / 2;
					if(merged[middle] == key)
						return middle;
					if(merged[middle] < key)
						low = middle + 1;
					if(merged[middle] > key)
						max = middle - 1;
				}
				return -1;
			}
			catch (Exception ex)
			{
				return -1;
			}
	}

	public static int LinearSearch(int[] merged, int merged_len)
	{
		System.out.println("Enter number you would like to search for: ");
		Scanner sc = new Scanner(System.in);
		try {
			int key = sc.nextInt();
			int low = 0;
			int max = merged_len;

			while(low <= max && key != merged[low]) {
				low++;
			}
			return low;
		}
		catch (Exception ex)
		{
			return -1;
		}
	}
}

