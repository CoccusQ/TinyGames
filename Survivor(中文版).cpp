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

enum Site{STORE=1,FLAT,CLINIC,SCHOOL,FACTORY,STREET,BASE};
enum Item{WATER=1,BREAD,MEAT,MEDICINE,WOOD,STEEL,AMMO};
enum ZombieType{NORMAL=1,INFECTED,GIANT};

string forwards=" =>>>>>>>>>>>>>>";
string backwards=" <<============";
string progress_bar=" ################";
string e="搜索中........\n";
string name,search_result;
string win="\n 击杀成功!!!";
string lose="\n 你战死了!!!";

class Player{
    public:
        Player(int xx=0,int bg=100,int sty=100,int lf=100,int attk=5):x(xx),bag(bg),satiety(sty),life(lf),atk(attk){}
        int setx(){x=0;return x;}
        int getx(){return x;}
        int getsatiety(){return satiety;}
        int getlife(){return life;}
        int get_atk(){return atk;}
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
                    life+=15;
                    break;
                default:
                    break;
            }
            if(life>100) life=100;
            if(satiety>100) satiety=100;
        }
        void decrease_satiety(int num){
            if(satiety>0){
                satiety-=num;
            }
            if(satiety<0){
                satiety=0;
            }
        }
        char starve(int num){
            if(satiety<=20&&life>0){
                life-=num;
            }
            if(life<=0){
                life=0;
                system("cls");system("color 04");
                cout<<"\n 你饿死了."<<endl;
                _sleep(1000);
                cout<<"\n按r键重来..."<<endl;
                char c=_getch();
                return c;
            }
            return 0;
        }
        void decreaseHP(int atk){life-=atk;}
    private:
        int x;
        int bag;
        int satiety;
        int life;
        int atk;
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
                    life=80;
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


void showdata(Player &p1){
    cout<<"+--------------------"<<endl;
    cout<<"| 位置 X : "<<p1.getx()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 生命值 : "<<p1.getlife()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| 饱食度 : "<<p1.getsatiety()<<endl;
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


void explore(Player &p){
    int i=rand()%6+1;
    int num=1;
    switch(path[p.getx()]){
    case STORE:
        if(i==WATER||i==BREAD||i==MEAT)num=5;
        if(i==MEDICINE) i=WATER;
        break;
    case FLAT:
        if(i==WOOD||i==STEEL)num=3;
        break;
    case CLINIC:
        if(i==MEDICINE||i==WATER)num=4;
        break;
    case SCHOOL:
        if(i==WATER||i==BREAD)num=2;
        break;
    case FACTORY:
        if(i==WOOD||i==STEEL)num=5;
        else if(i==MEAT||i==BREAD){
            i=AMMO;num=5;
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


Zombie produce_zombies(){
    int i=rand()%10+1;
    if(i<=7){
        i=NORMAL;
    }
    else if(i<=9){
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


void combat(Zombie z,Player &p){
    cout<<" 拿起武器, 击败丧尸!!!"<<endl;
    char c;
    while(1){
        system("cls");
        system("color 0A");
        showdata(p);
        cout<<"\n* 丧尸生命值: "<<z.getlife()<<endl;
        cout<<" 按F攻击丧尸..."<<endl;
        c=_getch();
        if(c=='f'||c=='F'){
            int life=z.decreaseHP(p.get_atk());
            p.decrease_satiety(2);
            cout<<"  丧尸生命值 -"<<p.get_atk()<<endl;
            if(z.getlife()<=0){
                printline(win);
                break;
            }
        }
        else{
            cout<<" 攻击失败..."<<endl;
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
        combat(produce_zombies(),p);
    }
}

int main(){
    srand(time(NULL));
    L1:
    system("color 0A");
    Player p1;
    while(1){
        
        showdata(p1);
        site(p1);
        printpath(p1);

        char end;
        char c=_getch();
        if(c=='d'||c=='D'){
            cout<<" 前进! 继续探索..."<<endl;
            printline(forwards);
            p1.forward();
            p1.decrease_satiety(5);
            end=p1.starve(8);
        }
        else if(c=='a'||c=='A'){
            cout<<" 后退...\n"<<backwards;
            _sleep(200);
            p1.backward();
            p1.decrease_satiety(2);
            end=p1.starve(5);
        }
        else if(c=='g'||c=='G'){
            cout<<" 正在前往安全屋..."<<endl;
            printline(progress_bar);
            p1.setx();
            p1.decrease_satiety(10);
            end=p1.starve(10);
        }
        else if(c=='z'||c=='z'){
            printline(e);
            detect(p1);
            end=p1.starve(2);
        }
        else if(c=='x'||c=='X'){
            showbag();
            cout<<" 输入序号以使用相应物品..."<<endl;
            cout<<" 若要关闭, 请输入0..."<<endl;
            end=_getch();
            int choice=end-'0';
            p1.eat(choice);
        }
        system("cls");
        if(end=='r'||end=='R'){
            goto L1;
        }
    }
    return 0;
}
