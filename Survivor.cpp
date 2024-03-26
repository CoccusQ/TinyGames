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
enum Item{WATER=1,BREAD,MEAT,WOOD,STEEL,AMMO,MEDICINE};

string forwards=" =>>>>>>>>>>>>>>";
string backwards=" <<============";
string progress_bar=" ################";
string name,search_result;

class Player{
    public:
        Player(int xx=0,int b=100):x(xx),bag(b){}
        void forward(){
            if(x+1>127){
                cout<<"Reach the border."<<endl;
                _sleep(500);
                return;
            }
            x++;
        }
        void backward(){
            if(x-1<0){
                cout<<"Reach the border."<<endl;
                _sleep(500);
                return;
            }
            x--;
        }
        int getx(){return x;}
        int setx(){x=0;return x;}
    private:
        int x;
        int bag;
};

//���ִ�ӡ�ַ���
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

//�����ͼ�����뱣��
void site(Player &p){
    int x=p.getx();
    path[0]=BASE;
    if(path[x]==0&&x!=0){
        path[x]=rand()%6+1;
    }
    cout<<"\n*";
    switch(path[x]){
    case STORE:
        cout<<" Store."<<endl;
        showpath[1][x]='M';
        break;
    case FLAT:
        cout<<" Residental Building."<<endl;
        showpath[1][x]='R';
        break;
    case CLINIC:
        cout<<" Clinic."<<endl;
        showpath[1][x]='+';
        break;
    case SCHOOL:
        cout<<" School."<<endl;
        showpath[1][x]='S';
        break;
    case FACTORY:
        cout<<" Factory."<<endl;
        showpath[1][x]='F';
        break;
    case STREET:
        cout<<" Street."<<endl;
        showpath[1][x]='_';
        break;
    case BASE:
        cout<<" Base. Your safe shelter."<<endl;
        showpath[1][x]='E';
        break;
    default:
        break;
    }
}

//��ӡ·��
void printpath(Player &p){
    int x=p.getx();
    showpath[0][x]='v';
    cout<<"\n    ";
    for(int i=0;path[i]!=0;i++){
        cout<<showpath[0][i]<<"  ";
    }
    cout<<"\n BAS";
    for(int i=0;path[i]!=0;i++){
        cout<<showpath[1][i]<<"__";
    }
    cout<<"..."<<endl;
    showpath[0][x]=' ';
}

//��ӡ��Ʒ��
string showname(int i){
    string name;
    switch (i){
    case WATER:
        name="Water";
        break;
    case BREAD:
        name="Bread";
        break;
    case MEAT:
        name="Canned Meat";
        break;
    case WOOD:
        name="Wood";
        break;
    case STEEL:
        name="Steel";
        break;
    case AMMO:
        name="Ammo";
        break;
    case MEDICINE:
        name="Medicine";
        break;
    default:
        break;
    }
    return name;
}

//̽������
void explore(Player &p){
    int i=rand()%7+1;
    int num=1;
    switch(path[p.getx()]){
    case STORE:
        if(i==WATER||i==BREAD||i==MEAT)num=5;
        break;
    case FLAT:
        if(i==WOOD||STEEL)num=3;
        break;
    case CLINIC:
        if(i==MEDICINE||i==WATER)num=4;
        break;
    case SCHOOL:
        if(i==WATER||i==BREAD)num=2;
        break;
    case FACTORY:
        if(i==WOOD||i==STEEL||i==AMMO)num=5;
        break;
    default:
        break;
    }
    backage[i]+=num;
    name=showname(i);
    string number=to_string(num);
    search_result=" Get "+name+" X"+number;
    printline(search_result);
    _sleep(500);
}

//��ʾ��������Ʒ
void showbag(){
    int sum=0;
    for(int i=1;i<=7;i++){
        if(backage[i]>0){
            cout<<"+----------------"<<endl;
            cout<<"| "<<showname(i)<<"  "<<backage[i]<<endl;
            sum++;
        }
    }
    if(sum==0){
        cout<<"\n Bag is empty..."<<endl;
        return;
    }
    cout<<"+----------------\n"<<endl;
    cout<<"\n Press any key to close..."<<endl;
    _getch();
}

int main(){
    srand(time(NULL));
    system("color 0A");
    Player p1;
    while(1){
        //��ʾ��ǰ����
        cout<<"+--------------------"<<endl;
        cout<<"| Position: X = "<<p1.getx()<<endl;
        cout<<"+--------------------"<<endl;
        
        //��ʾ��ͼʾ��ͼ
        site(p1);
        printpath(p1);

        //ִ�в���
        char c=_getch();
        if(c=='d'||c=='D'){
            cout<<"\n Go ahead. Explore..."<<endl;
            printline(forwards);
            p1.forward();
        }//��ǰ(����)̽��
        else if(c=='a'||c=='A'){
            cout<<"\n Go back...\n"<<backwards;
            _sleep(200);
            p1.backward();
        }//���(����)̽��
        else if(c=='g'||c=='G'){
            cout<<"\n Go back to the Base..."<<endl;
            printline(progress_bar);
            p1.setx();
        }//һ���ػ���
        else if(c=='z'||c=='z'){
            cout<<"\n Explore..."<<endl;
            explore(p1);
        }//̽����ǰ�ص�����
        else if(c=='x'||c=='X'){
            showbag();
        }//�鿴������Ʒ

        system("cls");
    }
    return 0;
}