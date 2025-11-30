// initial test
// Kel7
// TI-G

#include <iostream>
#include <fstream> // ubah oi ubahhhh
#include <string>
using namespace std;


// declare harga
const int MAX = 9,
          Harga_Buyer [MAX] = {},
          Harga_Stock [MAX] = {};

int Wallet = 20000;

// declare struct
struct structItem {
    string Nama;
    int Jumlah;
} Item[MAX]; 

// declare functions


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

}
// main function
int main() {

    fstream profit, stock;
    int Money;   // Mr. Krabs : Money!
    string Nama_Item, Jumlah;
    profit.open("Profit.txt");
    profit >> Money; //get the line for MONEYYYYYY
    profit.close();  //dont forget to close file
    stock.open("Stock.txt");  
    for (int i = 0; i < MAX; i++) {
        getline(stock, Nama_Item);//format Stock.txt = Nama Item\n 
        getline(stock, Jumlah);   //                   Jumlah
        Item[i].Nama = Nama_Item;
        Item[i].Jumlah = stoi(Jumlah);
    } //dont forget to close file
    stock.close();
}
