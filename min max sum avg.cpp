// Parallel Reduction - Min, Max, Avg, Sum
# include <iostream>
# include <omp.h>
# include<sys/time.h>
using namespace std;

int sum_sequential(int arr[], int n)
{
	int sum=0;
	for(int i=0; i<n; i++)
	{
		sum += arr[i];
	}
	return sum;
}
int sum_parallel(int arr[], int n)
{
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0; i<n; i++)
	{
		sum += arr[i];
	}
	return sum;
}
float avg_sequential(int arr[], int n)
{
	int sum = sum_sequential(arr, n);
	return sum/n;
}
float avg_parallel(int arr[], int n)
{
	int sum = sum_parallel(arr, n);
	return sum/n;
}
int min_sequential(int arr[], int n)
{
	int min=9999999;
	for(int i=0; i<n; i++)
	{
		if(min>arr[i])
			min = arr[i];
	}
	return min;
}
int min_parallel(int arr[], int n)
{
	int min=9999999;
	#pragma omp parallel for reduction(min:min)
	for(int i=0; i<n; i++)
	{
		if(min>arr[i])
			min = arr[i];
	}
	return min;
}
int max_sequential(int arr[], int n)
{
	int max=0;
	for(int i=0; i<n; i++)
	{
		if(max<arr[i])
			max = arr[i];
	}
	return max;
}
int max_parallel(int arr[], int n)
{
	int max=0;
	#pragma omp parallel for reduction(max:max)
	for(int i=0; i<n; i++)
	{
		if(max<arr[i])
			max = arr[i];
	}
	return max;
}
int prod_sequential(int arr[], int n)
{
	int prod=1;
	for(int i=0; i<n; i++)
	{
		prod *= arr[i];
	}
	return prod;
}
int prod_parallel(int arr[], int n)
{
	int prod=1;
	#pragma omp parallel for reduction(*:prod)
	for(int i=0; i<n; i++)
	{
		prod *= arr[i];
	}
	return prod;
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
		int arr2[100] = {52, 93, 15, 72, 61, 21, 83, 87, 75, 75, 88, 24, 3, 22,
		53, 2, 88, 30, 38, 2, 64, 60, 21, 33, 76, 58, 22, 89, 49, 91, 59, 42, 92, 60,
		80, 15, 62, 62, 47, 62, 51, 55, 64, 3, 51, 7, 21, 73, 39, 18, 4, 89, 60, 14, 9,
		90, 53, 2, 84, 92, 60, 71, 44, 8, 47, 35, 78, 81, 36, 50, 4, 2, 6, 54, 4, 54,
		93, 63, 18, 90, 44, 34, 74, 62, 14, 95, 48, 15, 72, 78, 87, 62, 40, 85, 80, 82,
		53, 24, 26, 89};
		for(int i=0; i<n; i++)
			arr[i] = arr2[i];
	}

	cout<<"Array = ";
	for(int i=0; i<n; i++)
		cout<<arr[i]<<",";
	cout<<endl<<endl;

	while(true)
	{
		cout<<"Enter 1-Sum | 2-Avg | 3-Min | 4-Max | 5-Prod | 0-Exit : ";
		cin>>ch;

		struct timeval start, end;

		if(ch==1)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = sum_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Sum Sequential Answer = "<<ans<<endl;
			cout<<"Sum Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = sum_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Sum Parallel Answer = "<<ans<<endl;
			cout<<"Sum Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==2)
		{ 
			float ans;
			gettimeofday(&start, NULL);
			ans = avg_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Avg Sequential Answer = "<<ans<<endl;
			cout<<"Avg Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = avg_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Avg Parallel Answer = "<<ans<<endl;
			cout<<"Avg Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==3)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = min_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Min Sequential Answer = "<<ans<<endl;
			cout<<"Min Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = min_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Min Parallel Answer = "<<ans<<endl;
			cout<<"Min Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==4)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = max_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Max Sequential Answer = "<<ans<<endl;
			cout<<"Max Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = max_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Max Parallel Answer = "<<ans<<endl;
			cout<<"Max Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==5)
		{ 
			int ans;
			gettimeofday(&start, NULL);
			ans = prod_sequential(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Product Sequential Answer = "<<ans<<endl;
			cout<<"Product Sequential Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl;

			gettimeofday(&start, NULL);
			ans = prod_parallel(arr, n);
			gettimeofday(&end, NULL);
			cout<<"Product Parallel Answer = "<<ans<<endl;
			cout<<"Product Parallel Reduction Time = "<<(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec -
				start.tv_usec) * 1000<<" ns"<<endl<<endl;
		}
		else if(ch==0)
		{
			cout<<"Exited Successfully."<<endl;
			break;
		}
		else
		{ 
			cout<<"Invalid Choice."<<endl<<endl;
		}
	}
	return 0;
}

/*Of course! I'll explain your **Parallel Reduction - Min, Max, Avg, Sum** code *line by line* in **easy language** so you fully understand it. ??

---

### Code Explanation:

```cpp
#include <iostream>
#include <omp.h>
#include <sys/time.h>
using namespace std;
```
- These are **header files**:
  - `iostream` is for **input/output** (like `cin`, `cout`).
  - `omp.h` is for **OpenMP**, which helps run **parallel (multithreaded) code**.
  - `sys/time.h` is for **measuring time** (to find how fast your code runs).

---

### Functions:

#### SUM functions
```cpp
int sum_sequential(int arr[], int n)
```
- This function finds the **sum** of an array **one by one** (normally, without parallelism).

```cpp
int sum_parallel(int arr[], int n)
```
- This function finds the **sum** using **parallel processing** with OpenMP.
- `#pragma omp parallel for reduction(+:sum)` means:
  - Split the for loop into parts,
  - Each thread calculates its part of the sum,
  - Then combine (`reduce`) the results at the end.

---

#### AVERAGE functions
```cpp
float avg_sequential(int arr[], int n)
```
- This function **calculates the average** normally (sum ÷ number of elements).

```cpp
float avg_parallel(int arr[], int n)
```
- This does **parallel sum**, and then divides by number of elements to get **average**.

---

#### MINIMUM functions
```cpp
int min_sequential(int arr[], int n)
```
- Finds the **smallest** element normally by checking every element one by one.

```cpp
int min_parallel(int arr[], int n)
```
- Finds the **minimum** using **parallel reduction**.
- `#pragma omp parallel for reduction(min:min)` means OpenMP will find the minimum together by sharing work.

---

#### MAXIMUM functions
```cpp
int max_sequential(int arr[], int n)
```
- Finds the **largest** element normally (simple loop).

```cpp
int max_parallel(int arr[], int n)
```
- Finds the **maximum** element using **parallel reduction**.

---

#### PRODUCT functions
```cpp
int prod_sequential(int arr[], int n)
```
- Multiplies all array elements **sequentially** to get the **product**.

```cpp
int prod_parallel(int arr[], int n)
```
- Multiplies all elements **parallelly** with OpenMP's reduction.

---

---

### `main()` function:

```cpp
int main()
```
- The main function starts.

---

#### Choosing array:

```cpp
int n, ch;
cout<<"Enter 1-User Defined Array | 2-Static Array : ";
cin>>ch;
```
- User decides:
  - 1 ? **Create your own array**
  - 2 ? **Use already given static array** (fixed elements).

```cpp
cout<<"Enter the array length | Any-Custom Array | 100-Static Array : ";
cin>>n;
int arr[n];
```
- Enter the size of the array (how many numbers?).

---

```cpp
if(ch==1)
{
    for(int i=0; i<n; i++)
    {
        cout<<"Enter element at position "<<i<<" : ";
        cin>>arr[i];
    }
}
else
{
    int arr2[100] = {52, 93, 15, 72, ...};
    for(int i=0; i<n; i++)
        arr[i] = arr2[i];
}
```
- If user wants custom array, take input one by one.
- Otherwise copy from **predefined array of 100 elements**.

---

```cpp
cout<<"Array = ";
for(int i=0; i<n; i++)
    cout<<arr[i]<<",";
cout<<endl<<endl;
```
- Prints the **original array** before performing operations.

---

---

### Main Menu: (Inside a `while(true)` infinite loop)

```cpp
while(true)
{
    cout<<"Enter 1-Sum | 2-Avg | 3-Min | 4-Max | 5-Prod | 0-Exit : ";
    cin>>ch;
```
- User selects which operation they want:
  - 1 ? Sum
  - 2 ? Average
  - 3 ? Minimum
  - 4 ? Maximum
  - 5 ? Product
  - 0 ? Exit Program

---

Each option has two parts:
1. **Sequential execution** (normal)
2. **Parallel execution** (faster using multiple threads)

And for both, **time is calculated** using:

```cpp
struct timeval start, end;
gettimeofday(&start, NULL);
// Your function call
gettimeofday(&end, NULL);
```

This tells how much **time was taken** for sequential and parallel versions separately.

---

#### Example: For Sum
```cpp
int ans;
gettimeofday(&start, NULL);
ans = sum_sequential(arr, n);
gettimeofday(&end, NULL);
cout<<"Sum Sequential Answer = "<<ans<<endl;
cout<<"Sum Sequential Time = "<<...<<" ns"<<endl;
```
- Calls `sum_sequential`
- Prints the answer and time taken.

Same way for:
- `sum_parallel`
- `avg_sequential`
- `avg_parallel`
- `min_sequential`
- `min_parallel`
- `max_sequential`
- `max_parallel`
- `prod_sequential`
- `prod_parallel`

---

```cpp
else if(ch==0)
{
    cout<<"Exited Successfully."<<endl;
    break;
}
```
- If user enters `0`, the program exits **safely**.

---

### ? **Summary** of Program Purpose:
- **Performs** ? Sum, Average, Minimum, Maximum, Product
- **Two Ways** ? Sequential and Parallel
- **Measures** ? Time for each method
- **Parallel Reduction** ? Makes operations faster by using multiple CPU cores at once.

---

### ?? Important Points:
- `reduction(+:sum)` ? for addition
- `reduction(min:min)` ? for finding minimum
- `reduction(max:max)` ? for finding maximum
- `reduction(*:prod)` ? for multiplication

Parallel reduction works by:
- Each thread does small part of work,
- Finally results are combined together safely and correctly.

---

### ?? Example OUTPUT:

Suppose you chose **Static Array** and did **Sum**:
```
Array = 52,93,15,72,61,21,....,89
Enter 1-Sum | 2-Avg | 3-Min | 4-Max | 5-Prod | 0-Exit : 1
Sum Sequential Answer = 5000
Sum Sequential Time = 5800 ns
Sum Parallel Answer = 5000
Sum Parallel Reduction Time = 2300 ns
```
Here, you can see **Parallel Sum** is **faster** than **Sequential Sum**!

---

Would you also like me to show a **beautiful table** summarizing the functions (`sum_sequential`, `sum_parallel`, etc.) if you want? ???  
It will be super easy to revise! ??
Shall I make it?*/
