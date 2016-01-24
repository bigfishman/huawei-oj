#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;


bool is7pairs(vector<int> card2[3])
{
	for (int i = 0; i<3; ++i)
		for (int j = 1; j <= 9; ++j)
			if (card2[i][j] & 1) return false;
	return true;
}

//
// 这是一份原理性代码，用来测试本题贪心算法思路是否
// 正确，代码性能没做过多优化。(72个Testcase全过）
//
// 简单说明下贪心思路（可证明）：
// 1） 对于牌数!=14，七对胡等特殊情况先处理；
// 2） 三套牌的每套牌的选择是独立的；
// 3)  枚举一对，即首先选出一对，
// 4) （贪心选择1）从开头选，而不能从中间选；
// 5) （贪心选择2）当开头的出现三个相同可以去掉；
// （即贪心选择为 先选开头三个相同，再选开头三个顺子即可）
//

bool Majiang2(vector<int> card3[3])
{
	// 抽碰交叉选
	// chow
	for (int i = 0; i<3; ++i) {
		for (int j = 1; j <= 7; ++j) {
			card3[i][j] %= 3;		// pung 开头的三个相同可以去
			if (!card3[i][j]) continue;
			int minn = min(card3[i][j], min(card3[i][j + 1], card3[i][j + 2]));
			card3[i][j] -= minn, card3[i][j + 1] -= minn, card3[i][j + 2] -= minn;
		}
		for (int j = 8; j <= 9; ++j)
			card3[i][j] %= 3;
	}

	for (int i = 0; i<3; ++i)
		for (int j = 1; j <= 9; ++j)
			if (card3[i][j]) return false;
	return true;
}

bool IsMahjonggWin(char *s)
{
	if (s == NULL) return false;
	vector <int> card2[3];
	vector<int> card[3];

	int nCards = 0;
	for (; *s; nCards++) {
		int num = *s++ - '0';
		char type = *s++;
		if (type == 'T') type = 0;
		else if (type == 'D') type = 1;
		else type = 2;
		card[type].push_back(num);
	}
	if (nCards != 14) return false;
	int total = (card[0].size() != 0) + (card[1].size() != 0) + (card[2].size() != 0);
	if (total > 2) return false;
	sort(card[0].begin(), card[0].end());
	sort(card[1].begin(), card[1].end());
	sort(card[2].begin(), card[2].end());

	//memset(card2, 0, sizeof(card2));
	card2[0].resize(10);
	card2[1].resize(10);
	card2[2].resize(10);
	for (int i = 0; i<3; ++i)
		for (size_t j = 0; j<card[i].size(); ++j) {
			++card2[i][card[i][j]];
		}
	// 对对胡
	if (is7pairs(card2)) return true;

	for (int i = 0; i<3; ++i)
		for (int j = 1; j <= 9; ++j) {
			if (card2[i][j] >= 2) {		// 选出一对
				vector<int> card3[3];
				card3[0] = card2[0], card3[1] = card2[1], card3[2] = card2[2];
				card3[i][j] -= 2;
				if (Majiang2(card3) == true) return true;
			}
		}
	return false;
}
