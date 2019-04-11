#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 给定一个排好序的数组，以及一个数字，求该数字在数组里面的任意一个可能位置。时间复杂度要求O(log(n))
int find_pos(const vector<int>& input_vec, int target, int lo, int hi) {
    if (lo > hi) return -1;

    int mid = 0;
    int cur = 0;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        cur = input_vec[mid];
        if (cur == target) return mid;
        if (cur > target) hi = mid - 1;
        if (cur < target) lo = mid + 1;
    }

    return -1;
}

// 给定一个排好序的数组，以及一个数字，求该数字在数组里面的下标的范围。时间复杂度要求O(log(n))
void find_range(const vector<int>& input_vec, int target, vector<int>& result) {

    int size = input_vec.size();
    if (size == 0) return;

    int lo = 0;
    int hi = size - 1;

    int pos = find_pos(input_vec, target, lo, hi);
    if (pos == -1) return;

    int left_lo = lo;
    int left_hi = pos;
    int start = pos;
    int candidate = start;
    while (left_lo < left_hi) {
        candidate = find_pos(input_vec, target, left_lo, left_hi);
        if (candidate == -1) break;
        start = candidate;
        left_hi = candidate - 1;
    }

    int right_lo = pos + 1;
    int right_hi = hi;
    int end = pos;
    candidate = end;
    while (right_lo < right_hi) {
        candidate = find_pos(input_vec, target, right_lo, right_hi);
        if (candidate == -1) break;
        end = candidate;
        right_lo = candidate + 1;
    }

    result[0] = start;
    result[1] = end;
    return;

}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<int> vec = {1, 2, 3, 3, 3, 4, 5};
    vector<int> result = {-1, -1};
    int target = 5;
    find_range(vec, target, result);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}
