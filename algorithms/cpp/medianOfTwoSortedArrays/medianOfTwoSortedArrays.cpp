// Source : https://oj.leetcode.com/problems/median-of-two-sorted-arrays/
// Author : LongquanLiu
// Date   : 2018-04-12

/********************************************************************************** 
* 
* There are two sorted arrays A and B of size m and n respectively. 
* Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*               
**********************************************************************************/

class Solution {
public:
    // Classical binary search algorithm, but slightly different
    // if cannot find the key, return the position where can insert the key
    int binarySearch(vector<int> a, int low, int high, int key){
        while(low <= high){
            int mid = low + (high - low)/2;
            if(a[mid] == key){
                return mid;
            }else if(a[mid] < key){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
        return low;
    }  
   double findMedianSortedArraysHelper(vector<int> A, int m, vector<int> B, int n, int lowA, int highA, int lowB, int highB){
        // Take the A[middle], search its position in B array 
        int mid = lowA + (highA - lowA)/2;
        int pos = binarySearch(B, lowB, highB, A[mid]);
        int num = mid + pos;
        // If the A[middle] in B is B's middle place, then we can have the result
        if(num == (m+n)/2){
            // If two arrays total length is odd, just simply return the A[mid]
            // Why not return the B[pos] instead ? 
            //   suppose A={ 1,3,5 } B={ 2,4 }, then mid=1, pos=1
            //   suppose A={ 3,5 }   B={1,2,4}, then mid=0, pos=2
            //   suppose A={ 1,3,4,5 }   B={2}, then mid=1, pos=1
            // You can see, the `pos` is the place A[mid] can be inserted, so return A[mid]
            if((m+n) % 2 == 1)
                return A[mid]/1.0;
            else {
             // If two arrys total length is even, then we have to find the next one.
                int next = 0;
            // If both `mid` and `pos` are not the first postion.
            // Then, find max(A[mid-1], B[pos-1]). 
            // Because the `mid` is the second middle number, we need to find the first middle number
            // Be careful about the edge case
                if(mid > 0 && pos > 0){
                    next = A[mid - 1] > B[pos - 1] ? A[mid - 1] : B[pos -1];
                }else if(mid > 0){
                    next = A[mid - 1];
                }else if(pos > 0){
                    next = B[pos - 1];
                }
                return (A[mid] + next)/2.0;
            }
        }
        
        // if A[mid] is in the left middle place of the whole two arrays
        //
        //         A(len=16)        B(len=10)
        //     [................] [...........]
        //            ^             ^
        //           mid=7         pos=1
        //
        //  move the `low` pointer to the "middle" position, do next iteration.
        if(num < (m+n)/2){
            lowA = mid + 1;
            lowB = pos;  // this pos is insert positon mean this value larger than A[mid]
            if (highA - lowA > highB - lowB){
                return findMedianSortedArraysHelper(A, m, B, n, lowA, highA, lowB, highB);
            }else{
                return findMedianSortedArraysHelper(B, n, A, m, lowB, highB, lowA, highA);
            }
        }
         // if A[mid] is in the right middle place of the whole two arrays
        if(num > (m+n)/2){
            highA = mid - 1;
            highB = pos - 1; // this pos is insert positon mean this value larger than A[mid] so move before
            if (highA - lowA > highB - lowB){
                return findMedianSortedArraysHelper(A, m, B, n, lowA, highA, lowB, highB);
            }else{
                return findMedianSortedArraysHelper(B, n, A, m, lowB, highB, lowA, highA);
            }
        }
        
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int length1 = nums1.size();
        int length2 = nums2.size();
        // check the edges case
        if(length1 == 0 && length2 == 0)
            return 0.0;
        //if the length of array is odd, return the middle one
        //if the length of array is even, return the average of the middle two numbers
        if(length1 == 0)
            return length2 % 2 == 1 ? nums2[length2/2]/1.0 : (nums2[length2/2 - 1] +nums2[length2/2])/2.0;
        if(length2 == 0)
            return length1 % 2 == 1 ? nums1[length1/2]/1.0 : (nums1[length1/2 - 1] +nums1[length1/2])/2.0;
        //let the longer array be A, and the shoter array be B
        if(length1 > length2){
            return findMedianSortedArraysHelper(nums1, length1, nums2, length2, 0, length1-1, 0, length2-1);
        }else{
            return findMedianSortedArraysHelper(nums2, length2, nums1, length1, 0, length2-1, 0, length1-1);
        }
        
    }
    
};
