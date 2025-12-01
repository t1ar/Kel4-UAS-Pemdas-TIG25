// initial test
// Kel7
// TI-G

#include <iostream>
#include <fstream> // ubah oi ubahhhh
#include <string>
using namespace std;


// declare harga & duit
const int MAX = 9,
          Harga_Buyer [MAX] = {},
          Harga_Stock [MAX] = {};

int Wallet = 20000; //buyer's wallet
int Money;   // Mr. Krabs : Money! | global var 

// declare struct
struct structItem {
    string Nama;
    int Jumlah;
} Item[MAX]; 


// declare functions

void viewStock(){ //data is stored in struct not file remember, oh and at the bottom give the line "0. Exit" 
                 
    


    cout << "\nPilih barang : "; //use this at the end of funct
}

void Restock(int pilihan) { //specific number of restock
    if (pilihan == 0) return;
    pilihan--; //due to how array works




}

void Beli(int pilihan) {
    pilihan--;
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
}

void Menu() {
    int pilihan;
                 //entry message
                 //user's wallet


    cin >> pilihan;
    switch (pilihan)
    {
    case 0: //exit
        return;
        break;
    case 1: //buy
        viewStock();
        cin >> pilihan;
        Beli(pilihan);
        break;
    case 2: //view profit
        cout << "Profit : " << Money << endl;
        Menu();
        break;
    case 3: //restock
        do {
            do {
                viewStock();
                cin >> pilihan;
                if (pilihan < 0 || pilihan > MAX) cout << "Invalid\n"; //countermeasure
            } while (pilihan < 0 || pilihan > MAX);
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
