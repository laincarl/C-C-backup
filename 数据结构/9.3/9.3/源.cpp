#include<iostream>
#include"compare.h"

using namespace std;



/*template <class Elem, class Comp>
int findK(Elem A[], int i, int j, Elem K) {
	if (j <= i) 
		return i; // Don¡¯t sort 0 or 1 Elem
	int pivotindex = findpivot(A, i, j);
	swap(A, pivotindex, j); // Put pivot at end
	// k will be the first position in the right subarray
	int k = partition<Elem, Comp>(A, i - 1, j, A[j]);
	swap(A, k, j); // Put pivot in place
	if (Comp.eq(A[k], K)) 
		return k;
	if (Comp.gt(A[k], K))
		return findK<Elem, Comp>(A, i, k - 1, K);
	else 
		return findK<Elem, Comp>(A, k + 1, j, K);
}*/
template <typename E, typename Comp>
void qsort(E A[], int i, int j) { // Quicksort
	if (j <= i) return; // Don't sort 0 or 1 element
	int pivotindex = findpivot(A, i, j);
	swap(A,pivotindex, j);    // Put pivot at end
	// k will be the first position in the right subarray
	int k = partition<E, Comp>(A, i - 1, j, A[j]);
	swap(A,k,j);             // Put pivot in place
	qsort<E, Comp>(A, i, k - 1);
	qsort<E, Comp>(A, k + 1, j);
}
template <typename E>
inline int findpivot(E A[], int i, int j)
{
	return (i + j) / 2;
}
template <typename E, typename Comp>
inline int partition(E A[], int l, int r, E& pivot) {
	do {             // Move the bounds inward until they meet
		while (Comp::prior(A[++l], pivot));  // Move l right and
		while ((l < r) && Comp::prior(pivot, A[--r])); // r left
		swap(A, l, r);              // Swap out-of-place values
	} while (l < r);              // Stop when they cross
	return l;      // Return first position in right partition
}
int main()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, i;
	qsort<int, int>(a, 0, 9);
	for (i = 0; i < 10; i++)
		cout << a[i] << " ";
	return 0;
}