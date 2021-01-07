#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/*int s, n, k, row1, row2, col1, col2, init[8][8], ret[50][50]; // 1030 프랙탈 평면 (내가 생각한 방법, 오래걸림)

void func(int s, int r1, int r2, int c1, int c2, int isBlack) {
	cout << "s : " << s << ", r1 : " << r1 << ", r2 : " << r2 << ", c1 : " << c1 << ", c2 : " << c2 << endl;
	int i, j;
	if (s == 1 || isBlack) {
		cout << "here, isBlack : "<<isBlack<<endl;
		for (i = r1; i <= r2; i++) {
			for (j = c1; j <= c2; j++) {
				if (isBlack) ret[i - row1][j - col1] = 1; // r1~r2, c1~c2 범위가 전부 검정색인 경우
				else ret[i - row1][j - col1] = init[i % n][j % n]; // s=1인 경우
			}
		}
		return;
	}

	int rs=r1, cs=c1, rStart=0, cStart=0, rBorder=0, cBorder=0, smallerN = (int)pow(n, s - 1); // rs, cs : 시작 지점
																							   // rBorder, cBorder : 각각 행, 열 끊어주는 구간
																							   // smallerN : N^(s-1)
	cout << "smallerN : " << smallerN << endl;
	while (rStart <= r1) rStart += smallerN;
	while (cStart <= c1) cStart += smallerN;

	rBorder = rStart;
	while (true) {
		int blk = 0;
		cs = c1;
		cBorder = cStart;
		int re = min(row2, rBorder - 1);
		while (true) {
			cout << "rs : "<<rs<<", cs : "<<cs<<", rBorder : " << rBorder << ", cBorder : " << cBorder << endl;
			cout << "border : " << smallerN * ((n - k) / 2) << " ~ " << smallerN * ((n + k) / 2) << endl;
			int tmp = pow(n, s), a=rs%tmp, b=cs%tmp;
			if ((a >= smallerN * ((n - k) / 2)) && (a < smallerN * ((n + k) / 2))
				&& (b >= smallerN * ((n - k) / 2)) && (b < smallerN * ((n + k) / 2))) blk = 1;
			else blk = 0;
			int ce = min(col2, cBorder - 1);
			func(s - 1, rs, re, cs, ce, blk);
			if (ce == col2) break; // 열을 전부 분할했을 때 반복문 종료
			cs = cBorder;
			cBorder += smallerN;
		}
		if (re == row2) break; // 행을 전부 분할했을 때 반복문 종료
		rs = rBorder;
		rBorder += smallerN;
	}
	cout << "	r1 : "<<r1<<", r2 : "<<r2<<", c1 : "<<c1<<", c2 : "<<c2<<", end." << endl;
}
int main() {
	int i, j;
	cin >> s >> n >> k >> row1 >> row2 >> col1 >> col2;
	if (s == 0) {
		cout << 0;
		return 0;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i >= (n - k) / 2 && i < (n + k) / 2 && j >= (n - k) / 2 && j < (n + k) / 2) { // 검은색으로 칠하는 부분
				init[i][j] = 1;
			}
			else init[i][j] = 0;
		}
	} //확인 끝

	func(s, row1, row2, col1, col2, 0);

	for (i = 0; i <= row2 - row1; i++) {
		for (j = 0; j <= col2 - col1; j++) {
			cout << ret[i][j];
		}
		cout << endl;
	}
}*/

/*int s, n, k, r1, r2, c1, c2; //1030 프랙탈 평면 (빠름)

int func(int len, int x, int y) {
	if (len == 1) return 0;
	int border = len / n;
	if (x >= border * (n - k) / 2 && x < border * (n + k) / 2 && y >= border * (n - k) / 2 && y < border * (n + k) / 2) {
		return 1;
	}
	return func(border, x % border, y % border);
}

int main() {
	int i, j;
	cin >> s >> n >> k >> r1 >> r2 >> c1 >> c2;
	if (s == 0) {
		cout << 0;
		return 0;
	}
	
	int len = 1;
	while (s--) len *= n;
	for (i = r1; i <= r2; i++) {
		for (j = c1; j <= c2; j++) {
			cout << func(len, i, j);
		}
		cout << endl;
	}
}*/

/*typedef long long ll; // 1034 램프
ll num[50];
int n, m;
ll maxa; // n자리까지 모두 1인 이진수
char board[50][50];

bool chk(ll num, int digit) { // num의 digit자리 bit가 1인지 0인지 확인하는 함수
							  // 1이면 true, 0이면 false return
	return num & ((1ll) << (n-digit-1));
}

ll reverse(ll num) { // num의 bit 0 -> 1로, 1 -> 0으로 변환하는 함수 
	return num ^ maxa;
}

int count(ll sum) { // 변수 sum에서 bit 1의 갯수를 세는 함수
	int ret = 0;
	while (sum > 0) {
		if (sum & 1) ret++;
		sum >>= 1;
	}
	return ret;
}

int main() {
	int i, j, k;
	cin >> n >> m;
	maxa = (((1ll) << n) - 1);
	for (i = 0; i < n; i++) {
		cin >> board[i];
	}
	cin >> k;

	// 각 열을 숫자로 나타내기
	for (i = 0; i < m; i++) { //열
		for (j = 0; j < n; j++) { //행
			num[i] += board[j][i]-'0';
			if(j!=n-1) num[i] <<= 1;
		}
	}

	int ret = 0;
	for (i = 0; i < n; i++) {
		int remain = k;
		long long sum = maxa; // 각 열들 and 연산한 결과가 들어감.
		for (j = 0; j < m; j++) {
			if (!chk(num[j], i)) { // num[j]의 2^i 자리가 0인 경우
				sum &= reverse(num[j]);
				remain--;
			}
			else sum &= num[j];
		}
		if (remain < 0 || remain % 2 == 1) continue;
		ret = max(ret, count(sum));
	}
	cout << ret << endl;
}*/

/*int n, arr[10]; //17127 벚꽃이 정보섬에 피어난 이유

int func(int idx, int prev, int val) {
	if (idx == 4) return val;
	int ret = 0, mul=1;
	for (int i = prev + 1; i < n - (3 - idx); i++) {
		mul *= arr[i];
		ret = max(ret, func(idx + 1, i, val+mul));
	}
	return ret;
}
int main() {
	int i;
	cin >> n;
	for (i = 0; i < n; i++) cin >> arr[i];
	cout << func(0, -1, 0);
}*/

/*map<string, int> mp; //15997 승부 예측

typedef struct game {
	int x, y;
	double win, draw, lose;
}Game;

Game gameArr[6];
double ret[6];
int score[6];
vector<pair<int, int>> finalScore(4);
void func(int idx, double proc) {
	if (idx == 6) { // 경기 끝나고 확률 더해주기
		if (proc == 0) return;
		for (int i = 0; i < 4; i++) {
			finalScore[i] = {score[i], i};
		}
		sort(finalScore.begin(), finalScore.end());
		int aScore = finalScore[0].first,
			bScore = finalScore[1].first,
			cScore = finalScore[2].first,
			dScore = finalScore[3].first;

		int a = finalScore[0].second,
			b = finalScore[1].second,
			c = finalScore[2].second,
			d = finalScore[3].second;
		//----------------------------------------------------------------------------------
		//	점수 경우의 수
		//	1. b != c-> c, d 진출
		//	2. b == c -> d 진출, b/c 추첨하여 한 명 진출 -> b와 c는 p/2 확률로 진출
		//	3. a == b == c -> d 진출, a/b/c 추첨하여 한 명 진출 -> a/b/c는 p/3 확률로 진출
		//	4. b == c == d -> b/c/d 추첨하여 두 명 진출 -> b/c/d p*2/3 확률로 진출
		//	5. a == b == c == d -> a/b/c/d 추첨하여 두 명 진출 -> a/b/c/d p/2 확률로 진출
		//	                                                       
		//-----------------------------------------------------------------------------------

		if (bScore != cScore) { // 1
			ret[c] += proc;
			ret[d] += proc;
		}
		else if (aScore == bScore && cScore == dScore) { // 5
			ret[a] += proc / 2;
			ret[b] += proc / 2;
			ret[c] += proc / 2;
			ret[d] += proc / 2;
		}
		else if (aScore == bScore) { // 3
			ret[a] += proc / 3;
			ret[b] += proc / 3;
			ret[c] += proc / 3;
			ret[d] += proc;
		}
		else if (cScore == dScore) { // 4
			ret[b] += proc * 2 / 3;
			ret[c] += proc * 2 / 3;
			ret[d] += proc * 2 / 3;
		}
		else { // 2
			ret[b] += proc / 2;
			ret[c] += proc / 2;
			ret[d] += proc;
		}
		return;
	}

	//-----------------------------------------
	//	idx번째 게임의 참가자를 x, y라 하자.
	//	1. x가 이겼을 때
	//	2. 비겼을 때
	//	3. y가 이겼을 때
	//	로 나눌 수 있다. 각각의 경우 완전탐색
	//-----------------------------------------

	Game g = gameArr[idx];
	//1. x가 이겼을 때
	score[g.x] += 3;
	func(idx + 1, proc * g.win);
	score[g.x] -= 3;

	//2. 둘이 비겼을 때
	score[g.x]++;
	score[g.y]++;
	func(idx + 1, proc * g.draw);
	score[g.x]--;
	score[g.y]--;

	//3. y가 이겼을 때
	score[g.y] += 3;
	func(idx + 1, proc * g.lose);
	score[g.y] -= 3;
}

int main() {
	int i;
	string a, b;
	double p, q, r;
	for (i = 0; i < 4; i++) {
		cin >> a;
		mp[a] = i;
	}

	for (i = 0; i < 6; i++) {
		cin >> a >> b >> p >> q >> r;
		gameArr[i] = { mp[a], mp[b], p, q, r };
	}

	func(0, 1.0);

	cout << fixed;
	cout.precision(10);
	for (i = 0; i < 4; i++) {
		cout << ret[i] << endl;
	}
}*/

/*const int MAX = 300000; //15998 카카오머니
typedef long long ll;
int n;
ll arr[MAX][2];
vector<pair<int, ll>> vec;
vector<ll> measure;
ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	int i, chk=1;
	ll curMoney = 0;
	cin >> n;
	//1. 인출 금액 구하기
	for (i = 0; i < n; i++) {
		cin >> arr[i][0] >> arr[i][1];
		if (arr[i][0] < 0 && -arr[i][0] > curMoney) { // 현재 금액보다 더 많은 금액을 출금하려 하는 경우
			ll km = arr[i][1] - arr[i][0] - curMoney; // 금액 m을 k번 인출했을 때의 인출 금액
			vec.emplace_back(i, km);
		}
		else if(curMoney + arr[i][0] != arr[i][1]) {
			chk = 0;
		}
		curMoney = arr[i][1];
	}
	
	if (!chk) {
		cout << -1;
		return 0;
	}
	if (vec.size()) {
		//2. 인출 금액들의 최대공약수 구하기
		ll tmp = vec[0].second;
		for (i = 1; i < vec.size(); i++) {
			if (tmp < vec[i].second) tmp = gcd(vec[i].second, tmp);
			else tmp = gcd(tmp, vec[i].second);
		}

		int chk = 1;
		for (auto it : vec) {
			int idx = it.first;
			ll prev = (idx == 0 ? 0 : arr[idx - 1][1]);
			if (it.second - tmp >= -(prev + arr[idx][0])) { // 만일 인출을 필요 이상으로 한 경우,
															// 이 값은 답이 될 수 없다.
				chk = 0;
				break;
			}
		}
		if (chk) {
			cout << tmp;
			return 0;
		}
		cout << -1;
	}
	else cout << 1;
}*/

/*typedef vector<vector<long long>> Matrix; //11444 피보나치 수 6
const int MOD = 1e9 + 7;
long long n;
Matrix init = { {1, 1}, {1, 0} };

Matrix matrixMul(Matrix a, Matrix b) {
	Matrix ret(2);
	int i, j, k;
	for (i = 0; i < 2; i++) {
		ret[i].resize(2);
		for (j = 0; j < 2; j++) {
			ret[i][j] = 0;
			for (k = 0; k < 2; k++) {
				ret[i][j] += a[i][k] * b[k][j];
				ret[i][j] %= MOD;
			}
		}
	}
	return ret;
}

Matrix func(long long n) {
	if (n == 1) return init;
	Matrix tmp;
	if (n % 2) { // n 홀수
		tmp = func(n - 1);
		return matrixMul(init, tmp);
	}
	else { // n 짝수
		tmp = func(n / 2);
		return matrixMul(tmp, tmp);
	}
}

int main(){
	cin >> n;
	if (n == 0) {
		cout << 0;
		return 0;
	}

	Matrix ret = func(n);
	cout << ret[1][0];
}*/

/*const int MOD = 1e9 + 7; // 15999 뒤집기	
int nxt[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
char board[2000][2000];

long long func(int num) {
	if (num == 1) return 2;
	long long tmp;
	if (num % 2) {
		tmp = func(num - 1);
		return (2 * tmp) % MOD;
	}
	else {
		tmp = func(num / 2);
		return (tmp * tmp) % MOD;
	}
}
int main() {
	int i, j, k, n, m;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		cin >> board[i];
	}

	int num = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			char here = board[i][j];
			for (k = 0; k < 4; k++) {
				int nxtX = i + nxt[k][0], nxtY = j + nxt[k][1];
				if (nxtX < 0 || nxtX >= n || nxtY < 0 || nxtY >= m) continue;
				if (board[nxtX][nxtY] != here) break;
			}
			if (k == 4) {
				num++;
			}
		}
	}
	cout << func(num) << endl;
}*/

/*const int UNIT = 10000; // 15953 상금 헌터
int firstArr[2][6] = { {1, 3, 6, 10, 15, 21}, {500, 300, 200, 50, 30, 10} },
    secondArr[2][5] = { {1, 3, 7, 15, 31}, {512, 256, 128, 64, 32} };
int main() {
	int i, j, t, a, b;
	cin >> t;
	for (i = 0; i < t; i++) {
		cin >> a >> b;
		int num = 0;
		if (a != 0) {
			for (j = 0; j < 6; j++) {
				if (firstArr[0][j] >= a) {
					num += firstArr[1][j];
					break;
				}
			}
		}

		if (b != 0) {
			for (j = 0; j < 5; j++) {
				if (secondArr[0][j] >= b) {
					num += secondArr[1][j];
					break;
				}
			}
		}
		cout << num * UNIT << "\n";
	}
}*/

/*typedef long long ll; // 1081 합

int arr[10] = { 0, 1, 3, 6, 10, 15, 21, 28, 36, 45 };
ll func(int n) {
	ll div = 1, sum = 0;
	while (n / div > 0) {
		int quot = n / (div * 10), remainder = n % (div * 10);
		if (n / (div*10) != 0) {
			sum += quot * div * arr[9];
		}
		ll smallerDivQuot = remainder / div, smallerDivRemainder = remainder % div;
		if (div != 1) {
			sum += smallerDivQuot * (smallerDivRemainder + 1ll);
		}
		if (div == 1) {
			sum += arr[smallerDivQuot] * div;
		}
		else
			sum += arr[smallerDivQuot - 1] * div;
		div *= 10;
	}
	return sum;
}
int main() {
	int a, b;
	cin >> a >> b;
	cout << func(b) - func(a - 1);
}*/

/*char board[8][8]; //1100 하얀 칸
int main() {
	int i, j, chk = 1, ret=0;
	for (i = 0; i < 8; i++) {
		cin >> board[i];
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (chk && board[i][j] == 'F') ret++;
			chk = (chk + 1) % 2;
		}
		chk = (chk + 1) % 2;
	}
	cout << ret;
}*/

/*int rad[2002]; //1254 팰린드롬 만들기
int main() {

	string s;
	cin >> s;
	char temp[2002];
	int i, r=0, c=0, len=s.length();
	for (i = 0; i < len; i++) {
		temp[2 * i] = '#';
		temp[2 * i + 1] = s[i];
	}
	temp[2 * len] = '#';
	temp[2 * len + 1] = '\0';
	for (i = 0; i <= 2*len; i++) {
		if (r < i) rad[i] = 0;
		else rad[i] = min(rad[2 * c - i], r - i);
		while (i + rad[i] + 1 <= 2 * len && i - (rad[i] + 1) >= 0
			&& temp[i + rad[i] + 1] == temp[i - rad[i] - 1]) {
			rad[i]++;
		}
		if (r < i + rad[i]) {
			r = i + rad[i];
			c = i;
		}
	}

	int mina = 1e9;
	for (i = 0; i <= 2*len; i++) {
		if (rad[i] + i == 2 * len) {
			int t = ((i - 1) - (2 * len - 1 - i)) / 2;
			mina = min(mina, t);
		}
	}
	cout << len + mina << endl;
}*/

/*int dp[5000][5000]; // 5502 팰린드롬
int main() {
	int i, j, n;
	string s, sRev;
	cin >> n >> sRev;
	s = sRev;
	reverse(sRev.begin(), sRev.end());
	for (i = 0; i < n; i++) {
		if (s[i] == sRev[0] || (i > 0 && dp[0][i - 1] == 1)) dp[0][i] = 1;
		if (sRev[i] == s[0] || (i > 0 && dp[i - 1][0] == 1)) dp[i][0] = 1;
	}

	int ret = 0;
	for (i = 1; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (sRev[i] == s[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
			dp[i][j] = max(dp[i][j], max(dp[i - 1][j], dp[i][j - 1]));
			ret = max(ret, dp[i][j]);
		}
	}
	cout << n - ret;
}*/

/*const int MAX = 2000000; // 1747 소수&팰린드롬
int arr[MAX], prime[MAX], sz=0;
void func() {
	int i;
	for (i = 2; i * i <= MAX; i++) {
		if (arr[i]) continue;
		int here = i * 2;
		while (here <= MAX) {
			arr[here] = 1;
			here += i;
		}
	}

	for (i = 2; i < MAX; i++) {
		if (arr[i] == 0) {
			prime[sz++] = i;
		}
	}
}

bool isPalindrome(int num) {
	string s = to_string(num);
	int i=0, j=s.length()-1;
	while (i < j) {
		if (s[i] != s[j]) return false;
		i++;
		j--;
	}
	return true;
}
int main() {
	int i, n;
	func();
	cin >> n;
	for (i = 0; i < sz; i++) {
		if (n > prime[i]) continue;
		if (isPalindrome(prime[i])) {
			cout << prime[i];
			return 0;
		}
	}
}*/