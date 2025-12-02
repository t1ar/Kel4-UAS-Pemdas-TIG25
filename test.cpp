// initial test
// Kel7
// TI-G

#include <iostream> // test commit
#include <fstream>
#include <string>
using namespace std;

// declare harga & duit
const int MAX = 9;
int Wallet = 20000;    //buyer's wallet
int Money, pilihan;   // Mr. Krabs : Money! | global var 
string Nama_Item, Jumlah, Harga;

// declare struct
struct structItem { 
    string Nama;
    int Jumlah;
    int Harga;
} Item[MAX], Storage[MAX]; //item dalam vending, storage dalam warehouse

void BuyStock(int pilihan) {
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    if (Money < Storage[pilihan].Harga){
        cout << "Not enough money.\n\n";
        return;
    }
    
    Item[pilihan].Jumlah++;
    Wallet -= Storage[pilihan].Harga;
    cout << "Restock completed.\nCurrent balance : " << Money;
}

// declare functions
void Restock(int pilihan) { // specific number of restock
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    cout << "Are you sure to restock " << Item[pilihan].Nama << "? (y/n) : ";
    char confirm;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Restock cancelled.\n\n";
        return;
    } //fajri, the nested-if fangirl
    if (Storage[pilihan].Nama != Item[pilihan].Nama) { //jri klo barangnya udah pasti sama, ga perlu di looping ber kali" dalam forloop
        cout << "Not matching in warehouse.\n\n";
        return;
    }  
        for(int i = 0; i <= 5; i++) {
            if (Item[pilihan].Jumlah == 5) { //check first, add later. in case vending machinenya udah penuh dari awal
                cout << "Vending machine full.\n\n";
                break; //use break instead of return
            }
            if (Storage[pilihan].Jumlah == 0) { 
                cout << "Out of stock.\n\n";
                return;
            }
            Storage[pilihan].Jumlah--;
            Item[pilihan].Jumlah++;           
        }
        cout << "Restock completed.\n\n";
}

void Beli(int pilihan) { //buy 1 item
    if (pilihan == 0) return;
    pilihan--; //due to how array works
    if (Item[pilihan].Jumlah == 0){
        cout << "No stock.\n\n";
        return;
    }
    if (Wallet < Item[pilihan].Harga){
        cout << "Not enough money.\n\n";
        return;
    }
    Item[pilihan].Jumlah--;
    Wallet -= Item[pilihan].Harga;
    cout << "Transaction completed.\nCurrent balance : " << Wallet;
}

void StockView(structItem arr[], char confirm){ //data is stored in struct not file, also needs confirmation whether u want to display price or not
    cout << "\n=== STOCK ===\n";
    for (int l = 0; l < MAX; l += 3) {
        // print names with index
        for (int j = l; j < (l + 3); ++j) {
            cout << "[" << j + 1 << "] " << arr[j].Nama << "\t" ;
        }
        cout << '\n';
        // print quantities
        for (int j = l; j < (l + 3); ++j) {
            cout << arr[j].Jumlah << " left\t\t\t";
        }
        if (confirm == 'y' || confirm == 'Y') { // 'y' || 'Y' for display, else for no
            cout << "\n";
            for (int j = l; j < (l + 3); ++j) {
                cout << arr[j].Harga << " left\t\t\t";
            }
        }
        cout << "\n\n";
    }
}                                        

void Pilih() {
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
        StockView(Item, 'y');
        Pilih();
        Beli(pilihan);
        break;
    case 2: //view profit
        cout << "Profit : " << Money << endl;
        Menu();
        break;
    case 3: //buystock
                //give entry message
        StockView(Storage, 'y');
        Pilih();

        break;
    case 4: //restock
        do {
                    //give entry message
            StockView(Storage, 'n');
            StockView(Item, 'n');
            Pilih();
            Restock(pilihan);
        } while (pilihan != 0);
        break;
    
    default:
        cout << "invalid menu" << endl;
        Menu();
        break;
    }
    //save file
    ofstream profit ("Profit.txt"), stock ("Stock.txt"), warehouse ("Storage.txt"); //save data after each menu
    profit << Money;
    profit.close();
    for (int i = 0; i < MAX; i++) {
        stock << Item[i].Nama << endl << Item[i].Jumlah << endl << Item[i].Harga << endl;
    }
    stock.close();
    for (int i = 0; i < MAX; i++) {
        warehouse << Storage[i].Nama << endl << Storage[i].Jumlah << endl << Storage[i].Harga << endl;
    }
    warehouse.close();
    Menu(); //recursive
}

void read(structItem arr[], ifstream &yap) {
    for (int i = 0; i < MAX; i++) {
        getline(yap, Nama_Item);//format .txt    =   Nama Item\n 
        getline(yap, Jumlah);   //                   Jumlah\n
        getline(yap, Harga);    //                   Harga\n
        arr[i].Nama = Nama_Item;
        arr[i].Jumlah = stoi(Jumlah);
        arr[i].Harga = stoi(Harga);
    }
}

// main function
int main() {
    ifstream profit ("Profit.txt"), stock ("Stock.txt"), warehouse ("Storage.txt"); // initialize data from file, Money for profit, structItem for stock,
    profit >> Money; //get the line for MONEYYYYYY
    profit.close();
    read(Item, stock);
    stock.close();
    read(Storage, warehouse);
    warehouse.close();
    
    Menu();

                //give exit message
    
}
