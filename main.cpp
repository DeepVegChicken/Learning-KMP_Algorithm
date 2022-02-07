#include<iostream>

#include<vector>
#include<string>
#include<sstream>
using namespace std;

class GetNext {
public:
	/*
	 * Func: GetNextArr1
	 * 按原位置生成next数组
	 * 例如：aaab -> [0,1,2,0]
	 */
	void GetNextArr1(vector<int>& next, string pattern) {
		int j = 0, len = next.size();
		for (int i = 1; i < len; i++) {
			// 回退
			while (j > 0 && pattern[i] != pattern[j]) {
				j = next[j - 1];
			}
			if (pattern[i] == pattern[j]) {
				next[i] = j++;
			}
		}
	}

	/*
	 * Func: GetNextArr2
	 * 向右平移一个生成next数组，其中next[0] = -1
	 * 例如：aaab -> [-1,0,1,2]
	 */
	void GetNextArr2(vector<int>& next, string pattern) {
		// 初始位为-1，即next[-1, ... ...]
		next[0] = -1;

		int j = 0, len = next.size();	// j设为前缀末尾
		for (int i = 1; i < len; i++) {
			next[i] = j;

			// 回退
			while (j > 0 && pattern[i] != pattern[j]) {
				j = next[j];
			}
			if (pattern[i] == pattern[j]) {
				j++;
			}
		}
	}
};

class KMP {
public:
	/*
	 * Func: KMP1_1
	 * 按原位置生成next数组的KMP算法实现
	 * 只找出第一组匹配的字符串
	 * Return: 匹配失败返回-1，成功则返回头位置
	 */
	int KMP1_1(string text, string pattern, vector<int>& next) {
		int j = 0;
		int m = text.size(), n = pattern.size();
		for (int i = 0; i < m; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = next[j - 1];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			// 匹配成功
			if (j == n) {
				return i - n + 1;
			}
		}
		return -1;
	}

	/*
	 * Func: KMP1_2
	 * 按原位置生成next数组的KMP算法实现
	 * 可找出多组匹配的字符串
	 */
	void KMP1_2(string text, string pattern, vector<int>& next, vector<int>& retStarArr) {
		// 获取next数组
		int j = 0;
		int	m = text.size(), n = pattern.size();
		for (int i = 0, j = 0; i < m; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = next[j - 1];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			// 匹配成功
			if (j == n) {
				retStarArr.push_back(i - n + 1);
				j = 0;
			}
		}
	}


	/*
	 * Func: KMP2_1
	 * next数组向右平移一格的KMP算法实现
	 * 只找出第一组匹配的字符串
	 * Return: 匹配失败返回-1，成功则返回头位置
	 */
	int KMP2_1(string text, string pattern, vector<int>& next) {
		int j = 0;
		int m = text.size(), n = pattern.size();
		for (int i = 1; i < m; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = next[j];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			// 匹配成功
			if (j == n) {
				return i - n + 1;
			}
		}
		return -1;
	}

	/*
	 * Func: KMP2_2
	 * next数组向右平移一格的KMP算法实现
	 * 可找出多组匹配的字符串
	 */
	void KMP2_2(string text, string pattern, vector<int>& next, vector<int>& retStarArr) {
		int j = 0;
		int	m = text.size(), n = pattern.size();
		for (int i = 1; i < m; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = next[j];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			// 匹配成功
			if (j == n) {
				retStarArr.push_back(i - n + 1);
				j = 0;
			}
		}
	}
};

string stringToString(string input) {
	string result;
	for (int i = 1; i < input.length() - 1; i++) {
		char currentChar = input[i];
		if (input[i] == '\\') {
			char nextChar = input[i + 1];
			switch (nextChar) {
			case '\"': result.push_back('\"'); break;
			case '/': result.push_back('/'); break;
			case '\\': result.push_back('\\'); break;
			case 'b': result.push_back('\b'); break;
			case 'f': result.push_back('\f'); break;
			case 'r': result.push_back('\r'); break;
			case 'n': result.push_back('\n'); break;
			case 't': result.push_back('\t'); break;
			default: break;
			}
			i++;
		}
		else {
			result.push_back(currentChar);
		}
	}
	return result;
}

string boolToString(bool input) {
	return input ? "True" : "False";
}

void Printf(vector<int>& v) {
	for (auto x : v) {
		cout << x << " ";
	}
	cout << endl;
}

int main() {
	string line;
	while (getline(cin, line)) {
		string text = stringToString(line);
		getline(cin, line);
		string pattern = stringToString(line);

		if (pattern.empty()) {
			return 0;
		}
		if (text.empty()) {
			return -1;
		}

		// 字符串长度
		int tLen = text.size(), pLen = pattern.size();

		/*
		 * 按原位置生成的next数组
		 */
		cout << "按原位置生成next数组: " << endl;

		vector<int> next1(pLen), retArr1;
		GetNext().GetNextArr1(next1, pattern);
		Printf(next1);	// 验证next数组生成是否正确

		// ①
		int num1 = KMP().KMP1_1(text, pattern, next1);
		cout << num1 << endl;
		// ②
		KMP().KMP1_2(text, pattern, next1, retArr1);
		if (retArr1.empty()) {
			// 因为返回-1后编译器直接就结束程序了
			// 所以当遇到不匹配的时候返回-1时，想要测试下面的方法就得单独测试
			return -1;
		}
		else {
			Printf(retArr1);
		}

		cout << endl;

		/*
		 * 向右平移一个生成的next数组
		 */
		cout << "向右平移一个生成next数组: " << endl;

		vector<int> next2(pLen), retArr2;
		GetNext().GetNextArr2(next2, pattern);
		Printf(next2);	// 验证next数组生成是否正确

		// ①
		int num2 = KMP().KMP2_1(text, pattern, next2);
		cout << num2 << endl;
		// ②
		KMP().KMP2_2(text, pattern, next2, retArr2);
		if (retArr2.empty()) {
			return -1;
		}
		else {
			Printf(retArr2);
		}
	}
	return 0;
}
