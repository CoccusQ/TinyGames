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
            cout<<"===== 等级提升!!!=====\n"<<endl;
            cout<<"---Level "<<level-1<<" --> Level "<<level<<endl;
            cout<<"\n----- 力量 +50-----"<<endl;
            _sleep(1000);
        }
        int get_level(){return level;}
        float get_strenth(){return strength;}
        friend void weather(Stone &st,Sisyphus &si);
    private:
        int level;
        float strength;
};

string g1="西西弗斯, 我惩罚你将一块巨石推上山顶, 并看着它一次又一次地从山顶滚落! \n";
string g2="好吧, 好吧. 附录: 每次石头滚回来的时候, 一个毫无意义的计数器会提示你升了一级 .\n";
string g3="更强的力量和更大的石头! \n";
string s1="不!!!\n";
string s3="升级对我有什么用吗?\n";
string s2="哇哦!!!\n";

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
    cout<<"|      西  西  弗  斯   |`   |"<<endl;
    cout<<"|    /_    / \\_/      \\      |"<<endl;
    cout<<"|  _/  \\  /   \\_       \\_    |"<<endl;
    cout<<"| /     \\/      \\_       \\   |"<<endl;
    cout<<"|/       \\        \\       \\  |"<<endl;
    cout<<"+----------------------------+"<<endl;
    cout<<"..请按任意键继续...\n"<<endl;
    _getch();
    system("cls");
}

void dialog(){
    cout<<"是否跳过对话?按S键跳过."<<endl;
    char c=_getch();
    system("cls");
    if(c=='s'||c=='S')return;
    cout<<"\n诸神: ";
    printline(g1);
    cout<<"\n西西弗斯: ";
    printline(s1);
    cout<<"\n诸神: ";
    printline(g2);
    cout<<"\n西西弗斯: ";
    printline(s2);
    cout<<"\n西西弗斯: ";
    printline(s3);
    cout<<"\n诸神: ";
    printline(g3);
    cout<<"\n西西弗斯: ";
    printline(s2);
    cout<<"\n请按F键继续..."<<endl;
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
        case SUNNY:cout<<"\n 阳光明媚的晴天.但是过于炎热.\n"<<endl; si.strength*=0.8; system("color 04"); break;
        case CLOUDY:cout<<"\n 多云.凉爽的一天.\n"<<endl; si.strength*=1.45; system("color 07");break;
        case RAINY:cout<<"\n 雨天.雨水仿佛要淹没整个世界.\n"<<endl; st.weight*=1.1; si.strength*=1.05;system("color 0B") ;break;
        case WINDY:cout<<"\n 起风了.强劲的狂风,足以撕裂任何东西.\n"<<endl; si.strength*=0.85; st.weight*=0.9; system("color 06");break;
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
        cout<<"| 高度       : "<<yourlife.getH()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| 剩余高度   : "<<totalh-yourlife.getH()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| 巨石重量   : "<<yourlife.getW()<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"| 当前等级   : "<<you.get_level()<<endl;
        cout<<"|-------------------------"<<endl;
        cout<<"| 力量       : "<<you.get_strenth()<<endl;
        cout<<"+-------------------------"<<endl;
        cout<<"请按F键推动巨石..."<<endl;

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
