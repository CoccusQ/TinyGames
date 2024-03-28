#include<iostream>
#include<conio.h>
#include<string>
#include<cstring>
#include<ctime>
#include<cstdlib>
using namespace std;

int path[128];
char showpath[2][128];
int backage[8];
int myweapon[5];
int killed_num=0;

enum Site{STORE=1,FLAT,CLINIC,SCHOOL,FACTORY,STREET,BASE};
enum Item{WATER=1,BREAD,MEAT,MEDICINE,WOOD,STEEL,AMMO};
enum ZombieType{NORMAL=1,INFECTED,GIANT};
enum Weapon{PUNCH=1,STICK,KNIFE,GUN};

string forwards=" =>>>>>>>>>>>>>>";
string backwards=" <<============";
string progress_bar=" ################";
string e="搜索中........\n";
string name,search_result;
string win="\n 击杀成功!!!";
string lose="\n 你战死了!!!";
string escaped="\n 成功逃跑!!!";

class Player{
    public:
        Player(int xx=0,int bg=100,int sty=100,int lf=100,int attk=5,int ex=0,int wpn=PUNCH):
            x(xx),bag(bg),satiety(sty),life(lf),atk(attk),exp(ex),weapon(wpn),b_atk(attk){}
        int setx(){x=0;return x;}
        int getx(){return x;}
        int getsatiety(){return satiety;}
        int getlife(){return life;}
        int get_atk(){return atk;}
        int getExp(){return exp;}
        int get_weapontype(){return weapon;}
        void forward(){
            if(x+1>127){
                cout<<"已到达边界."<<endl;
                _sleep(500);
                return;
            }
            x++;
        }
        void backward(){
            if(x-1<0){
                cout<<"已到达边界."<<endl;
                _sleep(500);
                return;
            }
            x--;
        }
        void eat(int i){
            if(i>=1&&i<=4){
                if(backage[i]<=0){
                    cout<<" 背包中没有该物品..."<<endl;
                    _sleep(500);
                    return;
                }
                backage[i]--;
            }
            switch (i){
                case WATER:
                    satiety+=2;
                    life+=5;
                    break;
                case BREAD:
                    satiety+=20;
                    life+=2;
                    break;
                case MEAT:
                    satiety+=12;
                    life+=5;
                    break;
                case WOOD:
                    break;
                case STEEL:        
                    break;
                case AMMO:       
                    break;
                case MEDICINE:
                    life+=24;
                    break;
                default:
                    break;
            }
            if(life>=100) life=100;
            if(satiety>=100) satiety=100;
        }
        void decrease_satiety(int num){
            if(satiety>0){
                satiety-=num;
            }
            if(satiety<0){
                satiety=0;
            }
        }
        void starve(int num){
            if(satiety<=20&&life>0){
                life-=num;
            }
            if(life<=0){
                life=0;
                system("cls");system("color 04");
                cout<<"\n 你饿死了."<<endl;
                _sleep(1000);
            }
        }
        void increaseHP(int num){life+=num;}

        void decreaseHP(int atk){life-=atk;}

        void addExp(int num){exp+=num;}

        void addAtk(int num){exp+=num;}

        void level_up(){
            if(exp<15){
                b_atk=5;
            }
            else if(exp>=15&&exp<=25){
                b_atk=10;
            }
            else if(exp<=35){
                b_atk=15;
            }
            else{
                b_atk=24;
            }
            atk=b_atk;
        }

        void change_weapon(int wpn){
            switch(wpn){
            case PUNCH:
                atk=b_atk;
                break;
            case STICK:
                atk=5+b_atk;
                break;
            case KNIFE:
                atk=15+b_atk;
                break;
            case GUN:
                atk=24+b_atk;
                break;
            default:
                break;
            }
            weapon=wpn;
        }
    private:
        int x;
        int bag;
        int satiety;
        int life;
        int atk;
        int exp;
        int weapon;
        int b_atk;
};


class Zombie{
    public:
        Zombie(int ztype=NORMAL):type(ztype){
            switch(type){
                case NORMAL:
                    life=50;
                    atk=4;
                    name="普通丧尸";
                    break;
                case INFECTED:
                    life=70;
                    atk=8;
                    name="感染者";
                    break;
                case GIANT:
                    life=200;
                    atk=20;
                    name="巨型丧尸";
                    break;
                default:
                    break;
            }
        }
        string getZName(){return name;}
        int getZType(){return type;}
        int get_atk(){return atk;}
        int getlife(){return life;}
        int decreaseHP(int atk){life-=atk;return life;}
    private:
        int life;
        int atk;
        string name;
        int type;
};

string show_WeaponName(int i);

void showdata(Player &p1){
    cout<<"+--------------------"<<endl;
    cout<<"| 位置 X : "<<p1.getx()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 生命值 : "<<p1.getlife()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 饱食度 : "<<p1.getsatiety()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 经验值 : "<<p1.getExp()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 攻击力 : "<<p1.get_atk()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 武器   : "<<show_WeaponName(p1.get_weapontype())<<endl;
    cout<<"+--------------------"<<endl;
}


void printline(string s,int t1=100,int t2=50,int t3=500){
    _sleep(t1);
    for(long long unsigned int i=0;i<s.length();i++){
        cout<<s[i];
        if(s[i]==' '||s[i]==','||s[i]=='.'){
            _sleep(t2);
        }
        _sleep(t2);
    }
    _sleep(t3);
}


void site(Player &p){
    int x=p.getx();
    path[0]=BASE;
    if(path[x]==0&&x!=0){
        path[x]=rand()%6+1;
    }
    cout<<"\n*";
    switch(path[x]){
    case STORE:
        cout<<" 商店."<<endl;
        showpath[1][x]='M';
        break;
    case FLAT:
        cout<<" 居民楼."<<endl;
        showpath[1][x]='R';
        break;
    case CLINIC:
        cout<<" 诊所."<<endl;
        showpath[1][x]='+';
        break;
    case SCHOOL:
        cout<<" 学校."<<endl;
        showpath[1][x]='S';
        break;
    case FACTORY:
        cout<<" 工厂."<<endl;
        showpath[1][x]='F';
        break;
    case STREET:
        cout<<" 街道."<<endl;
        showpath[1][x]='_';
        break;
    case BASE:
        cout<<" 基地. 你安全的庇护所."<<endl;
        showpath[1][x]='B';
        break;
    default:
        break;
    }
}


void printpath(Player &p){
    int x=p.getx();
    showpath[0][x]='v';
    cout<<"\n ";
    for(int i=0;path[i]!=0;i++){
        cout<<showpath[0][i]<<"  ";
    }
    cout<<"\n_";
    for(int i=0;path[i]!=0;i++){
        cout<<showpath[1][i]<<"__";
    }
    cout<<"...\n"<<endl;
    showpath[0][x]=' ';
}


string showname(int i){
    string name;
    switch (i){
    case WATER:
        name="水";
        break;
    case BREAD:
        name="面包";
        break;
    case MEAT:
        name="午餐肉";
        break;
    case WOOD:
        name="木材";
        break;
    case STEEL:
        name="钢铁";
        break;
    case AMMO:
        name="弹药";
        break;
    case MEDICINE:
        name="药品";
        break;
    default:
        break;
    }
    return name;
}


string show_WeaponName(int i){
    string name;
    switch(i){
        case PUNCH:
            name="无";
            break;
        case STICK:
            name="木棍";
            break;
        case KNIFE:
            name="刀";
            break;
        case GUN:
            name="手枪";
            break;
        default:
            break;
    }
    return name;
}

void explore(Player &p){
    int i=rand()%6+1;
    int num=1;
    switch(path[p.getx()]){
    case STORE:
        if(i==WATER||i==BREAD||i==MEAT)num=5;
        if(i==MEDICINE) i=WATER;
        break;
    case FLAT:
        if(i==WOOD||i==STEEL)num=2;
        break;
    case CLINIC:
        if(i==MEDICINE||i==WATER)num=4;
        if(i==WOOD||i==STEEL) i=MEDICINE;
        break;
    case SCHOOL:
        if(i==WATER||i==BREAD)num=2;
        break;
    case FACTORY:
        if(i==WOOD||i==STEEL)num=5;
        else if(i==MEAT||i==BREAD){
            i=STEEL;num=5;
        }
        break;
    case STREET:
        i=WOOD;
        break;
    default:
        break;
    }
    backage[i]+=num;
    name=showname(i);
    string number=to_string(num);
    search_result=" 获得 "+name+" X"+number;
    printline(search_result);
    _sleep(500);
}


void showbag(){
    int sum=0;
    cout<<endl; 
    for(int i=1;i<=7;i++){
        if(backage[i]>0){
            cout<<"+----------------"<<endl;
            cout<<"| "<<i<<"."<<showname(i)<<"  "<<backage[i]<<endl;
            sum++;
        }
    }
    if(sum==0){
        cout<<" 背包还是空的..."<<endl;
        return;
    }
    cout<<"+----------------\n"<<endl;
}


int showweapon(Player &p){
    int sum=0;
    for(int i=2;i<=4;i++){
        if(myweapon[i]!=0){
            cout<<"+----------------"<<endl;
            cout<<"| "<<i<<"."<<show_WeaponName(i)<<"  "<<myweapon[i]<<endl;
            sum++;
        }
    }
    if(sum==0){
        cout<<" 当前无武器..."<<endl;
        return 0;
    }
    cout<<"+----------------"<<endl;
    cout<<"\n 请输入序号选择武器..."<<endl;
    char c=_getch();
    int choice=c-'0';
    return choice;
}


void make_weapon(){
    int num1=0,num2=0;
    cout<<"+-------------------------"<<endl;
    cout<<"| 1.木棍: 木材 X2"<<endl;
    cout<<"+-------------------------"<<endl;
    cout<<"| 2.刀  : 木材 X3 钢铁 X6"<<endl;
    cout<<"+-------------------------"<<endl;
    cout<<"| 3.枪  : 木材 X2 钢铁 X15"<<endl;
    cout<<"+-------------------------"<<endl;
    cout<<"| 4.弹药: 钢铁 X3"<<endl;
    cout<<"+-------------------------"<<endl;
    cout<<"\n 请输入相应序号制作武器..."<<endl;
    char c=_getch();
    int choice=c-'0';
    switch(choice){
    case 1:
        num1=2;
        myweapon[STICK]++;
        break;
    case 2:
        num1=3;num2=6;
        myweapon[KNIFE]++;
        break;
    case 3:
        num1=2;num2=15;
        myweapon[GUN]++;
        break;
    case 4:
        num2=3;
        backage[AMMO]++;
    default:
        break;
    }
    if(backage[WOOD]>=num1&&backage[STEEL]>=num2){
        backage[WOOD]-=num1;
        backage[STEEL]-=num2;
        printline("\n 制作中...\n");
        printline(progress_bar);
    }
    else{
        printline("\n 材料不足!\n",0,10);
    }
}


void basement(Player &p){
    while(1){
        system("cls");
        system("color 06");
        cout<<"+--------------------"<<endl;
        cout<<"| 治疗     : 按R键"<<endl;
        cout<<"+--------------------"<<endl;
        cout<<"| 制作武器 : 按M键"<<endl;
        cout<<"+--------------------"<<endl;
        cout<<"\n 按E键退出基地..."<<endl;
        char c=_getch();
        if(c=='r'||c=='R'){
            p.increaseHP(50);
            p.decrease_satiety(15);
            printline(progress_bar,100,60);
            printline("\n 生命值 +50");
            printline("\n 饱食度 -15\n");
        }
        else if(c=='m'||c=='M'){
            make_weapon();
        }
        else if(c=='j'||c=='J'){
            char w=showweapon(p);
            p.change_weapon(w);
        }
        else if(c=='e'||c=='E'){
            system("color 0A");
            break;
        }
    }
}


Zombie produce_zombies(int site){
    int i=rand()%10+1;
    int rate1=7,rate2=9;
    switch(site){
    case STORE:
        rate1=5;
        break;
    case FLAT:
        rate1=8;
        break;
    case CLINIC:
        rate1=4;
        break;
    case SCHOOL:
        rate1=8;
        break;
    case FACTORY:
        rate1=6;
        rate2=8;
        break;
    case STREET:
        rate1=9;
        rate2=10;
        break;
    default:
        break;
    }

    if(i<=rate1){
        i=NORMAL;
    }
    else if(i<=rate2){
        i=INFECTED;
    }
    else{
        i=GIANT;
    }
    Zombie z1(i);
    cout<<"\n 发现一只"<<z1.getZName()<<"!!!"<<endl;
    _sleep(500);
    return z1;
}


bool escape(int exp,int ztype){
    int rate1,rate2=60;
    int i=rand()%100+1;
    switch(ztype){
    case NORMAL:
        rate1=90;
        break;
    case INFECTED:
        rate1=50;
        break;
    case GIANT:
        rate1=80;
        break;
    default:
        break;
    }
    if(exp>=15&&exp<=30){
        rate2=70;
    }
    else{
        rate2=80;
    }
    int rate=rate1*rate2/100;
    if(i<=rate){
        return true;
    }
    return false;
}


void combat(Zombie z,Player &p){
    cout<<"\n 要逃跑吗? (Y/N)"<<endl;
    char choice=_getch();
    if(choice=='y'||choice=='Y'){
        if(escape(p.getExp(),z.getZType())){
            printline(escaped);
            return;
        }
        cout<<"\n 逃脱失败..."<<endl;
        _sleep(500);
    }
    while(1){
        system("cls");
        system("color 0A");
        showdata(p);
        cout<<"\n* 丧尸生命值: "<<z.getlife()<<endl;
        cout<<" 按F攻击丧尸..."<<endl;
        char c=_getch();
        if(c=='f'||c=='F'){
            z.decreaseHP(p.get_atk());
            p.decrease_satiety(2);
            cout<<"  丧尸生命值 -"<<p.get_atk()<<endl;
            if(z.getlife()<=0){
                printline(win);
                killed_num++;
                switch(z.getZType()){
                    case NORMAL:
                        p.addExp(5);
                        break;
                    case INFECTED:
                        p.addExp(10);
                        break;
                    case GIANT:
                        p.addExp(50);
                        break;
                    default:
                        break;
                }
                p.level_up();
                break;
            }
        }
        else if(c=='x'||c=='X'){
            showbag();
            cout<<" 输入序号以使用相应物品..."<<endl;
            cout<<" 若要关闭, 请输入0..."<<endl;
            char c=_getch();
            int choice=c-'0';
            p.eat(choice);
            continue;
        }
        else if(c=='j'||c=='J'){
            char w=showweapon(p);
            p.change_weapon(w);
            continue;
        }
        else{
            continue;
        }
        _sleep(500);
        system("cls");
        showdata(p);
        cout<<"\n* 丧尸生命值: "<<z.getlife()<<endl;
        int r=rand()%10+1,rate;
        switch(z.getZType()){
        case NORMAL:
            rate=7;
            break;
        case INFECTED:
            rate=9;
            break;
        case GIANT:
            rate=6;
            break;
        default:
            break;
        }
        if(r<=rate){
            p.decreaseHP(z.get_atk());
            system("color 04");
            cout<<"\n 被击中了! 生命值 -"<<z.get_atk()<<endl;
        }
        else{
            cout<<"\n 你躲开了攻击."<<endl;
        }
        _sleep(500);
        if(p.getlife()<=0){
            system("cls");
            printline(lose);
            break;
        }
    }
}

void detect(Player &p){
    int i=rand()%10+1;
    if(i<=6){
        cout<<"\n 安全..."<<endl;
        explore(p);
        p.decrease_satiety(1);
    }
    else{
        combat(produce_zombies(path[p.getx()]),p);
    }
}

int main(){
    system("title Suvivor(中文版)");
    int sum=0;
    srand(time(NULL));
    L1:
    system("color 0A");
    Player p1;
    while(1){
        
        showdata(p1);
        site(p1);
        printpath(p1);

        char c=_getch();
        if(c=='d'||c=='D'){
            cout<<" 前进! 继续探索..."<<endl;
            printline(forwards);
            p1.forward();
            p1.decrease_satiety(5);
            p1.starve(8);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(5);
            }
        }
        else if(c=='a'||c=='A'){
            cout<<" 后退...\n"<<backwards;
            _sleep(200);
            p1.backward();
            p1.decrease_satiety(2);
            p1.starve(5);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(4);
            }
        }
        else if(c=='g'||c=='G'){
            cout<<" 正在前往安全屋..."<<endl;
            printline(progress_bar);
            p1.setx();
            p1.decrease_satiety(10);
            p1.starve(10);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(6);
            }
        }
        else if(c=='z'||c=='z'){
            printline(e);
            detect(p1);
        }
        else if(c=='x'||c=='X'){
            showbag();
            cout<<" 输入序号以使用相应物品..."<<endl;
            cout<<" 若要关闭, 请输入0..."<<endl;
            char c=_getch();
            int choice=c-'0';
            p1.eat(choice);
        }
        else if(c=='b'||c=='B' && p1.getx()==0){
            basement(p1);
        }
        else if(c=='j'||c=='J'){
            char w=showweapon(p1);
            p1.change_weapon(w);
        }
        system("cls");
        if(p1.getlife()<=0){
            cout<<"\n ...按r键重来..."<<endl;
            char end=_getch();
            if(end=='r'||end=='R'){
                sum++;
                cout<<"\n 剩余重生机会: "<<2-sum<<"次..."<<endl;
                _sleep(500);
                if(sum==3){
                    break;
                }
                system("cls");
                goto L1;
            }
            else break;
        }
    }
    return 0;
}
