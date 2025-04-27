// Parallel Bubble and Merge Sort 

#include <iostream>
#define _BSD_SOURCE
#include <sys/time.h>
#include <omp.h>

using namespace std;

void bubble_sort_sequential(int arr[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubble_sort_parallel(int arr[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        #pragma omp parallel for
        for(int j=0; j<n-i-1; j++)
        {
            #pragma omp critical
            {
                if(arr[j] > arr[j+1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
}

void merge(int arr[], int l, int mid, int r)
{
    int n1 = mid - l + 1, n2 = r - mid;
    int left[n1];
    int right[n2];
    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[mid + i + 1];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

void merge_sort_sequential(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort_sequential(arr, left, mid);
        merge_sort_sequential(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort_parallel(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        #pragma omp parallel
        {merge_sort_parallel(arr, left, mid);}
        #pragma omp parallel
        {merge_sort_parallel(arr, mid+1, right);}
        #pragma omp critical
        {merge(arr, left, mid, right);}
    }
}

int main()
{

    int n,ch;
    cout<<"Enter 1-User Defined Array | 2-Static Array : ";
    cin>>ch;
    
    cout<<"Enter the array length | Any-Custom Array | 100-Static Array : ";
    cin>>n;
    int arr[n];
    
    if(ch==1)
    {
    	for(int i=0; i<n; i++)
    	{
        	cout<<"Enter element at position "<<i<<" : ";
        	cin>>arr[i];
    	}
    	cout<<endl<<endl;
    }
    else
    {
    	int arr2[100] = {52, 93, 15, 72, 61, 21, 83, 87, 75, 75, 88, 24, 3, 22, 53, 2, 88, 30, 38, 2, 64, 60, 21, 33, 76, 58, 22, 89, 49, 91, 59, 42, 92, 60, 80, 15, 62, 62, 47, 62, 51, 55, 64, 3, 51, 7, 21, 73, 39, 18, 4, 89, 60, 14, 9, 90, 53, 2, 84, 92, 60, 71, 44, 8, 47, 35, 78, 81, 36, 50, 4, 2, 6, 54, 4, 54, 93, 63, 18, 90, 44, 34, 74, 62, 14, 95, 48, 15, 72, 78, 87, 62, 40, 85, 80, 82, 53, 24, 26, 89};
    	for(int i=0; i<n; i++)
    		arr[i] = arr2[i];
    }

    cout<<"Unsorted Array = ";
    for(int i=0; i<n; i++)
        cout<<arr[i]<<",";
    cout<<endl<<endl;

    cout<<"Enter 1-Bubble,Sequential | 2-Bubble,Parallel | 3-Merge,Sequential | 4-Merge,Parallel : ";
    cin>>ch;
    
    struct timeval start, end;
    
    if(ch==1)
    {
    	gettimeofday(&start, NULL);
    	bubble_sort_sequential(arr, n);
    	cout<<"Bubble Sort Sequential."<<endl;
    }
    else if(ch==2)
    {
    	gettimeofday(&start, NULL);
    	bubble_sort_parallel(arr, n);
    	cout<<"Bubble Sort Parallel."<<endl;
    }
    else if(ch==3)
    {
    	gettimeofday(&start, NULL);
    	merge_sort_sequential(arr, 0, n-1);
    	cout<<"Merge Sort Sequential."<<endl;
    }
    else if(ch==4)
    {
    	gettimeofday(&start, NULL);
    	merge_sort_parallel(arr, 0, n-1);
    	cout<<"Merge Sort Parallel."<<endl;
    }
    else
    {
    	cout<<"Invalid Choice."<<endl<<endl;
    	return 0;
    }
        
    gettimeofday(&end, NULL);
    cout<<"Answer = ";
    for(int i=0; i<n; i++)
        cout<<arr[i]<<",";
    cout<<endl<<endl;
    cout<<"Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec - start.tv_usec) * 1000<<" ns"<<endl;  
    cout<<endl;

    return 0;
}


/*
Of course! ??  
Let’s go **line by line** in **very easy language** so you understand clearly:

---

```cpp
// Parallel Bubble and Merge Sort
```
- This is a comment. It tells us the program is about sorting an array using **Bubble Sort** and **Merge Sort**, both **sequentially** and **in parallel**.

---
```cpp
#include <iostream>
#define _BSD_SOURCE
#include <sys/time.h>
#include <omp.h>
```
- We include **iostream** to use `cin` and `cout` for input and output.
- `_BSD_SOURCE` is defined to enable some advanced system features (needed for accurate time measurement sometimes).
- `sys/time.h` is included for using `gettimeofday()` to measure the time taken.
- `omp.h` is for **OpenMP**, which allows **parallel programming**.

---
```cpp
using namespace std;
```
- This saves us from writing `std::cout`, `std::cin` again and again.

---
```cpp
void bubble_sort_sequential(int arr[], int n)
```
- This defines a **function** that sorts an array **sequentially** using **Bubble Sort**.

---
```cpp
for(int i=0; i<n-1; i++)
```
- Outer loop runs `n-1` times to ensure complete sorting.

---
```cpp
for(int j=0; j<n-i-1; j++)
```
- Inner loop compares adjacent elements.

---
```cpp
if(arr[j] > arr[j+1])
```
- If the element is bigger than the next one, swap them.

---
```cpp
int temp = arr[j];
arr[j] = arr[j+1];
arr[j+1] = temp;
```
- **Swapping** two elements using a temporary variable.

---
Similarly, now:
```cpp
void bubble_sort_parallel(int arr[], int n)
```
- This defines a **parallel** version of Bubble Sort.

---
```cpp
#pragma omp parallel for
```
- This line tells OpenMP to **divide** the inner `for` loop work across multiple threads (parallelize it).

---
```cpp
#pragma omp critical
```
- Because swapping two elements **affects shared memory**, `critical` is used so that **only one thread swaps at a time** to avoid errors.

---
```cpp
void merge(int arr[], int l, int mid, int r)
```
- This function **merges** two **sorted subarrays** back into one sorted array.

---
Inside merge:
- `left[]` and `right[]` are two temporary arrays.
- We **copy** elements into left and right arrays.
- We then **merge** them back into the original array `arr[]` by comparing elements one by one.

---
```cpp
void merge_sort_sequential(int arr[], int left, int right)
```
- This is **Sequential Merge Sort**.
- If `left < right`:
  - Find the middle.
  - Sort **left half** and **right half** **recursively**.
  - Then merge them.

---
```cpp
void merge_sort_parallel(int arr[], int left, int right)
```
- This is **Parallel Merge Sort**.
- It uses **OpenMP** to divide and conquer the left and right halves **in parallel**.

---
Inside parallel merge sort:
```cpp
#pragma omp parallel
```
- It spawns new threads to work **simultaneously** on left and right parts.

```cpp
#pragma omp critical
```
- Again, merging must be done **safely** so that no two threads disturb the data.

---
Now the **main() function**:

```cpp
int n,ch;
cout<<"Enter 1-User Defined Array | 2-Static Array : ";
cin>>ch;
```
- Ask user if they want to **enter their own array** or **use a pre-made static array**.

---
```cpp
cout<<"Enter the array length | Any-Custom Array | 100-Static Array : ";
cin>>n;
int arr[n];
```
- Ask for the **size of array** and create an array `arr[]` of size `n`.

---
Then:
- If user wants a **user-defined array**, ask them to input each element.
- Else, use a **predefined array** `arr2` and **copy** its values into `arr[]`.

---
```cpp
cout<<"Unsorted Array = ";
for(int i=0; i<n; i++)
    cout<<arr[i]<<",";
cout<<endl<<endl;
```
- Print the **unsorted array**.

---
```cpp
cout<<"Enter 1-Bubble,Sequential | 2-Bubble,Parallel | 3-Merge,Sequential | 4-Merge,Parallel : ";
cin>>ch;
```
- Ask user which **sorting method** they want to test:
  - 1 for sequential Bubble Sort
  - 2 for parallel Bubble Sort
  - 3 for sequential Merge Sort
  - 4 for parallel Merge Sort

---
```cpp
struct timeval start, end;
```
- Create two time variables to **record time**.

---
Depending on user choice:

```cpp
gettimeofday(&start, NULL);
bubble_sort_sequential(arr, n);
// or any chosen sorting function
gettimeofday(&end, NULL);
```
- Record the **time before** and **after** sorting to calculate how long sorting took.

---
```cpp
cout<<"Answer = ";
for(int i=0; i<n; i++)
    cout<<arr[i]<<",";
cout<<endl<<endl;
```
- Print the **sorted array**.

---
```cpp
cout<<"Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec - start.tv_usec) * 1000<<" ns"<<endl;  
```
- Calculate and print the **time taken** to sort the array **in nanoseconds**.

---
```cpp
return 0;
```
- End the program successfully.

---

# ? Summary:
- You can **sort arrays** using **Bubble Sort** or **Merge Sort**.
- You can do it either **normally** (sequential) or using **multiple threads** (parallel).
- It also measures the **time taken** so you can **compare speed** of sequential vs parallel.

---

Would you like me to also make a small *visual flowchart* ?? or a *simple example* of how parallel bubble/merge actually looks? ??  
It'll help you understand even better! ??
*/
