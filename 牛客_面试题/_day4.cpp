#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <stack>


/*
 *把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 
 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 
 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 
 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0
 *
 * 旋转之后的数组实际上可以划分成两个有序的子数组：前面子数组的大小都大于后面子数组中的元素
 * 
 * 注意到实际上最小的元素就是两个子数组的分界线。本题目给出的数组一定程度上是排序的，因此我们试着用二分查找法寻找这个最小的元素。
 * 
 * 思路：
 *
 * （1）我们用两个指针left,right分别指向数组的第一个元素和最后一个元素。按照题目的旋转的规则，第一个元素应该是大于最后一个元素的（没有重复的元素）。
 *
 * 但是如果不是旋转，第一个元素肯定小于最后一个元素。
 *
 * （2）找到数组的中间元素。
 *
 * 中间元素大于第一个元素，则中间元素位于前面的递增子数组，此时最小元素位于中间元素的后面。我们可以让第一个指针left指向中间元素。
 *
 * 移动之后，第一个指针仍然位于前面的递增数组中。
 *
 * 中间元素小于第一个元素，则中间元素位于后面的递增子数组，此时最小元素位于中间元素的前面。我们可以让第二个指针right指向中间元素。
 *
 * 移动之后，第二个指针仍然位于后面的递增数组中。
 *
 * 这样可以缩小寻找的范围。
 *
 * （3）按照以上思路，第一个指针left总是指向前面递增数组的元素，第二个指针right总是指向后面递增的数组元素。
 *
 * 最终第一个指针将指向前面数组的最后一个元素，第二个指针指向后面数组中的第一个元素。
 *
 * 也就是说他们将指向两个相邻的元素，而第二个指针指向的刚好是最小的元素，这就是循环的结束条件。
 *
 * 到目前为止以上思路很耗的解决了没有重复数字的情况，这一道题目添加上了这一要求，有了重复数字。
 *
 * 因此这一道题目比上一道题目多了些特殊情况：
 *
 * 我们看一组例子：｛1，0，1，1，1｝ 和 ｛1，1， 1，0，1｝ 都可以看成是递增排序数组｛0，1，1，1，1｝的旋转。
 *
 * 这种情况下我们无法继续用上一道题目的解法，去解决这道题目。因为在这两个数组中，第一个数字，最后一个数字，中间数字都是1。
 *
 * 第一种情况下，中间数字位于后面的子数组，第二种情况，中间数字位于前面的子数组。
 *
 * 因此当两个指针指向的数字和中间数字相同的时候，我们无法确定中间数字1是属于前面的子数组（绿色表示）还是属于后面的子数组
*/


int MinOrder(vector<int>& array, int left, int right)
{
    int result = array[left];
    for(int i = left + 1;i < right;i++)
    {
        if(array[i] < result)
            result = array[i];
    }
    return result;
}

int minNumberArray(vector<int> array)
{
    int length = array.size();
    if(length == 0)
        return 0;
    int left = 0, right = length - 1, mid = 0;
    while(array[left] >= array[right])  //左边元素大于右边元素，确保是旋转数组
    {
        if(right - left == 1)   //num = [6,4] 
        {
            mid = right;
            break;
        }
        mid  = left + (right - left) / 2;
        if(array[left] == array[right] && array[left] == array[mid])    //num = [2,2,2,2,1,2]
        {
            return MinOrder(array, left, right);
        }
        if(array[mid] >= array[left])   //最小元素位于中间元素后面 num = {3,4,5,1,2};
        {
            left = mid;
        }
        else    //最小元素位于中间元素前面 num = {4,1,2,3};
        {
            right = mid;
        }
    }
    return array[mid];
}


int main()
{
    vector<int> num1 = {2,2,2,2,1,2};
    vector<int> num2 = {3,4,5,2};
    int result1 = minNumberArray(num1);
    int result2 = minNumberArray(num2);
    cout << result1 << endl;
    cout << result2 << endl;
    return 0;
}

