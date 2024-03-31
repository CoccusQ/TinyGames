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
int killed_num[4];
int achieve_list[10];
int search_times[128];

enum Site{STORE=1,FLAT,CLINIC,SCHOOL,FACTORY,STREET,BASE};
enum Item{WATER=1,BREAD,MEAT,MEDICINE,WOOD,STEEL,AMMO};
enum ZombieType{NORMAL=1,INFECTED,GIANT};
enum Weapon{PUNCH=1,STICK,KNIFE,GUN};

string forwards=" =>>>>>>>>>>>>>>";
string backwards=" <<============";
string progress_bar=" ################";
string e="������......\n";
string name,search_result;
string win="\n ��ɱ�ɹ�!!!";
string lose="\n ��ս����!!!";
string escaped="\n �ɹ�����!!!";


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
                cout<<"�ѵ���߽�."<<endl;
                _sleep(500);
                return;
            }
            x++;
        }
        void backward(){
            if(x-1<0){
                cout<<"�ѵ���߽�."<<endl;
                _sleep(500);
                return;
            }
            x--;
        }
        void eat(int i){
            if(i>=1&&i<=4){
                if(backage[i]<=0){
                    cout<<" ������û�и���Ʒ..."<<endl;
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
                cout<<"\n �������."<<endl;
                _sleep(1000);
            }
        }
        void increaseHP(int num){
            life+=num;
            if(life>100) life=100;
        }

        void decreaseHP(int atk){
            life-=atk;
            if(life<0) life=0;
        }

        void addExp(int num){exp+=num;}

        void addAtk(int num){atk+=num;}

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
                b_atk=20;
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
                    name="��ͨɥʬ";
                    break;
                case INFECTED:
                    life=60;
                    atk=8;
                    name="��Ⱦ��";
                    break;
                case GIANT:
                    life=180;
                    atk=20;
                    name="����ɥʬ";
                    break;
                default:
                    break;
            }
        }
        void level_up(Player &p){
            if(p.getExp()>=15){
                life+=10;
            }
            if(p.getExp()>=30){
                life+=10;
                atk+=5;
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
    cout<<"| λ�� X : "<<p1.getx()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| ����ֵ : "<<p1.getlife()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| ��ʳ�� : "<<p1.getsatiety()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| ����ֵ : "<<p1.getExp()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| ������ : "<<p1.get_atk()<<endl;
    cout<<"+--------------------"<<endl;
    cout<<"| ����   : "<<show_WeaponName(p1.get_weapontype())<<endl;
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
        cout<<" �̵�."<<endl;
        showpath[1][x]='M';
        break;
    case FLAT:
        cout<<" ����¥."<<endl;
        showpath[1][x]='R';
        break;
    case CLINIC:
        cout<<" ����."<<endl;
        showpath[1][x]='+';
        break;
    case SCHOOL:
        cout<<" ѧУ."<<endl;
        showpath[1][x]='S';
        break;
    case FACTORY:
        cout<<" ����."<<endl;
        showpath[1][x]='F';
        break;
    case STREET:
        cout<<" �ֵ�."<<endl;
        showpath[1][x]='_';
        break;
    case BASE:
        cout<<" ����. �㰲ȫ�ıӻ���."<<endl;
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
        name="ˮ";
        break;
    case BREAD:
        name="���";
        break;
    case MEAT:
        name="�����";
        break;
    case WOOD:
        name="ľ��";
        break;
    case STEEL:
        name="����";
        break;
    case AMMO:
        name="��ҩ";
        break;
    case MEDICINE:
        name="ҩƷ";
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
            name="��";
            break;
        case STICK:
            name="ľ��";
            break;
        case KNIFE:
            name="��";
            break;
        case GUN:
            name="��ǹ";
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
            i=STEEL;num=2;
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
    search_result=" ��� "+name+" X"+number;
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
        cout<<"(!)�������ǿյ�..."<<endl;
        return;
    }
    cout<<"+----------------\n"<<endl;
    cout<<" ���������ʹ����Ӧ��Ʒ..."<<endl;
}


void usebag(Player &p){
    while(1){
        system("cls");
        showbag();
        cout<<" <��X���رձ���...>"<<endl;
        char c=_getch();
        int choice=c-'0';
        if(c=='x'||c=='X'){
            return;
        }
        else{
            p.eat(choice);
        }
    }
}


int showweapon(Player &p){
    int sum=0;
    int choice=PUNCH;
    for(int i=2;i<=4;i++){
        if(myweapon[i]!=0){
            cout<<"+----------------"<<endl;
            cout<<"| "<<i<<"."<<show_WeaponName(i)<<"  "<<myweapon[i]<<endl;
            sum++;
        }
    }
    if(sum==0){
        cout<<"(!)û�пɸ���������..."<<endl;
        _sleep(500);
        return choice;
    }
    cout<<"+----------------"<<endl;
    cout<<"\n ���������ѡ������..."<<endl;
    char c=_getch();
    choice=c-'0';
    return choice;
}


void choose_weapon(Player &p){
    int w=showweapon(p);
    if(w!=STICK&&w!=KNIFE&&w!=GUN){
        cout<<"\n(!)��������ȷ�����!"<<endl;
    }
    if(w!=PUNCH&&myweapon[w]!=0){
        if(w==GUN&&backage[AMMO]<=0){
            cout<<"\n(!)��ҩ����!"<<endl;
        }
        p.change_weapon(w);
        printline("\n ���������ɹ�!\n");
    }
}


void make_weapon(){
    while(1){
        system("cls");
        int num1=0,num2=0;
        cout<<"\n=========================="<<endl;
        cout<<"| ʣ��ľ�� : "<<backage[WOOD]<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| ʣ����� : "<<backage[STEEL]<<endl;
        cout<<"==========================\n"<<endl;
        cout<<"=========================="<<endl;
        cout<<"| 1.ľ��: ľ�� X2"<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| 2.��  : ľ�� X3 ���� X4"<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| 3.ǹ  : ľ�� X2 ���� X10"<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| 4.��ҩ: ���� X1"<<endl;
        cout<<"=========================="<<endl;
        cout<<"\n ��������Ӧ�����������..."<<endl;
        cout<<" <��M���˳���������...>"<<endl;
        char c=_getch();
        int choice=c-'0';
        switch(choice){
        case 1:
            num1=2;
            myweapon[STICK]++;
            break;
        case 2:
            num1=3;num2=4;
            myweapon[KNIFE]++;
            break;
        case 3:
            num1=2;num2=10;
            myweapon[GUN]++;
            break;
        case 4:
            num2=1;
            backage[AMMO]++;
            break;
        case 'm'-'0':
            return;
        case 'M'-'0':
            return;
        default:
            cout<<"\n(!)��������ȷ���!"<<endl;
            _sleep(500);
            continue;
        }
        if(backage[WOOD]>=num1&&backage[STEEL]>=num2){
            backage[WOOD]-=num1;
            backage[STEEL]-=num2;
            printline("\n ������...\n");
            printline(progress_bar);
            printline("\n ���!\n",0);
        }
        else{
            printline("\n ���ϲ���!\n",0,10);
        }
    }
}


void basement(Player &p){
    while(1){
        system("cls");
        system("color 06");
        cout<<"====================="<<endl;
        cout<<"| ����     : ��R��  |"<<endl;
        cout<<"+-------------------+"<<endl;
        cout<<"| �������� : ��M��  |"<<endl;
        cout<<"+-------------------+"<<endl;
        cout<<"\n<��B���˳�����...>"<<endl;
        char c=_getch();
        if(c=='r'||c=='R'){
            if(p.getlife()<100&&p.getsatiety()>=15){
                p.increaseHP(50);
                p.decrease_satiety(15);
                cout<<"\n ��ʼ����..."<<endl;
                printline(progress_bar,100,60);
                printline("\n ����ֵ +50");
                printline("\n ��ʳ�� -15\n");
            }
            else if(p.getsatiety()==100){
                cout<<"\n(!)����ֵ����!"<<endl;
                _sleep(500);
            }
            else if(p.getsatiety()<15){
                cout<<"\n(!)��ʳ�ȹ���!"<<endl;
                _sleep(500);
            }
        }
        else if(c=='m'||c=='M'){
            make_weapon();
        }
        else if(c=='j'||c=='J'){
            choose_weapon(p);
        }
        else if(c=='b'||c=='B'){
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
    cout<<"\n ����һֻ"<<z1.getZName()<<"!!!"<<endl;
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
        rate1=60;
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

string ac0="\n ��ɳɾ�: ���羡ͷ--�����ͼ�ұ߽粢�Ѽ�����������\n";
string ac1="\n ��ɳɾ�: С��ţ��--��ɱһֻɥʬ\n";
string ac2="\n ��ɳɾ�: ɥʬɱ��--��ɱ��ֻɥʬ\n";
string ac3="\n ��ɳɾ�: �ݿ�����--��ɱʮֻɥʬ\n";
string ac4="\n ��ɳɾ�: ��Σ����--��ɱһֻ��Ⱦ��\n";
string ac5="\n ��ɳɾ�: ����η��--��ɱ��ֻ��Ⱦ��\n";
string ac6="\n ��ɳɾ�: �ռ�����--��ɱһֻ����ɥʬ\n";
//string ac7="\n ��ɳɾ�: ��Ϊ�ϲ�--������Ⱦ�ߺ�ɹ�����\n";

void achievement(Player &p){
    cout<<endl;
    if(search_times[127]>=3){
        printline(ac0);
        achieve_list[0]++;
        p.increaseHP(10000);
    }
    if(killed_num[0]==1&&achieve_list[1]==0){
        printline(ac1);
        achieve_list[1]++;
    }
    else if(killed_num[0]==5&&achieve_list[2]==0){
        printline(ac2);
        achieve_list[2]++;
    }
    else if(killed_num[0]==10&&achieve_list[3]==0){
        printline(ac3);
        achieve_list[3]++;
    }
    if(killed_num[INFECTED]==1&&achieve_list[4]==0){
        printline(ac4);
        achieve_list[4]++;
    }
    else if(killed_num[INFECTED]==3&&achieve_list[5]==0){
        printline(ac5);
        achieve_list[5]++;
    }
    if(killed_num[GIANT]==1&&achieve_list[6]==0){
        printline(ac6);
        achieve_list[6]++;
    }
    cout<<"\n ����:";
    explore(p);
}


void show_achievement(){
    int sum=0;
    system("cls");
    system("color 06");
    if(achieve_list[0]!=0){
        cout<<ac0;
        sum++;
    }
    if(achieve_list[1]!=0){
        cout<<ac1;
        sum++;
    }
    if(achieve_list[2]!=0){
        cout<<ac2;
        sum++;
    }
    if(achieve_list[3]!=0){
        cout<<ac3;
        sum++;
    }
    if(achieve_list[4]!=0){
        cout<<ac4;
        sum++;
    }
    if(achieve_list[5]!=0){
        cout<<ac5;
        sum++;
    }
    if(achieve_list[6]!=0){
        cout<<ac6;
        sum++;
    }
    if(sum==0) cout<<"\n(!)��ǰ�޳ɾ�..."<<endl;
    cout<<"\n<��������ر�...>"<<endl;
    _getch();
    system("color 0A");
}


void combat(Zombie z,Player &p){
    z.level_up(p);
    cout<<"\n Ҫ������? (Y/N)"<<endl;
    char choice=_getch();
    if(choice=='y'||choice=='Y'){
        if(escape(p.getExp(),z.getZType())){
            printline(escaped);
            return;
        }
        cout<<"\n ����ʧ��..."<<endl;
        _sleep(500);
    }
    while(1){
        system("cls");
        system("color 0A");
        showdata(p);
        cout<<"\n* ɥʬ����ֵ: "<<z.getlife()<<endl;
        cout<<" ��F����ɥʬ..."<<endl;
        char c=_getch();
        if(c=='f'||c=='F'){
            if(p.get_weapontype()==GUN){
                if(backage[AMMO]>=1) backage[AMMO]--;
                else p.change_weapon(PUNCH);
            }
            z.decreaseHP(p.get_atk());
            p.decrease_satiety(2);
            cout<<"  ɥʬ����ֵ -"<<p.get_atk()<<endl;
            if(z.getlife()<=0){
                printline(win);
                killed_num[0]++;
                killed_num[z.getZType()]++;
                achievement(p);
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
                p.change_weapon(p.get_weapontype());
                break;
            }
        }
        else if(c=='x'||c=='X'){
            usebag(p);
            continue;
        }
        else if(c=='j'||c=='J'){
            choose_weapon(p);
            continue;
        }
        else{
            continue;
        }
        _sleep(500);
        system("cls");
        showdata(p);
        cout<<"\n* ɥʬ����ֵ: "<<z.getlife()<<endl;
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
            cout<<"\n ��������! ����ֵ -"<<z.get_atk()<<endl;
        }
        else{
            cout<<"\n ��㿪�˹���."<<endl;
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
    if(search_times[p.getx()]>=3){
        cout<<"\n(!)�õص��Ѿ�û�п��Ѽ�������..."<<endl;
        _sleep(500);
        return;
    }
    if(i<=6){
        cout<<"\n ��ȫ..."<<endl;
        explore(p);
        p.decrease_satiety(1);
        search_times[p.getx()]++;
    }
    else{
        combat(produce_zombies(path[p.getx()]),p);
    }
}


void help_menu(){
    while(1){
        system("cls");
        system("color 0B");

        cout<<"=================="<<endl;
        cout<<"|      ���� "<<endl;
        cout<<"+-----------------"<<endl;
        cout<<"|  1.����˵��"<<endl;
        cout<<"|  2.��Ʒ˵��"<<endl;
        cout<<"|  3.ɥʬ˵��"<<endl;
        cout<<"|  4.������ʾ"<<endl;
        cout<<"=================="<<endl;
        cout<<"\n �����Ӧ��Ų鿴����..."<<endl;
        cout<<" <��H���˳�����...>"<<endl;

        char c=_getch();
        int choice=c-'0';

        switch(choice){
            case 1:
                cout<<"====================="<<endl;
                cout<<"|  ����--����˵�� "<<endl;
                cout<<"====================="<<endl;
                cout<<"|  ǰ��     : D"<<endl;
                cout<<"|  ����     : A"<<endl;
                cout<<"|  �ص����� : G"<<endl;
                cout<<"|  �򿪱��� : X"<<endl;
                cout<<"|  ����     : Z"<<endl;
                cout<<"|  �������� : J"<<endl;
                cout<<"|  ������� : B"<<endl;
                cout<<"|  �鿴�ɾ� : K"<<endl;
                cout<<"====================="<<endl;
                break;
            case 2:
                cout<<"\n==============================="<<endl;
                cout<<"|  ����--��Ʒ˵�� "<<endl;
                cout<<"==============================="<<endl;
                cout<<"|  ˮ     : ��ʳ��+2  ����ֵ+5"<<endl;
                cout<<"|  ���   : ��ʳ��+20 ����ֵ+2"<<endl;
                cout<<"|  ����� : ��ʳ��+12 ����ֵ+5"<<endl;
                cout<<"|  ҩƷ   : ����ֵ+20"<<endl;
                cout<<"==============================="<<endl;
                break;
            case 3:
                cout<<"\n==========================================="<<endl;
                cout<<"|  ����--ɥʬ����˵�� "<<endl;
                cout<<"==========================================="<<endl;
                cout<<"| ��ͨɥʬ : �������� Ѫ����   ���ѳɹ��ʸ�"<<endl;
                cout<<"| ��Ⱦ��   : �������� Ѫ���ϵ� ���ѳɹ��ʵ�"<<endl;
                cout<<"| ����ɥʬ : �������� Ѫ����   ���ѳɹ��ʸ�"<<endl;
                cout<<"==========================================="<<endl;
                break;
            case 4:
                cout<<"\n ������ʾ:"<<endl;
                cout<<" * ���һ������������, ����������õ����ʺ�̽���ĵ�ͼ,\n   ���Ǿ���ֵ�͹������ָ�����ʼ״̬"<<endl;
                cout<<" * ��ɱɥʬ�ɵþ���ֵ, ����ֵ�ۻ���һ������, ���������"<<endl;
                cout<<" * ������ľ�Ŀ������ڻ�������������"<<endl;
                cout<<" * ������ǰ�������˻�������, ���ή��һ���ı�ʳ��, ��ʳ\n   �Ƚ��͵�20���»Ỻ����������ֵ, ��ʳ����40�����ܻ���\n   �ָ�����ֵ"<<endl;
                cout<<" * ��ͬ�ص������ʺ�����ɥʬ�ĸ��ʲ�ͬ"<<endl;
                break;
            default:
                return;
        }
        cout<<"\n<�밴������ر�...>"<<endl;
        char exit=_getch();
        if(exit=='h'||exit=='H') return;
    }
}


void opening(){
    system("color 0B");
    cout<<"      _____"<<endl;
    cout<<"     /     \\"<<endl;
    cout<<"    | () () |"<<endl;
    cout<<"     \\  ^  /"<<endl;
    cout<<"      |||||"<<endl;
    cout<<"\n S U R V I V O R"<<endl;
    cout<<"\n <�밴�������ʼ>\n"<<endl;
    _getch();
    system("cls");
}

int main(){
    system("title Suvivor(���İ�)");
    int sum=0;
    srand(time(NULL));
    opening();
    L1:
    system("color 0A");
    Player p1;
    while(1){
        cout<<"<��H���鿴����...>"<<endl;
        showdata(p1);
        site(p1);
        printpath(p1);

        char c=_getch();
        if(c=='d'||c=='D'){
            cout<<" ǰ��! ����̽��..."<<endl;
            printline(forwards);
            p1.forward();
            p1.decrease_satiety(5);
            p1.starve(8);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(5);
            }
        }
        else if(c=='a'||c=='A'){
            cout<<" ����...\n"<<backwards;
            _sleep(200);
            p1.backward();
            p1.decrease_satiety(2);
            p1.starve(5);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(4);
            }
        }
        else if(c=='g'||c=='G'){
            cout<<" ����ǰ����ȫ��..."<<endl;
            printline(progress_bar);
            p1.setx();
            p1.decrease_satiety(10);
            p1.starve(10);
            if(p1.getlife()<100&&p1.getsatiety()>=40){
                p1.increaseHP(6);
            }
        }
        else if(c=='z'||c=='Z'){
            if(path[p1.getx()]!=BASE){
                printline(e);
                detect(p1);
            }
        }
        else if(c=='x'||c=='X'){
            usebag(p1);
        }
        else if(c=='b'||c=='B' && p1.getx()==0){
            basement(p1);
        }
        else if(c=='j'||c=='J'){
            choose_weapon(p1);
        }
        else if(c=='h'||c=='H'){
            help_menu();
            system("color 0A");
        }
        else if(c=='k'||c=='K'){
            show_achievement();
        }
        system("cls");
        if(p1.getlife()<=0){
            cout<<"\n ...��r������..."<<endl;
            char end=_getch();
            if(end=='r'||end=='R'){
                sum++;
                cout<<"\n ʣ����������: "<<2-sum<<"��..."<<endl;
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
