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
	int xiache = -1;  //-1表示还没上过车，1表示上车然后下车了
}user[10001];

struct ele {
	int dangqianceng = 1;
	int qingqiuxulie[20] = { -1 };  //请求序列为空时，乘客外部请求放入这里，并存储
	int qingqiushu = 0;
	int kongxianqingqiuxulie[20] = { -1 };   //请求序列不为空时，乘客外部请求先放入这里
	int kongxianqingqiushu = 0;
	int chengzhong=0;
	int chengke = 0;
	int jingzhishijian = 0;
	int zhuangtai = 0; //状态0为静止，-1为下行，1为上行
	bool kaimen = 0;
}ele;

void yicengdaiming() {  //若电梯静止300t，则回1层待命
	if (ele.jingzhishijian == 300) {
		ele.dangqianceng = 1;
		ele.zhuangtai = 0;
	}
}

void shengxuqingqiupaixu() {   //新请求放入末尾并排序，小的排在前面
	for(int i=1;i<=ele.qingqiushu-1;i++)
		for (int j = i + 1; j <= ele.qingqiushu; j++) {
			if (ele.qingqiuxulie[i] > ele.qingqiuxulie[j]) {
				int t = ele.qingqiuxulie[i];
				ele.qingqiuxulie[i] = ele.qingqiuxulie[j];
				ele.qingqiuxulie[j] = t;
			}
		}
}

void jiangxuqingqiupaixu() {   //新请求放入末尾并排序，大的排在前面
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

bool chachong(int x){	//检验用户目标层是否已在请求序列中
	int f = 0;
	for (int i = 1; i <= ele.qingqiushu; i++)
		if (x == ele.qingqiuxulie[i]) {
			f = 1;
			break;
		}
	return f;
}

int zhuangtaijisuan() { //检查电梯运动状态
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
							cout << "、" << user[i].num;
							qingqiutianjia(user[i].mubiaoceng);
							shijian += 25;
						}
					}
					else cout << "    " << user[i].num << "等待时间过长离开";
				}
				else {
					f = 0;
					break;
				}
			}
		}
	}
	if (t == 1)return;
	if(f!=0)cout << "号乘客进入电梯  ";
	if (f == 0) cout << "电梯超载，无法继续载客";
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
	cout << "   乘客";
	int t = 1;
	for (int i = 1; i <= keshu; i++) {
		if (user[i].shangche == 1) {  //记得上车变量
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
				cout << "、" << user[i].num;
				shijian += 25;
				user[i].shangche = 0;
				user[i].xiache = 1;
				ele.chengke--;
				ele.chengzhong -= user[i].tizhong;
			}
		}
	}
	cout << "号离开电梯";
}

void showDiantiZhuangTai() {  //显示电梯各项参数状态
	int f = 0;
	ele.zhuangtai = zhuangtaijisuan();
	printf("电梯上有%d人，在%d层--状态：", ele.chengke,ele.dangqianceng);
	if (ele.zhuangtai == 1)cout << "上行";
	else if (ele.zhuangtai == -1)cout << "下行";
	else cout << "静止在" << ele.dangqianceng << "楼";
	cout << "--当前承重：" << ele.chengzhong << "KG";
	cout << "--当前时间：" << shijian;
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
				printf("         %d号乘客想从%d层去%d层", user[keshu].num, user[keshu].dangqianceng, user[keshu].mubiaoceng);
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
		if (ele.qingqiushu != 0) {  //请求数不为0的话
			if (ele.dangqianceng > ele.qingqiuxulie[1])ele.dangqianceng--;
			else if (ele.dangqianceng < ele.qingqiuxulie[1])ele.dangqianceng++;
		}
	}
}

int main()
{
	cout << "=========================电梯模拟系统启动！======================================="<<endl;
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
//等待时间300返回1层
//请求添加