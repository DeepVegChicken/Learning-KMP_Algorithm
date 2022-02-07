#include<iostream>

#include<vector>
#include<string>
#include<sstream>
using namespace std;

class GetNext {
public:
	/*
	 * Func: GetNextArr1
	 * ��ԭλ������next����
	 * ���磺aaab -> [0,1,2,0]
	 */
	void GetNextArr1(vector<int>& next, string pattern) {
		int j = 0, len = next.size();
		for (int i = 1; i < len; ++i) {
			// ����
			while (j > 0 && pattern[i] != pattern[j]) {
				j = next[j - 1];
			}
			if (pattern[i] == pattern[j]) {
				next[i] = ++j;
			}
		}
	}

	/*
	 * Func: GetNextArr2
	 * ����ƽ��һ������next���飬����next[0] = -1
	 * ���磺aaab -> [-1,0,1,2]
	 */
	void GetNextArr2(vector<int>& next, string pattern) {
		// ��ʼλΪ-1����next[-1, ... ...]
		next[0] = -1;

		int j = 0, len = next.size();	// j��Ϊǰ׺ĩβ
		for (int i = 1; i < len; i++) {
			next[i] = j;

			// ����
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
	 * ��ԭλ������next�����KMP�㷨ʵ��
	 * ֻ�ҳ���һ��ƥ����ַ���
	 * Return: ƥ��ʧ�ܷ���-1���ɹ��򷵻�ͷλ��
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
			// ƥ��ɹ�
			if (j == n) {
				return i - n + 1;
			}
		}
		return -1;
	}

	/*
	 * Func: KMP1_2
	 * ��ԭλ������next�����KMP�㷨ʵ��
	 * ���ҳ�����ƥ����ַ���
	 */
	void KMP1_2(string text, string pattern, vector<int>& next, vector<int>& retStarArr) {
		// ��ȡnext����
		int j = 0;
		int	m = text.size(), n = pattern.size();
		for (int i = 0, j = 0; i < m; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = next[j - 1];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			// ƥ��ɹ�
			if (j == n) {
				retStarArr.push_back(i - n + 1);
				j = 0;
			}
		}
	}


	/*
	 * Func: KMP2_1
	 * next��������ƽ��һ���KMP�㷨ʵ��
	 * ֻ�ҳ���һ��ƥ����ַ���
	 * Return: ƥ��ʧ�ܷ���-1���ɹ��򷵻�ͷλ��
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
			// ƥ��ɹ�
			if (j == n) {
				return i - n + 1;
			}
		}
		return -1;
	}

	/*
	 * Func: KMP2_2
	 * next��������ƽ��һ���KMP�㷨ʵ��
	 * ���ҳ�����ƥ����ַ���
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
			// ƥ��ɹ�
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

		// �ַ�������
		int tLen = text.size(), pLen = pattern.size();

		/*
		 * ��ԭλ�����ɵ�next����
		 */
		cout << "��ԭλ������next����: " << endl;

		vector<int> next1(pLen), retArr1;
		GetNext().GetNextArr1(next1, pattern);
		Printf(next1);	// ��֤next���������Ƿ���ȷ

		// ��
		int num1 = KMP().KMP1_1(text, pattern, next1);
		cout << num1 << endl;
		// ��
		KMP().KMP1_2(text, pattern, next1, retArr1);
		if (retArr1.empty()) {
			// ��Ϊ����-1�������ֱ�Ӿͽ���������
			// ���Ե�������ƥ���ʱ�򷵻�-1ʱ����Ҫ��������ķ����͵õ�������
			return -1;
		}
		else {
			Printf(retArr1);
		}

		cout << endl;

		/*
		 * ����ƽ��һ�����ɵ�next����
		 */
		cout << "����ƽ��һ������next����: " << endl;

		vector<int> next2(pLen), retArr2;
		GetNext().GetNextArr2(next2, pattern);
		Printf(next2);	// ��֤next���������Ƿ���ȷ

		// ��
		int num2 = KMP().KMP2_1(text, pattern, next2);
		cout << num2 << endl;
		// ��
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
