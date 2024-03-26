#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<string>
#include<ctime>
using namespace std;

class Sisyphus;

//巨石
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

//西西弗斯
class Sisyphus{
    public:
        Sisyphus(int lv=0,float s=50):level(lv),strength(s){};
        void level_up(){
            level++;
            strength+=50;
            system("cls");
            cout<<"=====LEVEL UP !!!=====\n"<<endl;
            cout<<"---Level "<<level-1<<" --> Level "<<level<<endl;
            cout<<"\n-----STRENGTH +50-----"<<endl;
            _sleep(1000);
        }
        int get_level(){return level;}
        float get_strenth(){return strength;}
        friend void weather(Stone &st,Sisyphus &si);
    private:
        int level;
        float strength;
};

//储存对话的字符串
string g1="Sisyphus, you're published to push a huge rock to the top of the mountain, and watch it fall over and over again!\n";
string g2="Okay, okay. Appendix: every time when the rock rolls back, a meaningless counter will tell you that you are moving up a level.\n";
string g3="More powerful strength and huger rock!\n";
string s1="Nooooo!!!\n";
string s3="What does an upgrade do for me?\n";
string s2="Wow!!!\n";
string end1="\n I'm  tired. ";
string end2=" Time  to  the  Eversleeping. \n";

//逐字输出对话
void printline(string s){
    _sleep(500);
    for(long long unsigned int i=0;i<s.length();i++){
        cout<<s[i];
        if(s[i]==' '||s[i]==','||s[i]=='.'){
            _sleep(50);
        }
        _sleep(40);
    }
    _sleep(500);
}

//游戏开始界面
void opening(){
    cout<<"+---------_/    \\------------+"<<endl;
    cout<<"|        /       \\_    .|.   |"<<endl;
    cout<<"|       /        / \\  --@--  |"<<endl;
    cout<<"|      S I S Y P H U S  |`   |"<<endl;
    cout<<"|    /_    / \\_/      \\      |"<<endl;
    cout<<"|  _/  \\  /   \\_       \\_    |"<<endl;
    cout<<"| /     \\/      \\_       \\   |"<<endl;
    cout<<"|/       \\        \\       \\  |"<<endl;
    cout<<"+----------------------------+"<<endl;
    cout<<"..Press any key to continue...\n"<<endl;
    _getch();
    system("cls");
}

//开场对话
void dialog(){
    //是否跳过对话
    cout<<"Skip conversation? Press s."<<endl;
    char c=_getch();
    system("cls");
    if(c=='s'||c=='S')return;
    system("color 0A");
    
    //对话内容输出
    cout<<"\nGods: ";
    printline(g1);
    cout<<"\nSisyphus: ";
    printline(s1);
    cout<<"\nGods: ";
    printline(g2);
    cout<<"\nSisyphus: ";
    printline(s2);
    cout<<"\nSisyphus: ";
    printline(s3);
    cout<<"\nGods: ";
    printline(g3);
    cout<<"\nSisyphus: ";
    printline(s2);
    
    cout<<"\nPress F to continue..."<<endl;
    _getch();
    system("cls");
}

//推石头进度条
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

//天气系统
enum Weather{SUNNY=0,CLOUDY,RAINY,WINDY};

void weather(Stone &st,Sisyphus &si){
    srand(time(NULL));
    int w=rand()%4;
    switch(w){
        case SUNNY:
            cout<<"\n Sunny toay.But too hot.\n"<<endl; 
            si.strength*=0.8; 
            system("color 04"); 
            break;
        case CLOUDY:
            cout<<"\n Cloudy.So many clouds, a mild day.\n"<<endl; 
            si.strength*=1.4; 
            system("color 07");
            break;
        case RAINY:
            cout<<"\n Rainy.The rain seems to flood the whole world.\n"<<endl; 
            st.weight*=1.1; 
            si.strength*=1.05;
            system("color 0B");
            break;
        case WINDY:
            cout<<"\n Windy.The wind is strong enough to tear everything apart.\n"<<endl; 
            si.strength*=0.85; 
            st.weight*=0.9; 
            system("color 06");break;
        default: break;
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
        
        //打印数据
        weather(yourlife,you);
        cout<<"+----------------------------"<<endl;
        cout<<"| Height          : "<<yourlife.getH()<<endl;
        cout<<"|----------------------------"<<endl;
        cout<<"| Remaining Height: "<<totalh-yourlife.getH()<<endl;
        cout<<"|----------------------------"<<endl;
        cout<<"| Stone's Weight  : "<<yourlife.getW()<<endl;
        cout<<"+----------------------------"<<endl;
        cout<<"| Current Level   : "<<you.get_level()<<endl;
        cout<<"|----------------------------"<<endl;
        cout<<"| Strength        : "<<you.get_strenth()<<endl;
        cout<<"+----------------------------"<<endl;
        cout<<"Press f to push the stone...\n"<<endl;

        //推石头
        char c=_getch();
        if(c=='f'){
            float l=you.get_strenth()/yourlife.getW();
            cout<<"...Push..."<<endl;
            push(l);
            yourlife.setH(you.get_strenth());
        }
        else if(c=='e'){
            system("cls");
            printline(end1);
            printline(end2);
            break;
        }

        //判断是否到达山顶
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
