// pacman_bfs.cpp : Defines the entry point for the console application.
// 4210161021 Dhani yanuar erdiansyah
// Referensi https://github.com/fernandoBRS/HackerRank/commit/1cd52e239f32a3734db581715bcf638ca726fef8
#include <conio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

int px, py, fx, fy, n, m;
char arr[40][40];

struct node {
	struct node* par;
int fn, hn, gn;
int cur_row, cur_col;
}*head;

//memasang koodinatnya
struct node *initialize(struct node *par, int i, int j) {
	struct node* p = (struct node*)malloc(sizeof(struct node));
	p->cur_row = i;
	p->cur_col = j;
	p->par = par;
	p->fn = p->gn = p->hn = 0;
	return p;
}

vector <struct node*> closedlist;
vector <struct node*> openlist;
vector <struct node*> generated;

bool check_goal(struct node *p){
	if (p != NULL && p->cur_row == fx && p->cur_col == fy) {
		//jika pencarian selesai
		return true;
	}
	//jika pencarian belum selesai
	return false;
}

//menampilkan semua hasil pencarian
void printas(struct node*p) {
	int c = closedlist.size();
	int d = generated.size();
	cout << c << endl;
	for (int i = 0; i < c; i++)
	{
		cout << closedlist[i]->cur_row << " " << closedlist[i]->cur_col << endl;
	}
	int len;
	std::stack<struct node*> ss;
	while (p&&p->par)
	{
		ss.push(p);
		p = p->par;
	}
	ss.push(p);
	len = ss.size() - 1;
	cout << len << endl;
	while (!ss.empty()) {
		struct node* w = ss.top();
		ss.pop();
		cout << w->cur_row << " " << w->cur_col << endl;
	}
}

// pengecek apakah sudah di visit 
bool visited(struct node* p) {
	int i, c = generated.size();
	for (i = 0; i < c; i++)
	{
		if (generated[i]->cur_row == p->cur_row && generated[i]->cur_col == p->cur_col) {
			return true;
		}
	}
	return false;
}

//check jalan
bool move_up(int a, int b) {
	return(a - 1 >= 0 && arr[a - 1][b] != '%');
}

bool move_down(int a, int b) {
	return(a + 1 < n && arr[a + 1][b] != '%');
}

bool move_left(int a, int b) {
	return(b - 1 >=0 && arr[a][b-1] != '%');
}

bool move_right(int a, int b) {
	return(b + 1 >= 0 && arr[a][b + 1] != '%');
}

void do_the_job(struct node* p) {
	if (visited(p) == false) {
		openlist.push_back(p);
		generated.push_back(p);
	}
}

//2nd
int bfs_pacman() {
	closedlist.clear();
	openlist.clear();
	generated.clear();

	// inisiasi koordinat start
	head = initialize(NULL, px, py);
	openlist.push_back(head);
	generated.push_back(head);
	while (!openlist.empty()) {
		//ambil openlist paling depan
		struct node* p = openlist.front();
		//hapus openlist awal
		openlist.erase(openlist.begin());
		// yang tadi diambil di proses
		int a = p->cur_row;
		int b = p->cur_col;
		// dimasukkan ke closedlist
		closedlist.push_back(p);

		if (check_goal(p)) {
			//Diprint setelah ketemu
			printas(p);
			return 1;
		}

		if (move_up(a, b)) {
			struct node* q = initialize(p, a-1, b);
			do_the_job(q);
		}
		if (move_down(a, b)) {
			struct node* q = initialize(p, a + 1, b);
			do_the_job(q);
		}
		if (move_left(a, b)) {
			struct node* q = initialize(p, a, b-1);
			do_the_job(q);
		}
		if (move_right(a, b)) {
			struct node* q = initialize(p, a, b + 1);
			do_the_job(q);
		}
	}

	return 0;
}

//Pada main ini masih ada beberapa point yang masih kami bingung
// Mengambil referensi yang kami cantumkan di atas, terdapat baris getchar dan getline. yang dimana kami masih belum bisa menjelaskan kegunaan fungsi tersebut.
int main()
{
	cout << "player Player Position : ";	cin >> px >> py;
	cout << "goal : "; cin >> fx >> fy;
	cout << "terrain size : ";  cin >> n >> m;

	//TERRAIN DRAWING
	int i, j;
	string str;
	getchar();
	for (i = 0; i < n; i++)
	{
		getline(cin, str);
		for (j = 0; j<m && j < str.size(); j++)
		{
			arr[i][j] = str[j];
		}
	}

	//MULAI BFS
	i = bfs_pacman();
	cin >> i;

	return 0;
}