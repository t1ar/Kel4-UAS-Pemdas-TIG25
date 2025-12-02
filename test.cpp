// initial test
// Kel7
// TI-G

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// declare harga & duit
const int MAX = 9,
          Harga_Buyer [MAX] = {},
          Harga_Stock [MAX] = {};
int Wallet = 20000; //buyer's wallet
int Money, pilihan;   // Mr. Krabs : Money! | global var 

// declare struct
struct structItem {
    string Nama;
    int Jumlah;
} Item[MAX]; 

// declare functions
void Restock(int pilihan) 
{ //specific number of restock
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works




}

void Beli(int pilihan) { //buy 1 item
    if (pilihan == 0) return;
    pilihan--; //due to how array works
    if (Item[pilihan].Jumlah == 0){
        cout << "No stock.\n\n";
        return;
    }
    if (Wallet < Harga_Buyer[pilihan]){
        cout << "Not enough money.\n\n";
        return;
    }
    Item[pilihan].Jumlah--;
    Wallet -= Harga_Buyer[pilihan];
    cout << "Transaction completed.\nCurrent balance : " << Money;
}

void StockPilih(){ //data is stored in struct not file remember, oh and at the bottom give the line "0. Exit" ;
                                                                   
                        //give the format like  [1]Name  [2]Name  [3]Name
                        //                       5 left   4 left   2 left 

                        //                      [4]Name  [5]Name  [6]Name
                        //                       3 left   2 left   1 left  

                        //                      [7]Name  [8]Name  [9]Name
                        //                       2 left   4 left   3 left  kinda like an actual vending machine
                                               

    
    cout << "\n0.Exit";
    do { //pilih
        cout << "\nPilih barang : ";
        cin >> pilihan;
        if (pilihan < 0 || pilihan > MAX) cout << "\nInvalid\n"; //countermeasure
    } while (pilihan < 0 || pilihan > MAX);
}

void Menu() {
                 //give entry message
                 //user's wallet


    cin >> pilihan;
    switch (pilihan)
    {
    case 0: //exit
        return;
        break;
    case 1: //buy
                    //give entry message
        StockPilih();
        Beli(pilihan);
        break;
    case 2: //view profit
        cout << "Profit : " << Money << endl;
        Menu();
        break;
    case 3: //restock
        do {
                    //give entry message
            StockPilih();
            Restock(pilihan);
        } while (pilihan != 0);
        break;
    default:
        cout << "invalid menu" << endl;
        Menu();
        break;
    }
    ofstream profit ("Profit.txt"), stock ("Stock.txt"); //save data after each menu
    profit << Money;
    profit.close();
    for (int i = 0; i < MAX; i++) {
        stock << Item[i].Nama << endl << Item[i].Jumlah << endl;
    }
    stock.close();
    Menu(); //recursive
}
// main function
int main() {
    // initialize data from file, Money for profit, structItem for stock
    ifstream profit, stock;
    string Nama_Item, Jumlah;
    profit.open("Profit.txt");
    profit >> Money; //get the line for MONEYYYYYY
    profit.close();
    stock.open("Stock.txt");  
    for (int i = 0; i < MAX; i++) {
        getline(stock, Nama_Item);//format Stock.txt = Nama Item\n 
        getline(stock, Jumlah);   //                   Jumlah
        Item[i].Nama = Nama_Item;
        Item[i].Jumlah = stoi(Jumlah);
    }
    stock.close();

    Menu();

                //give exit message
    
}
