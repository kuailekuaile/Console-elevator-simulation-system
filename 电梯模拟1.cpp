#include<iostream>
#include<Windows.h>
#include<string>
#include<cstdio>
using namespace std;

const int diantimaxwaitime = 300;
const int maxwaitime = 600;
const int maxchengzhong = 1000;
int shijian = 0;
int keshu = 0;
int s = 0;

struct user {
	int dengdaishijian=0;
	int dangqianceng;
	int mubiaoceng;
	int tizhong;
	int num;
	bool shangche = 0;
	int xiache = -1;  //-1��ʾ��û�Ϲ�����1��ʾ�ϳ�Ȼ���³���
}user[10001];

struct ele {
	int dangqianceng = 1;
	int qingqiuxulie[20] = { -1 };  //��������Ϊ��ʱ���˿��ⲿ�������������洢
	int qingqiushu = 0;
	int kongxianqingqiuxulie[20] = { -1 };   //�������в�Ϊ��ʱ���˿��ⲿ�����ȷ�������
	int kongxianqingqiushu = 0;
	int chengzhong=0;
	int chengke = 0;
	int jingzhishijian = 0;
	int zhuangtai = 0; //״̬0Ϊ��ֹ��-1Ϊ���У�1Ϊ����
	bool kaimen = 0;
}ele;

void yicengdaiming() {  //�����ݾ�ֹ300t�����1�����
	if (ele.jingzhishijian == 300) {
		ele.dangqianceng = 1;
		ele.zhuangtai = 0;
	}
}

void shengxuqingqiupaixu() {   //���������ĩβ������С������ǰ��
	for(int i=1;i<=ele.qingqiushu-1;i++)
		for (int j = i + 1; j <= ele.qingqiushu; j++) {
			if (ele.qingqiuxulie[i] > ele.qingqiuxulie[j]) {
				int t = ele.qingqiuxulie[i];
				ele.qingqiuxulie[i] = ele.qingqiuxulie[j];
				ele.qingqiuxulie[j] = t;
			}
		}
}

void jiangxuqingqiupaixu() {   //���������ĩβ�����򣬴������ǰ��
	for (int i = 1; i <= ele.qingqiushu - 1; i++)
		for (int j = i + 1; j <= ele.qingqiushu; j++) {
			if (ele.qingqiuxulie[i] < ele.qingqiuxulie[j]) {
				int t = ele.qingqiuxulie[i];
				ele.qingqiuxulie[i] = ele.qingqiuxulie[j];
				ele.qingqiuxulie[j] = t;
			}
		}
}

void kongxianqingqiuquchu() {  //
	if (ele.kongxianqingqiushu == 1) {
		ele.kongxianqingqiushu--;
	}
	else
	{
		for (int i = 1; i <= ele.kongxianqingqiushu - 1; i++)ele.kongxianqingqiuxulie[i] = ele.kongxianqingqiuxulie[i + 1];
		ele.kongxianqingqiushu--;
	}
}

void kongxianqingqiupaixu() {
	for (int i = 1; i <= ele.kongxianqingqiushu - 1; i++)
		for (int j = i + 1; j <= ele.kongxianqingqiushu; j++) {
			if (ele.kongxianqingqiuxulie[i] > ele.kongxianqingqiuxulie[j]) {
				int t = ele.kongxianqingqiuxulie[i];
				ele.kongxianqingqiuxulie[i] = ele.kongxianqingqiuxulie[j];
				ele.kongxianqingqiuxulie[j] = t;
			}
		}
}

void gengxinqingqiu() {
	if (ele.qingqiushu == 0 && ele.kongxianqingqiushu != 0) {
		for (int i = 1; i <= ele.kongxianqingqiushu; i++) {
			ele.qingqiushu++;
			ele.qingqiuxulie[i]=ele.kongxianqingqiuxulie[i];
		}
		kongxianqingqiuquchu();
	}
}

bool chachong(int x){	//�����û�Ŀ����Ƿ���������������
	int f = 0;
	for (int i = 1; i <= ele.qingqiushu; i++)
		if (x == ele.qingqiuxulie[i]) {
			f = 1;
			break;
		}
	return f;
}

int zhuangtaijisuan() { //�������˶�״̬
	if (ele.qingqiushu == 0)return 0;
	if (ele.dangqianceng > ele.qingqiuxulie[1])return -1;
	else if (ele.dangqianceng < ele.qingqiuxulie[1])return 1;
	else return 0;
}

void qingqiuquchu() {
	if (ele.qingqiushu == 0)return;
	if (ele.qingqiushu == 1) {
		ele.qingqiushu--;
		return;
	}
	else for (int i = 1; i <= ele.qingqiushu - 1; i++)ele.qingqiuxulie[i] = ele.qingqiuxulie[i + 1];
	ele.qingqiushu--;
}

void qingqiutianjia(int x) {
	if (ele.qingqiushu == 0) {
		ele.qingqiushu++;
		ele.qingqiuxulie[ele.qingqiushu] = x;
	}
	else {
		int f = 0;    
		for (int i = 1; i <= ele.qingqiushu; i++)
			if (x == ele.qingqiuxulie[i]) {
				f = 1;
				break;
			}
		if (f == 0) {
			for (int i = 1; i <= ele.kongxianqingqiushu; i++) {
				if (x == ele.kongxianqingqiuxulie[i]) {
					f = 1;
					break;
				}
			}
		}
		if (f == 0&&ele.zhuangtai==1) {
			ele.qingqiushu++;
			ele.qingqiuxulie[ele.qingqiushu] = x;
			shengxuqingqiupaixu();
		}
		else if (f == 0 && ele.zhuangtai == -1) {
			ele.qingqiushu++;
			ele.qingqiuxulie[ele.qingqiushu] = x;
			jiangxuqingqiupaixu();
		}
	}
}

void shangche() {
	cout << "    ";
	int t = 1, f = 1;
	for (int i = 1; i <= keshu; i++) {
		if (ele.dangqianceng == user[i].dangqianceng && user[i].xiache != 1) {
			if (user[i].shangche == 0) {
				if (ele.chengzhong + user[i].tizhong <= maxchengzhong) {
					if (user[i].dengdaishijian <= maxwaitime) {
						user[i].shangche = 1;
						ele.chengzhong += user[i].tizhong;
						ele.chengke++;
						if (t == 1) {
							qingqiuquchu();
							cout << user[i].num;
							t++;
							qingqiutianjia(user[i].mubiaoceng);
							shijian += 25;
						}
						else {
							cout << "��" << user[i].num;
							qingqiutianjia(user[i].mubiaoceng);
							shijian += 25;
						}
					}
					else cout << "    " << user[i].num << "�ȴ�ʱ������뿪";
				}
				else {
					f = 0;
					break;
				}
			}
		}
	}
	if (t == 1)return;
	if(f!=0)cout << "�ų˿ͽ������  ";
	if (f == 0) cout << "���ݳ��أ��޷������ؿ�";
}

int chengkedaozhan() {
	if (ele.chengke == 0)return 0;
	int f = 0; //
	if (ele.dangqianceng == ele.qingqiuxulie[1]) {
		for (int i = 1; i <= keshu; i++) {
			if (ele.dangqianceng == user[i].mubiaoceng && user[i].shangche == 1) {
				f = 1;
				break;
			}
		}
	}
	if (f == 1)return 1;
	else return 0;
}

int diantidaozhan() {
	int f = 0,x = 0;
	for (int i = 1; i <= keshu; i++) {
		if (ele.dangqianceng == user[i].dangqianceng && user[i].shangche == 0 && user[i].xiache == -1) {
			f = 1;
			break;
		}
	}
	if (ele.qingqiushu == 0) {
		if (ele.kongxianqingqiushu == 0)s = 1;
		else {
			gengxinqingqiu();
		}
	}
	else {
		s = 0;
		ele.jingzhishijian = 0;
	}
	if (f == 1)return 1;
	else return 0;
}

void xiache() {
	cout << "   �˿�";
	int t = 1;
	for (int i = 1; i <= keshu; i++) {
		if (user[i].shangche == 1) {  //�ǵ��ϳ�����
			if (user[i].mubiaoceng == ele.dangqianceng && t == 1) {
				cout << user[i].num;
				user[i].shangche = 0;
				user[i].xiache = 1;
				ele.chengke--;
				ele.chengzhong -= user[i].tizhong;  
				t += 1;
				shijian += 25;
				qingqiuquchu();
			}
			else if (user[i].mubiaoceng == ele.dangqianceng) {
				cout << "��" << user[i].num;
				shijian += 25;
				user[i].shangche = 0;
				user[i].xiache = 1;
				ele.chengke--;
				ele.chengzhong -= user[i].tizhong;
			}
		}
	}
	cout << "���뿪����";
}

void showDiantiZhuangTai() {  //��ʾ���ݸ������״̬
	int f = 0;
	ele.zhuangtai = zhuangtaijisuan();
	printf("��������%d�ˣ���%d��--״̬��", ele.chengke,ele.dangqianceng);
	if (ele.zhuangtai == 1)cout << "����";
	else if (ele.zhuangtai == -1)cout << "����";
	else cout << "��ֹ��" << ele.dangqianceng << "¥";
	cout << "--��ǰ���أ�" << ele.chengzhong << "KG";
	cout << "--��ǰʱ�䣺" << shijian;
	if (chengkedaozhan() != 0) {
		xiache();
		f = 1;
	}
	if (diantidaozhan() != 0) {
		shangche();
		f = 1;
	}
	if (f == 1)shijian += 80;
}

void qingqiu(){  
	if (shijian % 50 == 0) {
		int x = rand() % 2;
		if (x == 1 && keshu < 10001) {
			keshu++;
			user[keshu].dangqianceng = rand() % 5;
			user[keshu].mubiaoceng = rand() % 5;
			if (user[keshu].dangqianceng!= user[keshu].mubiaoceng) {
				user[keshu].tizhong = (rand() % 100) + 30;
				user[keshu].num = keshu;
				printf("         %d�ų˿����%d��ȥ%d��", user[keshu].num, user[keshu].dangqianceng, user[keshu].mubiaoceng);
				if (ele.qingqiushu == 0) {
					ele.qingqiushu++;
					ele.qingqiuxulie[ele.qingqiushu] = user[keshu].dangqianceng;
				}
				else {
					int f = 0;
					for (int i = 1; i <= ele.qingqiushu; i++)
						if (user[keshu].dangqianceng == ele.qingqiuxulie[i]) {
							f = 1;
							break;
						}
					if (f == 0) {
						for (int i = 1; i <= ele.kongxianqingqiushu; i++) {
							if (user[keshu].dangqianceng == ele.kongxianqingqiuxulie[i]) {
								f = 1;
								break;
							}
						}
					}
					if (f == 0) {
						if (user[keshu].dangqianceng - user[keshu].mubiaoceng > 0 && ele.zhuangtai == -1 && user[keshu].dangqianceng > ele.qingqiuxulie[1] && user[keshu].dangqianceng < ele.dangqianceng) {
							if (ele.qingqiuxulie[1] != user[keshu].mubiaoceng) {
								ele.qingqiushu++;
								ele.qingqiuxulie[ele.qingqiushu] = user[keshu].dangqianceng;
								jiangxuqingqiupaixu();
							}
						}
						else if (user[keshu].dangqianceng - user[keshu].mubiaoceng < 0 && ele.zhuangtai == 1 && user[keshu].dangqianceng < ele.qingqiuxulie[1] && user[keshu].dangqianceng > ele.dangqianceng)
						{
							if (ele.qingqiuxulie[1] != user[keshu].mubiaoceng){
								ele.qingqiushu++;
								ele.qingqiuxulie[ele.qingqiushu] = user[keshu].dangqianceng;
								shengxuqingqiupaixu();
							}
						}
						else {
							ele.kongxianqingqiushu++;
							ele.kongxianqingqiuxulie[ele.kongxianqingqiushu] = user[keshu].dangqianceng;
						}
					}
				}
			}
			else keshu--;
		}
	}
}

void qingqiugengxin() {
	if (ele.qingqiushu == 0 && ele.kongxianqingqiushu!=0) {
		ele.qingqiushu++;
		ele.qingqiuxulie[ele.qingqiushu] = ele.kongxianqingqiuxulie[1];
		if (ele.kongxianqingqiushu == 1)ele.kongxianqingqiushu--;
		else{
			for (int i = 1; i <= ele.kongxianqingqiushu - 1; i++)ele.kongxianqingqiuxulie[i] = ele.kongxianqingqiuxulie[i + 1];
		}
		ele.kongxianqingqiushu = 0;
	}
}

void dengdaishijian(){
	for (int i = 1; i <= keshu; i++)user[keshu].dengdaishijian++;
}

void yundong() {
	if (shijian % 25 == 0) {
		showDiantiZhuangTai();
		qingqiu();
		qingqiugengxin();
		if (ele.qingqiushu != 0) {  //��������Ϊ0�Ļ�
			if (ele.dangqianceng > ele.qingqiuxulie[1])ele.dangqianceng--;
			else if (ele.dangqianceng < ele.qingqiuxulie[1])ele.dangqianceng++;
		}
	}
}

int main()
{
	cout << "=========================����ģ��ϵͳ������======================================="<<endl;
	while (1) {
		yundong();

		cout << endl;
		dengdaishijian();
		if (s == 1)ele.jingzhishijian++;
		shijian++;
		Sleep(100);
	}
	
	return 0;
}
//�ȴ�ʱ��300����1��
//�������