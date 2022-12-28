#include <iostream> 
#include <pthread.h> 
#include <time.h>
#define MAX 10  // number of elements in array 
#define THREAD_MAX 4 // number of threads
using namespace std;  // array of size MAX 
int array[MAX]; int part = 0;  // merge function for merging two parts 
void merge(int low, int mid, int high) 
{ 	
int* left = new int[mid - low + 1]; 	
int* right = new int[high - mid];  	// n1 is size of left part and n2 is size 	// of right part 	
int p1 = mid - low + 1, p2 = high - mid, i, j;  	// storing values in left part 	
for (i = 0; i < p1; i++) 		
left[i] = array[i + low];  	// storing values in right part 	
for (i = 0; i < p2; i++) 		
right[i] = array[i + mid + 1];  	
int k = low; 	
i = j = 0;  	// merge left and right in ascending order 	
while (i < p1 && j < p2) 
{
 		if (left[i] <= right[j]) 			
 		array[k++] = left[i++]; 		
 		else 			
 		array[k++] = right[j++]; 	
 		}  	// insert remaining values from left 	
 		while (i < p1) 
 		{ 		
 		array[k++] = left[i++]; 	
 		}  	// insert remaining values from right 	
 		while (j < p2) 
 		{ 		
 		array[k++] = right[j++]; 	
 		} 
 		}  // merge sort function 
 		void merge_sort(int low, int high) 
 		{ 	// calculating mid point of array 	
 		int mid = low + (high - low) / 2; 	
 		if (low < high) 
 		{  		// calling first half 		
 		merge_sort(low, mid);  		// calling second half 		
 		merge_sort(mid + 1, high);  		// merging the two halves 		
 		merge(low, mid, high); 	
 		} 
 		}  // thread function for multi-threading 
 		void* merge_sort(void* arg) 
 		{ 	// which part out of 4 parts 	
 		int thread_part = part++;  	// calculating low and high 	
 		int low = thread_part * (MAX / 4); 	
 		int high = (thread_part + 1) * (MAX / 4) - 1;  	// evaluating mid point 	
 		int mid = low + (high - low) / 2; 	
 		if (low < high) 
 		{ 		
 		merge_sort(low, mid); 		
 		merge_sort(mid + 1, high); 		
 		merge(low, mid, high); 	
 		} 
 		} 
 	        int main()                                        // Driver Code 
 		{
 		int n=10;
 		cout<<"(Mimmum 10 values stored in the Array)\n";
 		for (int i = 0; i <n; i++)
 		{ 		
 		cout<<"Enter the value "<<i+1<<" in the array\n";
 		cin>>array[i];  
 		} 	
 		clock_t c1, c2;  	
 		c1 = clock(); 	
 		pthread_t threads[THREAD_MAX];  	         // creating 4 threads 	
 		for (int i = 0; i < THREAD_MAX; i++) 		
 		pthread_create(&threads[i], NULL, merge_sort,(void*)NULL);  	// joining all  threads 	
 		for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);  	// merging the final 4 parts 	
 		merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1); 	
 		merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1); 	
 		merge(0, (MAX - 1)/2, MAX - 1);  	
 		c2 = clock();  	// displaying sorted array 	
 		cout << "Sorted array: "; 	
 		for (int i = 0; i < MAX; i++) 		
 		cout << array[i] << " ";  	// time taken by merge sort in seconds 	
 		cout << "Time taken: " << (c2 - c1) /(double)CLOCKS_PER_SEC << endl;  
 		return 0;	 
 		}
