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
// ����һ��ԭ���Դ��룬�������Ա���̰���㷨˼·�Ƿ�
// ��ȷ����������û�������Ż���(72��Testcaseȫ����
//
// ��˵����̰��˼·����֤������
// 1�� ��������!=14���߶Ժ�����������ȴ���
// 2�� �����Ƶ�ÿ���Ƶ�ѡ���Ƕ����ģ�
// 3)  ö��һ�ԣ�������ѡ��һ�ԣ�
// 4) ��̰��ѡ��1���ӿ�ͷѡ�������ܴ��м�ѡ��
// 5) ��̰��ѡ��2������ͷ�ĳ���������ͬ����ȥ����
// ����̰��ѡ��Ϊ ��ѡ��ͷ������ͬ����ѡ��ͷ����˳�Ӽ��ɣ�
//

bool Majiang2(vector<int> card3[3])
{
	// ��������ѡ
	// chow
	for (int i = 0; i<3; ++i) {
		for (int j = 1; j <= 7; ++j) {
			card3[i][j] %= 3;		// pung ��ͷ��������ͬ����ȥ
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
	// �ԶԺ�
	if (is7pairs(card2)) return true;

	for (int i = 0; i<3; ++i)
		for (int j = 1; j <= 9; ++j) {
			if (card2[i][j] >= 2) {		// ѡ��һ��
				vector<int> card3[3];
				card3[0] = card2[0], card3[1] = card2[1], card3[2] = card2[2];
				card3[i][j] -= 2;
				if (Majiang2(card3) == true) return true;
			}
		}
	return false;
}
