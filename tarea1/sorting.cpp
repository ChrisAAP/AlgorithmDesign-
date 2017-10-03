#include <iostream>
//#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>


typedef std::chrono::high_resolution_clock Clock;

using namespace std;
struct Node
{
    int key;
    struct Node *left, *right;
};
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void storeSorted(Node *root, int array[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, array, i);
        array[i++] = root->key;
        storeSorted(root->right, array, i);
    }
}
Node* insert(Node* node, int key)
{
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

void print(int *array, int size)
{
    cout << "array: ";
    for(int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << "\n";
}
int getMax(int array[], int size)
{
	int max = array[0];
	for(int i = 1; i < size; ++i)
		if(array[i] > max) max = array[i];
	return max;
}

void bubbleSort(int array[], int size)
{
    bool flag = false;
    while(!flag)
    {
        flag = false;
        for(int i = 0; i < size-1; i++)
        {
            if(array[i] > array[i + 1])
            {
                swap(array[i],array[i + 1]);
                flag = true;
            }
        }
        if (!flag) break;
        flag = false;
    }
}

void shakerSort(int array[], int size){
    int begin = 0;
    int end = size;
    bool flag = false;
    do
    {
        flag = false;
        for(int i = begin; i < end - 1; ++i)
        {
            if(array[i] > array[i + 1])
            {
                swap(array[i],array[i + 1]);
                flag = true;
            }
        }
        --end;
        if (!flag) break;
        flag = false;
        for(int i = end - 2; i >= begin; --i)
        {
            if(array[i] > array[i + 1])
            {
                swap(array[i],array[i + 1]);
                flag = true;
            }
        }
        ++begin;
    } while(flag);
}
void insertionSort(int array[], int size){
    for(int i = 0; i < size; ++i)
    {
        for(int j = i; j > 0; --j)
        {
            if(array[j] < array[j - 1])
                swap(array[j],array[j-1]);
        }
    }
}
void bucketSort(int array[], int size)
{
int minValue = array[0];
	int maxValue = array[0];

	for (int i = 1; i < size; i++)
	{
		if (array[i] > maxValue)
			maxValue = array[i];
		if (array[i] < minValue)
			minValue = array[i];
	}

	int bucketLength = maxValue - minValue + 1;
	vector<int>* bucket = new vector<int>[bucketLength];

	for (int i = 0; i < bucketLength; i++)
	{
		bucket[i] = vector<int>();
	}

	for (int i = 0; i < size; i++)
	{
		bucket[array[i] - minValue].push_back(array[i]);
	}

	int k = 0;
	for (int i = 0; i < bucketLength; i++)
	{
		int bucketSize = bucket[i].size();

		if (bucketSize > 0)
		{
			for (int j = 0; j < bucketSize; j++)
			{
				array[k] = bucket[i][j];
				k++;
			}
		}
	}
}
void countingSort(int array[], int size)
{
	int maxNumber = getMax(array,size);
 	int countingArray[maxNumber];
 	int outputArray[size];
 	for(int i = 0; i < maxNumber; ++i)
 		countingArray[i] = 0;
 	for(int i = 0; i < size; ++i)
 		++countingArray[array[i]];
 	for(int i = 1; i <= maxNumber; ++i)
 		countingArray[i]+=countingArray[i-1];
 	for(int i = maxNumber; i > 0; --i)
 		countingArray[i] = countingArray[i-1];
 	countingArray[0] = 0; 	
 	for(int i = 0; i < size; ++i)
 	{
 		outputArray[countingArray[array[i]]] = array[i];
 		++countingArray[array[i]];
 	}
 	for(int i = 0; i < size; ++i)
 		array[i] = outputArray[i];
}
void mergeStep(int array[], int lo, int mid, int hi)
{
	int n1 = mid - lo + 1; 
	int n2 = hi - mid;    
	int aux1[n1 + 1];     
	int aux2[n2 + 1];    
	for(int i = 0; i < n1; ++i)
		aux1[i] = array[lo + i];
	aux1[n1] = 214748364;	     
	for(int i = 0; i < n2; ++i)   
		aux2[i] = array[mid + 1 + i];
	aux2[n2] = 214748364;       
	int i = 0, j = 0;
	for(int k = lo; k < hi + 1; ++k)    
	{
		if(aux1[i] < aux2[j])	
		{
			array[k] = aux1[i];
			++i;
		}
		else                         
		{
			array[k] = aux2[j];
			++j;
		}
	}
}
void mergeSort(int array[], int lo, int hi)
{
    if(lo < hi)
    {
        int mid = (lo + hi)/2;
        mergeSort(array, lo, mid);
        mergeSort(array, mid+1, hi);
        mergeStep(array, lo, mid, hi);
    }
    
}

void binaryTree(int array[], int size)
{
    struct Node *root = NULL;
 
    // Construct the BST
    root = insert(root, array[0]);
    for (int i=1; i<size; i++)
        insert(root, array[i]);
 
    // Store inoder traversal of the BST
    // in arr[]
    int i = 0;
    storeSorted(root, array, i);
}
void radixStep(int array[], int size, int exp)
{
	int outputArray[size];
    int i, count[10] = {0};
    for (i = 0; i < size; ++i)
        ++count[(array[i] / exp) % 10];
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = size - 1; i >= 0; --i)
    {
        outputArray[count[ (array[i] / exp) % 10 ] - 1] = array[i];
        --count[(array[i] / exp) % 10];
    }
    for (i = 0; i < size; ++i)
        array[i] = outputArray[i];
}
void radixSort(int array[], int size)
{
    int max = getMax(array, size);
    for (int exp = 1; max/exp > 0; exp *= 10)
        radixStep(array, size, exp);
}
void shellSort(int array[], int size)
{
    for(int gap = size / 2; gap > 0; gap /= 2)
    {
    	for(int i = gap; i < size; ++i)
    	{
    		int temp = array[i];
    		int j;
    		for(j = i; j >= gap && array[j - gap] > temp; j-=gap)
    			array[j] = array[j - gap];
    		array[j] = temp;
    	}
    }
}
void selectionSort(int array[],int size)
{
	for(int i = 0; i < size - 1 ; ++i)
	{
		int minimum = i;
		for(int j = i + 1; j < size; ++j)
		{
			if(array[j] < array[minimum])
				minimum = j;
		}
		if(minimum !=i)
			swap(array[i], array[minimum]);
	}
}
void heapify(int array[], int size, int i)
{
    int largest = i;  
    int left = 2*i + 1;  
    int right = 2*i + 2; 
    if (left < size && array[left] > array[largest])
        largest = left;
    if (right < size && array[right] > array[largest])
        largest = right;
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, size, largest);
    }
}
void heapSort(int array[], int size)
{
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(array, size, i);
    for (int i = size - 1; i >= 0; --i)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int partition(int array[], int lo, int hi)
{
    int pivot = array[hi];
    int i = lo - 1;
    for(int j = lo; j < hi; ++j)
    {
        if(array[j] < pivot)
        {
            ++i;
            swap(array[i], array[j]);
        }
    }
    if(array[hi] < array[i + 1])
        swap(array[i + 1], array[hi]);
    return i + 1; 
}
void quickSort(int array[], int lo, int hi)
{
    if(hi <= lo) return;
    int j = partition(array,lo,hi);
    quickSort(array,lo, j - 1);
    quickSort(array,j + 1, hi);
    
}
int main()
{
	int size = 1000000;
	int x = 0;
	int toInt;
	int array[size];
	string line;
	ifstream numbers("1000000.txt");
	if(numbers.is_open())
	{
		while(getline (numbers, line))
		{
			toInt = stoi(line);
 			array[x] = toInt;
			++x;
		}
		numbers.close();
	}
	else cout << "unable \n";
	//clock_t cl = clock();
	//int correctTime = CLOCKS_PER_SEC/1000;
	auto t1 = Clock::now();
    binaryTree(array,size);
    auto t2 = Clock::now();
    cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count())/1000 << " ms\n";
	//cout << (clock()-cl)/correctTime << "ms" << "\n";
	//print(array,size);
}