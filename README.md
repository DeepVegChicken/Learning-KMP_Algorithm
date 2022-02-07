# Learning-KMP_Algorithm
Use C++ to implement KMP algorithm

我已经将两种生成next数组的方法及其对应的KMP算法实现都写在对应的类里了。如对于next数组的计算，就在GetNext类里；其对应的KMP算法则写在KMP类里了，其中：
GetNextArr1 对应 KMP1_1 与 KMP1_2
GetNextArr2 对应 KMP2_1 与 KMP2_2

同一KMP算法的实现（如 KMP1_1 与 KMP1_2）仅在代码的输出实现有所区别。就比如KMP1_1函数是找到第一组匹配的字符串就返回其对应的开头位置，不对剩下的Text字符串继续寻找是否还存在匹配的字符串；而KMP1_2的代码则是找到所有符合的字符串开头位置。

对于代码的字符串输入，读取字符串的函数是与LeetCode是一样的，所有按照LeetCode的字符串输入格式来输入就可以了
