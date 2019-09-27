#include <stdio.h>

// returns the position of the 1st element in the list to evaluate greater than v (> v)
// (returns n if element is larger than the largest element in list)
int upper_bound(int a[], int n, int v) {// n = size of the array, v = value to be found
    int l = 0, h = n, m; 
    // h = n, not n - 1 so the program can return n if v is greater than the greatest element
    while(l < h) {
        m = l + (h - l)/2;
        if (a[m] <= v) l = m + 1;
        else h = m;
    }
    return l;
}

// returns the position of the 1st element in the list to evaluate not less than v (>= v)
// (returns n if element is larger than the largest element in list)
int lower_bound(int a[], int n, int v) {// n = size of the array, v = value to be found
    int l = 0, h = n, m; 
    // h = n, not n - 1 so the program can return n if v is greater than the greatest element
    while(l < h) {
        m = l + (h - l)/2;
        if (a[m] >= v) h = m;
        else l = m + 1;
    }
    return l;
}

// returns the position of the last element in the list to evaluate not less than v (>= v)
// (return -1 if element is smaller than the smallest element in list) 
int rev_lower_bound(int a[], int n, int v) {// n = size of the array, v = value to be found
    int l = -1, h = n-1, m;
    // l = -1, not 0 so the program can return -1 if v is smaller than the smallest element
    while (l < h) {
        m = l + (h - l + 1)/2; // ceiling division
        if (a[m] <= v) l = m;
        else h = m - 1;
    }
    return l;
}

// upper_bound - lower_bound for a specific v in a sorted list gives the frequency of v in the list

int main() {
    int n;
    scanf("%d", &n);
    int a[n]; // a sorted list
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    int v;
    scanf("%d", &v);
    printf("%d %d %d\n", lower_bound(a, n, v), upper_bound(a, n, v), rev_lower_bound(a, n, v));
    return 0;
}
