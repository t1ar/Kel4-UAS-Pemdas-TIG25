// initial test
// Kel7
// TI-G

#include <iostream> //bla bla bla this is for testing merge files
#include <fstream>
#include <string>
using namespace std;


// declare harga
const int MAX = 9,
          Harga_User [MAX] = {},
          Harga_Seller [MAX] = {};


// declare struct
struct structItem {
    string Nama;
    int Jumlah;
} Item[MAX]; 

// declare functions

int Beli() {
    
}

void Menu(int pilihan) {

}
// main function
int main() {

    fstream profit, stock;
    int Money;   // Mr. Krabs : Money!
    string Nama_Item, Jumlah;
    profit.open("Profit.txt");
    profit >> Money; //get the line for MONEYYYYYY
    stock.open("Stock.txt"); //format Stock.txt = Nama Item\n Jumlah 
    for (int i = 0; i < MAX; i++) {
        getline(stock, Nama_Item);
        getline(stock, Jumlah);
        Item[i].Nama = Nama_Item;
        Item[i].Jumlah = stoi(Jumlah);
        cout << Item[i].Nama   << "   "<< i << endl;
        cout << Item[i].Jumlah << endl;
    }






    //dont forget to close file
    profit.close();
    stock.close();
}
