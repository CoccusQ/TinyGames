#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<string>
#include<ctime>
using namespace std;

class Sisyphus;

class Stone{
    public:
        Stone(float h=0,int w=100):height(h),weight(w){};
        void clear(){height=0;}
        void setH(float strength){height+=strength/weight*50;}
        void setW(){weight+=50;}
        float getH(){return height;}
        int getW(){return weight;}
        friend void weather(Stone &st,Sisyphus &si);
    private:
        float height;
        int weight;
};

class Sisyphus{
    public:
        Sisyphus(int lv=0,float s=50):level(lv),strength(s){};
        void level_up(){
            level++;
            strength+=50;
            system("cls");
            cout<<"===== �ȼ�����!!!=====\n"<<endl;
            cout<<"---Level "<<level-1<<" --> Level "<<level<<endl;
            cout<<"\n----- ���� +50-----"<<endl;
            _sleep(1000);
        }
        int get_level(){return level;}
        float get_strenth(){return strength;}
        friend void weather(Stone &st,Sisyphus &si);
    private:
        int level;
        float strength;
};

string g1="������˹, �ҳͷ��㽫һ���ʯ����ɽ��, ��������һ����һ�εش�ɽ������! \n";
string g2="�ð�, �ð�. ��¼: ÿ��ʯͷ��������ʱ��, һ����������ļ���������ʾ������һ�� .\n";
string g3="��ǿ�������͸����ʯͷ! \n";
string s1="��!!!\n";
string s3="����������ʲô����?\n";
string s2="��Ŷ!!!\n";

void printline(string s){
    _sleep(500);
    for(long long unsigned int i=0;i<s.length();i++){
        cout<<s[i];
        if(s[i]==' '||s[i]==','||s[i]=='.'){
            _sleep(50);
        }
        _sleep(60);
    }
    _sleep(500);
}

void opening(){
    cout<<"+---------_/    \\------------+"<<endl;
    cout<<"|        /       \\_    .|.   |"<<endl;
    cout<<"|       /        / \\  --@--  |"<<endl;
    cout<<"|      ��  ��  ��  ˹   |`   |"<<endl;
    cout<<"|    /_    / \\_/      \\      |"<<endl;
    cout<<"|  _/  \\  /   \\_       \\_    |"<<endl;
    cout<<"| /     \\/      \\_       \\   |"<<endl;
    cout<<"|/       \\        \\       \\  |"<<endl;
    cout<<"+----------------------------+"<<endl;
    cout<<"..�밴���������...\n"<<endl;
    _getch();
    system("cls");
}

void dialog(){
    cout<<"�Ƿ������Ի�?��S������."<<endl;
    char c=_getch();
    system("cls");
    if(c=='s'||c=='S')return;
    cout<<"\n����: ";
    printline(g1);
    cout<<"\n������˹: ";
    printline(s1);
    cout<<"\n����: ";
    printline(g2);
    cout<<"\n������˹: ";
    printline(s2);
    cout<<"\n������˹: ";
    printline(s3);
    cout<<"\n����: ";
    printline(g3);
    cout<<"\n������˹: ";
    printline(s2);
    cout<<"\n�밴F������..."<<endl;
    _getch();
    system("cls");
    //system("color 0A");
}

void push(float sw){
    int t=(int)20/sw;
    for(int i=0;i<8;i++){
        for(int j=0;j<i;j++){
            cout<<'#';
            _sleep(t);
        }
        _sleep(t);
    }
}

enum Weather{SUNNY=0,CLOUDY,RAINY,WINDY};

void weather(Stone &st,Sisyphus &si){
    srand(time(NULL));
    int w=rand()%4;
    switch(w){
        case SUNNY:cout<<"\n �������ĵ�����.���ǹ�������.\n"<<endl; si.strength*=0.8; system("color 04"); break;
        case CLOUDY:cout<<"\n ����.��ˬ��һ��.\n"<<endl; si.strength*=1.45; system("color 07");break;
        case RAINY:cout<<"\n ����.��ˮ�·�Ҫ��û��������.\n"<<endl; st.weight*=1.1; si.strength*=1.05;system("color 0B") ;break;
        case WINDY:cout<<"\n �����.ǿ���Ŀ��,����˺���κζ���.\n"<<endl; si.strength*=0.85; st.weight*=0.9; system("color 06");break;
        default:break;
    }
}

int main(){
    Sisyphus you;
    Stone yourlife;
    float totalh=500;
    system("color 0B");
    opening();
    dialog();
    while(1){
        
        //print data
        weather(yourlife,you);
        cout<<"+-------------------------"<<endl;
        cout<<"| �߶�       : "<<yourlife.getH()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| ʣ��߶�   : "<<totalh-yourlife.getH()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| ��ʯ����   : "<<yourlife.getW()<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| ��ǰ�ȼ�   : "<<you.get_level()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| ����       : "<<you.get_strenth()<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"�밴F���ƶ���ʯ..."<<endl;

        //push the stone
        char c=_getch();
        if(c=='f'){
            float l=you.get_strenth()/yourlife.getW();
            cout<<"\n...Push..."<<endl;
            push(l);
            yourlife.setH(you.get_strenth());
        }

        //judge
        if(yourlife.getH()>=totalh){
            yourlife.clear();
            you.level_up();
            yourlife.setW();
        }
        _sleep(500);
        system("cls");
    }
    return 0;
}
