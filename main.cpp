#include<conio.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
using namespace std;
int accbuf;
string pass ="";
void password(){
    cout<<"Enter the PASSWORD to verify that you are an ADMINISTRATOR :\n";
    char ch;
    ch = _getch();
   while(ch != 13){//character 13 is enter
      pass.push_back(ch);
      cout<< '*';
      ch = _getch();
   }
}
class Bank{
    long accno;
    float amount;   char type;
public:
    char name[30];
    void input(){
        char sel;
        repeat:
        cout<<"Enter the Account Number : ";   cin>>accno; cout<<"Accno : "<<accno<<endl;
        cout<<"Enter Name of the Account Holder : ";  cin.ignore(); cin.getline(name,30);
        cout<<"Enter Type of the Account (Savings(s)/Checking(c)) : ";   cin>>type;
        cout<<"Enter the Initial Amount :\n>=500 for Savings &>=1000 for Checking : ";  cin>>amount;
        if(type=='s'||type=='S'){
            if(amount<=500){
                cout<<"Invalid Amount for Savings Account!\nTRY AGAIN!!"<<endl;
                goto repeat;
                }
        }
        else if(type=='c'||type=='C'){
            if(amount<=1000){
                cout<<"Invalid Amount for Checking Account!\nTRY AGAIN!!"<<endl;
                goto repeat;
                }
        }
    }
    long getaccno(){
        return accno;
    }
    float getamt(){
        return amount;
    }
    float dep_amount(float a){
        amount+=a;
    }
    float wd_amount(float a){
        amount-=a;
    }
};
Bank x,y;

void new_account(){
    pass ="";
    password();
    if(pass == "compbank"){
      cout<< "\nAccess granted \n";
      cout<<"**********NEW ACCOUNT**********\n\n";
      repeat_entry:
        ofstream fout("Bank.dat",ios::app);
        cout<<"Enter details for the NEW ACCOUNT : "<<endl;
        x.input();
        ifstream fin("Bank.dat");
        while(!fin.eof()){
            fin.read((char*)&y,sizeof(Bank));
            long accbuf1=y.getaccno();
            long accbuf2=x.getaccno();
            if(accbuf1==accbuf2){
                cout<<"CONFLICTING ACCOUNT NUMBERS! TRY AGAIN!"<<endl;
                goto repeat_entry;
            }
        fin.close();
        fout.write((char*)&x,sizeof(Bank));
        fout.close();
        }
   }
   else{
      cout<< "\nAccess Denied\n";
   }
}
void deposit_amount(){
    pass ="";
    password();
    if(pass == "compbank"){
        cout<< "\nAccess granted \n";
        cout<<"**********DEPOSIT AMOUNT**********\n\n";
        float dep_amt; long accno,buffer;
        ofstream fout("temp.dat",ios::app);
        cout<<"Enter the Account Number to deposit the amount to : ";   cin>>accno;
        ifstream fin("Bank.dat",ios::in);
        while(!fin.eof()){
            fin.read((char*)&x,sizeof(Bank));
            long accbuf=x.getaccno();
            if(accno==accbuf){
                if(buffer==accbuf)  goto over;
                cout<<"Enter the Amount to deposit : "; cin>>dep_amt;
                x.dep_amount(dep_amt);
                cout<<"DEPOSITED "<<dep_amt<<" to "<<x.name<<"'s Account"<<endl;
                fout.write((char*)&x,sizeof(Bank));
                over:
                buffer=accbuf;
            }
            else
                fout.write((char*)&x,sizeof(Bank));
        }
        cout<<"\n\n";
        fout.close();
        fin.close();
        remove("Bank.dat");
        rename("Temp.dat","Bank.dat");
        cout<<"\n\n";
    }
    else
        cout<<"\nACCESS DENIED"<<endl;
}
void withdraw_amount(){
    pass ="";
    password();
    if(pass == "compbank"){
        cout<< "\nAccess granted \n";
        cout<<"**********WITHDRAW AMOUNT**********\n\n";
        float wd_amt; long accno,buffer;
        ofstream fout("temp.dat",ios::app);
        cout<<"Enter the Account Number to withdraw the amount from : ";    cin>>accno;
        ifstream fin("Bank.dat",ios::in);
        while(!fin.eof()){
            fin.read((char*)&x,sizeof(Bank));
            long accbuf=x.getaccno();
            if(accno==accbuf){
                if(buffer==accbuf)  goto over2;
                cout<<"Enter the Amount to withdraw : "; cin>>wd_amt;
                x.wd_amount(wd_amt);
                cout<<"WITHDRAWED "<<wd_amt<<" from "<<x.name<<"'s Account"<<endl;
                fout.write((char*)&x,sizeof(Bank));
            over2:
                buffer=accno;
            }
            else
                fout.write((char*)&x,sizeof(Bank));
        }

        cout<<"\n\n";
        fout.close();
        fin.close();
        remove("Bank.dat");
        rename("Temp.dat","Bank.dat");
        cout<<"\n\n";
    }
    else
        cout<<"\nACCESS DENIED"<<endl;
}
void balance(){
        cout<<"\n\n"<<"**********BALANCE ENQURIY**********"<<"\n\n";
        long accno; char namebuf[30];
        cout<<"Enter the Account Number to check its Balance : ";   cin>>accno;
        ifstream fin("Bank.dat",ios::in);
        while(!fin.eof()){
            fin.read((char*)&x,sizeof(Bank));
            long accbuf=x.getaccno();
            if(accno==accbuf){
                float bal=x.getamt();
                cout<<"Account Balance is : "<<bal<<endl;
                goto end_of_balance;
            }
        }
        end_of_balance:
        fin.close();

}
void account_holders() {
    cout<<"\n\n**********ACCOUNT HOLDERS**********\n\n";
    ifstream fin("Bank.dat",ios::in); int counter=1; long accno,buffer;
    while(!fin.eof()){
        fin.read((char*)&x,sizeof(Bank));
        accno=x.getaccno();
        if(buffer==accno)
            goto endofloop;
        cout<<counter<<". "<<x.name<<endl;
        counter++;
            endofloop:
                buffer=accno;
                ;
    }
    cout<<"\n\n";
    fin.close();
}
void modify_account() {
    pass ="";
    password();
    if(pass == "compbank"){
        cout<< "\nAccess granted \n";
        cout<<"**********ACCOUNT MODIFIER**********\n\n";
        long accno,dummy=0; char namebuf[30];
        ofstream fout("temp.dat",ios::app);
        cout<<"Enter the Account Number to MODIFY its contents : ";   cin>>accno;
        ifstream fin("Bank.dat",ios::in);
        while(!fin.eof()){
            fin.read((char*)&x,sizeof(Bank));
            if(x.getaccno()==dummy)
                goto end_of_modify;
            long accbuf=x.getaccno();
            if(accno==accbuf){
                cout<<"Enter the new details : "<<endl;
                x.input();
                dummy=x.getaccno();
                fout.write((char*)&x,sizeof(Bank));
            }
            else{
                fout.write((char*)&x,sizeof(Bank));
                dummy=x.getaccno();
            }
        }
        end_of_modify:
        cout<<"\n\n";
        fout.close();
        fin.close();
        remove("Bank.dat");
        rename("Temp.dat","Bank.dat");
        cout<<"\n\n";
    }
    else
        cout<<"\nACCESS DENIED"<<endl;
}
void close_account() {
    pass ="";
    password();
    if(pass == "compbank"){
        cout<< "\nAccess granted \n";
        cout<<"**********ACCOUNT CLOSER**********\n\n";
        long accno,buffer;   int counter=0;
    ofstream fout("temp.dat",ios::out);
    cout<<"Enter the Account Number to Close The Account : ";    cin>>accno;
    ifstream fin("Bank.dat",ios::in);
    while(!fin.eof()){
        fin.read((char*)&x,sizeof(Bank));
        long accbuf=x.getaccno();
        if(accno==accbuf){
            if(buffer==accno)
                goto end_of_loop;
            char ch;
            cout<<"Are you sure ? (y/n) "; cin>>ch;
            if(ch=='y'||ch=='Y'){
                cout<<"CLOSED THE ACCOUNT"<<endl;
                counter++;
            }
            else{
                fout.write((char*)&x,sizeof(Bank));
                counter++;
            }
            end_of_loop:
                buffer=accno;
                    ;
        }
        else
            fout.write((char*)&x,sizeof(Bank));
    }
    cout<<"\n\n";
    fin.close();
    fout.close();
    remove("Bank.dat");
    rename("Temp.dat","Bank.dat");
    cout<<"\n\n";
    }
    else
        cout<<"\nACCESS DENIED"<<endl;
}
int main(){
    char art1[]=" $$$$$$\\     $$$$$\\  $$$$$$\\  $$\\   $$\\       \n$$  __$$\\    \\__$$ |$$  __$$\\ $$ |  $$ |      \n$$ /  $$ |      $$ |$$ /  $$ |\\$$\\ $$  |      \n$$$$$$$$ |      $$ |$$$$$$$$ | \\$$$$  /       \n$$  __$$ |$$\\   $$ |$$  __$$ | $$  $$<        \n$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  /\\$$\\       \n$$ |  $$ |\\$$$$$$  |$$ |  $$ |$$ /  $$ |      \n\\__|  \\__| \\______/ \\__|  \\__|\\__|  \\__|      \n                                              \n                                              \n                                              \n\n";
    char art2[]="$$\\   $$\\  $$$$$$\\ $$$$$$$$\\ $$$$$$\\  $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$\\       \n$$$\\  $$ |$$  __$$\\\\__$$  __|\\_$$  _|$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$ |      \n$$$$\\ $$ |$$ /  $$ |  $$ |     $$ |  $$ /  $$ |$$$$\\ $$ |$$ /  $$ |$$ |      \n$$ $$\\$$ |$$$$$$$$ |  $$ |     $$ |  $$ |  $$ |$$ $$\\$$ |$$$$$$$$ |$$ |      \n$$ \\$$$$ |$$  __$$ |  $$ |     $$ |  $$ |  $$ |$$ \\$$$$ |$$  __$$ |$$ |      \n$$ |\\$$$ |$$ |  $$ |  $$ |     $$ |  $$ |  $$ |$$ |\\$$$ |$$ |  $$ |$$ |      \n$$ | \\$$ |$$ |  $$ |  $$ |   $$$$$$\\  $$$$$$  |$$ | \\$$ |$$ |  $$ |$$$$$$$$\\ \n\\__|  \\__|\\__|  \\__|  \\__|   \\______| \\______/ \\__|  \\__|\\__|  \\__|\\________|\n                                                                             \n                                                                             \n                                                                             \n\n";
    char art3[]="$$$$$$$\\   $$$$$$\\  $$\\   $$\\ $$\\   $$\\ \n$$  __$$\\ $$  __$$\\ $$$\\  $$ |$$ | $$  |\n$$ |  $$ |$$ /  $$ |$$$$\\ $$ |$$ |$$  / \n$$$$$$$\\ |$$$$$$$$ |$$ $$\\$$ |$$$$$  /  \n$$  __$$\\ $$  __$$ |$$ \\$$$$ |$$  $$<   \n$$ |  $$ |$$ |  $$ |$$ |\\$$$ |$$ |\\$$\\  \n$$$$$$$  |$$ |  $$ |$$ | \\$$ |$$ | \\$$\\ \n\\_______/ \\__|  \\__|\\__|  \\__|\\__|  \\__|\n                                        \n                                        \n                                        \n\n";
    cout<<art1<<art2<<art3;
    menu:
    cout<<"**********BANKING SYSTEM**********\n\n";
    cout<<"-----MAIN MENU-----\n";
    cout<<"1. New Account\n";
    cout<<"2. Deposit Amount\n";
    cout<<"3. Withdraw Amount\n";
    cout<<"4. Balance Enquiry\n";
    cout<<"5. All Account Holders List\n";
    cout<<"6. Close an Account\n";
    cout<<"7. Modify Account\n";
    cout<<"--Any Other Key to Exit--\n\n\n";
    int n;  cin>>n;
    switch(n){
        case 1: new_account();
        goto menu;
        case 2: deposit_amount();
        goto menu;
        case 3: withdraw_amount();
        goto menu;
        case 4: balance();
        goto menu;
        case 5:account_holders();
        goto menu;
        case 6:close_account();
        goto menu;
        case 7:modify_account();
        goto menu;
    }
    return 0;
}


