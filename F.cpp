// Markino Samuels
// Project FINAL
// 

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <ctime>
#include <fstream>
#include <locale>
#include <sstream>
#include <stack> 

using namespace std;
#define hash_max 1000
#define inventory_max 500 
#define cart_max 20

void Menu()
{
    cout << endl << endl;
    string Cmd[11] = 
    {
    "                           MAIN MENU",
    "+------------------------------------------------------------------+",
    "|",
    "|  1)  Edit inventory ",
    "|  2)	Edit account Record ",
    "|  3)	Shop ",
    "|  4)	Print invoice(s) ",
    "|",
    "|  5)  Exit sales ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<11;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// main menu

void Edit_inventory_menu()
{
    cout << endl << endl;
    string Cmd[10] = 
    {
    "                           EDIT INVENTORY",
    "+------------------------------------------------------------------+",
    "|",
    "|  A)	Delete item ",
    "|  B)	Add item ",
    "|  C)	Modify item ",
    "|",
    "|  D)	Exit (return to main menu)  ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<10;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// inventory menu

void mod_item_menu()
{
    cout << endl << endl;
    string Cmd[11] = 
    {
    "                           MOD ITEM",
    "+------------------------------------------------------------------+",
    "|",
    "|  A)	Modify description ",
    "|  B)	Modify onHand ",
    "|  C)	Modify capacity ",
    "|  D)  Modify min stock ",
    "|",
    "|  E)	Exit (return to edit inventory menu)  ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<11;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// inventory menu

void Edit_account_menu()
{
    cout << endl << endl;
    string Cmd[10] = 
    {
    "                           EDIT ACCOUNT",
    "+------------------------------------------------------------------+",
    "|",
    "|  A) Add account ",
    "|  B) Disable account ",
    "|  C) Modify account ",
    "|",
    "|  D) Exit (return to main menu)  ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<10;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// account menu

void mod_account_menu()
{
    cout << endl << endl;
    string Cmd[16] = 
    {
    "                           MODIFY ACCOUNT",
    "+------------------------------------------------------------------+",
    "|",
    "|  A) Modify credit limit ",
    "|  B) Modify active/inactive ",
    "|  C) Modify first name ",
    "|  D) Modify last name ",
    "|  E) Deposit funds ",
    "|  F) Modify address ",
    "|  G) Modify city ",
    "|  H) Modify state ",
    "|  I) Modify zip ",
    "|",
    "|  J) Exit (return to main menu)  ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<16;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// account menu

void Print_invoice_menu()
{
    cout << endl << endl;
    string Cmd[11] = 
    {
    "                           PRINT INVOICE(s)",
    "+------------------------------------------------------------------+",
    "|",
    "|  A)	Print specific invoice ",
    "|  B)	Print range of invoices [00 – 999] ",
    "|  C)	Print all invoices for specific account number ",
    "|  D)	Print All invoices for mm/dd/yyyy ",
    "|",
    "|  E)	Exit (return to main menu) ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<10;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// print invoice menu

void Shop_menu()
{
    cout << endl << endl;
    string Cmd[11] = 
    {
    "                           SHOP",
    "+------------------------------------------------------------------+",
    "|",
    "|  A)	View item, desc & cost ",
    "|  B)	Add item(s) to cart ",
    "|  C)	check out** ",
    "|  D)	Remove item from cart ",
    "|",
    "|  E)	Exit (return to main menu) ",
    "|",
     "+------------------------------------------------------------------+"
    };
    for (int k=0; k<10;k++)
    {
        cout << "     " << Cmd[k] << endl;
    }
    cout << endl << endl;
}// shop menu

struct inventory
{
    int item_number;
    string description;
    int onHand;
    int capacity;
    float price;
    unsigned year_created;
    unsigned month_created;
    unsigned day_created;
    unsigned year_modified;
    unsigned month_modified;
    unsigned day_modified;
    int min_stock;
    int quantity;
    int price_total;
    
    inventory *left;
    inventory *right;
    inventory() {left = NULL; right = NULL;}
};

struct account
{
    int account_number;
    float credit_limit;
    bool active;
    string first_name;
    string last_name;
    float balance;
    string address;
    string city;
    string state;
    int zip;
};

struct invoice
{
    int invoice_number;
    string first_name;
    string last_name;
    int account_number;
    int item_number;
    string description;
    float price;
    float item_count;
    float invoice_tax_amt;
    float shipping_cost;
    float invoice_billing_amount;
    //string reoder_description;
    //int Qty_left;
    unsigned month;
    unsigned day;
    unsigned year;
    int price_total;
};

class sales
{
    private:
    inventory *root;
    inventory *node;
    //inventory stock[inventory_max]
    
    account Accts[hash_max];
    stack<invoice> Voice;
    
    public:
    sales()
    {
        root = NULL;
        for(int i=0; i<hash_max; i++)
        {
            Accts[i].account_number = -1;
            Accts[i].credit_limit = -1;
            Accts[i].active = 0;
            Accts[i].first_name = "-1";
            Accts[i].last_name = "-1";
            Accts[i].balance = -1;
            Accts[i].address = "-1";
            Accts[i].city = "-1";
            Accts[i].state = "-1";
            Accts[i].zip = -1;
        }
    }// Constructor
    
    inventory* getRoot(){return root;}                     // BST return root node
    void build_inventory(inventory*&, inventory);               // BST: build tree
    bool itemExist(inventory *&p, inventory n);            // BST: check if item exist
    void add_inventory(inventory *& newNode, inventory node);
    inventory* deleteNode(inventory *root, int key);
    void mod_inventory_description(inventory *&p, inventory var);
    void mod_inventory_onHand(inventory *&p, inventory var);
    void mod_inventory_capacity(inventory *&p, inventory var);
    void mod_inventory_dateCreated(inventory *&p, inventory var);
    void mod_inventory_dateModified(inventory *&p, inventory var);
    void mod_inventory_minStock(inventory *&p, inventory var);
        
    
    int Hash(int key);                              // Create hash key to insert account 
    bool insert_account_table(account var);                   // Insert item into Accts using linear probing
    bool exist(account var);                      // check if account_number exist
    void disable_account(int n);
    void mod_credit_limit(account var);
    void mod_active(account var);
    void mod_account_nameF(account var);
    void mod_account_nameL(account var);
    void mod_account_balance(account var);
    void mod_account_address(account var);
    void mod_account_city(account var);
    void mod_account_state(account var);
    void mod_account_zip(account var);
    
    //void create_invoice(inventory cart[], account var);
    void print_Specific(invoice var, ofstream &outF);
    void print_range(int s, int e, ofstream &outF);
    void print_account(invoice var, ofstream &outF);
    void print_onDate(invoice var, ofstream &outF);
    
    //void new_invoice();
    void show_items(inventory *p);
    bool addCart(inventory *&p, inventory var, inventory cart[]);
    void remove_item(inventory *&p, inventory var, inventory cart[]);
    bool checkout(inventory cart[], account var, int invNum); // send cart and account number 
    void emptyCart(inventory *&p, inventory cart[]);
    
    void inventory_report(ofstream &outF, inventory *p);
    void reorder_report(ofstream &outF, inventory *p);
    void account_report(ofstream &outF);
    
    
};

void sales::emptyCart(inventory *&p, inventory cart[])
{
    emptyCart(p->left, cart);
    for(int i=0; i<cart_max; i++)
    {
        if(cart[i].item_number = p->item_number)
        {
            p->quantity += cart[i].quantity;
            cart[i].item_number = -1;
            cart[i].quantity = -1;
            cart[i].price = -1;
            cart[i].price_total = -1;
            cart[i].description = "-1";
            break;
        }
    }
    emptyCart(p->right, cart);
}

void sales::print_Specific(invoice var, ofstream &outF)//need to complete
{
    stack<invoice> backup = Voice;
    
    while(!backup.empty() )
    {
        if(backup.top().invoice_number == var.invoice_number)
        {
            outF << backup.top().item_number << endl;
            backup.pop();
        }
        else{backup.pop();}
    }
    
}

void sales::print_range(int s, int e, ofstream &outF)//need to complete
{
    stack<invoice> backup = Voice;
    int i = 1;
    
    while(!backup.empty() )
    {
        if(i >= s && i <= e)
        {
            outF << backup.top().item_number << endl;
            backup.pop(); i++;
        }
        else{backup.pop(); i++;}
    }
    
}

void sales::print_account(invoice var, ofstream &outF)//need to complete
{
    stack<invoice> backup = Voice;
    
    while(!backup.empty() )
    {
        if(backup.top().account_number == var.account_number)
        {
            outF << backup.top().item_number << endl;
            backup.pop();
        }
        else{backup.pop();}
    }
    
}

void sales::print_onDate(invoice var, ofstream &outF)//need to complete
{
    stack<invoice> backup = Voice;
    
    while(!backup.empty() )
    {
        if(backup.top().month == var.month && backup.top().day == var.day && backup.top().year == var.year)
        {
            outF << backup.top().item_number;
            backup.pop();
        }
        else{backup.pop();}
    }
    
}

void sales::inventory_report(ofstream &outF, inventory *p)
{
    string mnth[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", "May. ", "Jun. ", 
                       "Jul. ", "Aug. ", "Sept. ", "Oct. ", "Nov. ", "Dec. "};
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    unsigned m = timePtr->tm_mon+1; 
    unsigned d = timePtr->tm_mday;
    unsigned y = timePtr->tm_year+1900;
    
    if(p == NULL){return;}
    
    if(p != NULL){
    inventory_report(outF, p->left);
    if(p->quantity < p->min_stock*p->capacity)
    {
        outF << setw(3) << setfill('0') << p->item_number << setfill(' ') << setw(5) << p->onHand << setw(20) << p->description << setw(15) << p->price*p->quantity <<
            setw(15) << mnth[p->month_created-1] << " " << p->day_created << "," << p->year_created << setw(15) << mnth[p->month_modified-1] << p->day_modified <<
            p->year_modified << setw(5) << p->min_stock << endl;
    }
    inventory_report(outF, p->right);}
}

void sales::reorder_report(ofstream &outF, inventory *p)
{
    string mnth[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", "May. ", "Jun. ", 
                       "Jul. ", "Aug. ", "Sept. ", "Oct. ", "Nov. ", "Dec. "};
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    unsigned m = timePtr->tm_mon+1; 
    unsigned d = timePtr->tm_mday;
    unsigned y = timePtr->tm_year+1900;
    
    if(p == NULL){return;} 
    
    if(p != NULL){
    reorder_report(outF, p->left);
    if (p->quantity < p->min_stock*p->capacity)
    {
        p->onHand = p->quantity/p->capacity;
        outF << setw(3) << setfill('0') << p->item_number << setfill(' ') << setw(5) << p->onHand << setw(15) << mnth[m-1] << d << ", " << y << setw(20) << p->description << endl;
    }
    reorder_report(outF, p->right);}
}

void sales::account_report(ofstream &outF)
{
    for(int i=0; i<hash_max; i++)
    {
        if(Accts[i].account_number != -1)
        {
            outF << Accts[i].account_number << endl;
        }
    }
}

bool sales::checkout(inventory cart[], account var, int invNum)
{
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    unsigned m = timePtr->tm_mon+1; 
    unsigned d = timePtr->tm_mday;
    unsigned y = timePtr->tm_year+1900;
    
    invoice v;
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        if(Accts[i].active == true)
        {
            int k = 0;
            int sum = 0;
            for(k; k<cart_max; k++)
            {
                if(cart[k].item_number != -1){ sum += cart[k].price_total;}
            }
            if(Accts[i].balance > sum)
            {
                for(int a=0; a<cart_max; a++)
                {
                    if(cart[a].item_number != -1)
                    {
                        v.invoice_number = invNum;
                        v.first_name = Accts[i].first_name;
                        v.last_name = Accts[i].last_name;
                        v.account_number = Accts[i].account_number;
                        v.item_number = cart[a].item_number;
                        v.description = cart[a].description;
                        v.price = cart[a].price;
                        v.item_count = cart[a].quantity;
                        v.invoice_tax_amt = .07*cart[a].price_total; // add total price field
                        v.month = m;
                        v.day = d;
                        v.year = y;
                        v.price_total = cart[a].price_total;
                        //v.shipping_cost = 50; // find exact amount later
                        //v.invoice_billing_amount = 
                        Voice.push(v);
                    }  
                }
                Accts[i].balance -= sum;
                return true;
            }
            else{ cout << "ACCOUNT DOES NOT HAVE ENOUGH FUNDS" << endl; return false;}
        }
        else{ cout << "ACCOUNT IS INACTIVE" << endl; return false;}
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number)
            {
                if(Accts[i].active == true)
                {
                    int k = 0;
                    int sum = 0;
                    for(k; k<cart_max; k++)
                    {
                        if(cart[k].item_number != -1){ sum += cart[k].price_total;}
                    }
                    if(Accts[j].balance > sum)
                    {
                        for(int a=0; a<cart_max; a++)
                        {
                            if(cart[a].item_number != -1)
                            {
                                v.invoice_number = invNum;
                                v.first_name = Accts[i].first_name;
                                v.last_name = Accts[i].last_name;
                                v.account_number = Accts[i].account_number;
                                v.item_number = cart[a].item_number;
                                v.description = cart[a].description;
                                v.price = cart[a].price;
                                v.item_count = cart[a].quantity;
                                v.invoice_tax_amt = .07*cart[a].price_total; // add total price field
                                v.month = m;
                                v.day = d;
                                v.year = y;
                                v.price_total = cart[a].price_total;
                                //v.shipping_cost = 50; // find exact amount later
                                //v.invoice_billing_amount = 
                                Voice.push(v);
                            }
                        }
                        Accts[j].balance -= sum;
                        return true;
                    }
                    else{ cout << "ACCOUNT DOES NOT HAVE ENOUGH FUNDS" << endl; return false;}
                }
                else{ cout << "ACCOUNT IS INACTIVE" << endl; return false;}
            }
            if(j == initialindex){ cout << "ACCOUNT NUMBER DOES NOT EXIST" << endl; return false;}
        }
    }
}

void sales::remove_item(inventory *&p, inventory var, inventory cart[])
{
    if (p->item_number == var.item_number)
    {
        int i = 0;
        for(i; i<cart_max; i++)
        {
            if(cart[i].item_number == var.item_number){break; }
        }
        p->quantity += cart[i].quantity;
        cart[i].item_number = -1;
        cart[i].quantity = -1;
        cart[i].price = -1;
        cart[i].description = "-1";
        cart[i].price_total = -1;
    }
    if (p->item_number < var.item_number){remove_item(p->right, var, cart);}
    if (p->item_number > var.item_number){remove_item(p->left, var, cart);}
}

bool sales::addCart(inventory *&p, inventory var, inventory cart[])
{
    if (p->item_number == var.item_number)
    {
        if(p->quantity < var.quantity){ cout << "NOT ENOUGH '" << p->description << "' IN STOCK" << endl; return false; }
        else
        {
            if(p->quantity > var.quantity)
            {
                p->quantity -= var.quantity;
                for(int n=0; n<cart_max; n++)
                {
                    if(cart[n].item_number == -1)
                    {
                        cart[n].item_number = var.item_number;
                        cart[n].quantity = var.quantity;
                        cart[n].price = p->price;
                        cart[n].price_total = p->price*var.quantity;
                        cart[n].description = p->description;
                        return true;
                    }
                }
            }
            else{ return false;}
        }
    }
    if (p->item_number < var.item_number){addCart(p->right, var, cart);}
    if (p->item_number > var.item_number){addCart(p->left, var, cart);}
}

void sales::show_items(inventory *p)
{
    int n = 1;
    char cont;
    if(p == NULL){return;}
    
    if(p != NULL)
    {
        show_items(p->left);
        cout << setw(3) << setfill('0') << p->item_number << "    " << setw(20) << setfill(' ') << left << p->description << setw(7) << "  qty: x" << setw(10) << p->onHand*p->capacity <<  "$" << setw(9) << setprecision(2) << fixed << p->price << endl; n++;
        //if(n%10 == 0){ cout << "continue?[y/n]"; cin >> cont; if(cont == 'y' || cont == 'Y'){continue;} if(cont == 'n' || cont == 'N'){return;}}
        show_items(p->right);
    }
}

void sales::mod_account_zip(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].zip = var.zip;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].zip = var.zip; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_state(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].state = var.state;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].state = var.state; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_city(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].city = var.city;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].city = var.city; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_address(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].address = var.address;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].address = var.address; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_balance(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].balance += var.balance;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].balance += var.balance; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_nameL(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].last_name = var.last_name;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].last_name = var.last_name; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_account_nameF(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].first_name = var.first_name;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].first_name = var.first_name; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_active(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].active = var.active;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].active = var.active; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::mod_credit_limit(account var)
{
    int i = Hash(var.account_number);
    if(Accts[i].account_number == var.account_number)
    {
        Accts[i].credit_limit = var.credit_limit;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != var.account_number){j = 0;}
            if(Accts[j].account_number == var.account_number){Accts[j].credit_limit = var.credit_limit; break;}
            if(j == initialindex){break;}
        }
    }
}

void sales::disable_account(int n)
{
    int i = Hash(n);
    if(Accts[i].account_number == n)
    {
        Accts[i].active = false;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].account_number != n){j = 0;}
            if(Accts[j].account_number == n){Accts[j].active = false; break;}
            if(j == initialindex){break;}
        }
    }
    
}

bool sales::exist(account var) 
{
    stringstream ss;
    
    bool x = false;
    for(int i=0; i<hash_max; i++)
    {
        if(Accts[i].account_number == var.account_number){x = true; return x;}
    }
    return x;
}// check account number doesn't exist

int sales::Hash(int key) 
{ 
    int index = key % hash_max;
    return index;
}// create index for items in table

bool sales::insert_account_table(account var) 
{
    bool full = false;
    int i = Hash(var.account_number);
    if(Accts[i].first_name == "-1")
    {
        Accts[i].account_number = var.account_number;
        Accts[i].credit_limit = var.credit_limit;
        Accts[i].active = var.active;
        Accts[i].first_name = var.first_name;
        Accts[i].last_name = var.last_name;
        Accts[i].balance = var.balance;
        Accts[i].address = var.address;
        Accts[i].city = var.city;
        Accts[i].state = var.state;
        Accts[i].zip = var.zip;
        return full;
    }
    else
    {
        int initialindex = i;
        int j;
        if(i == hash_max-1){i = 0; j = i;}
        else{j = i + 1;}
        for(j; j<hash_max; j++)
        {
            if(j == hash_max-1 && Accts[j].first_name != "-1"){j = 0;}
            if(Accts[j].first_name == "-1")
            {
                Accts[j].account_number = var.account_number;
                Accts[j].credit_limit = var.credit_limit;
                Accts[j].active = var.active;
                Accts[j].first_name = var.first_name;
                Accts[j].last_name = var.last_name;
                Accts[j].balance = var.balance;
                Accts[j].address = var.address;
                Accts[j].city = var.city;
                Accts[j].state = var.state;
                Accts[j].zip = var.zip;
                return full;
            }
            if(j == initialindex){cout << "TABLE IS FULL" << endl; full = true; return full;}
        }
    }
}// insert 

void sales::mod_inventory_description(inventory *&p, inventory var)
{
    if (p->item_number == var.item_number){p->description = var.description;}
    if (p->item_number < var.item_number){mod_inventory_description(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_description(p->left, var);}
}

void sales::mod_inventory_onHand(inventory *&p, inventory var)
{
    if (p->item_number == var.item_number){p->onHand = var.onHand;}
    if (p->item_number < var.item_number){mod_inventory_onHand(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_onHand(p->left, var);}
}

void sales::mod_inventory_capacity(inventory *&p, inventory var)
{
    if (p->item_number == var.item_number){p->capacity = var.capacity;}
    if (p->item_number < var.item_number){mod_inventory_capacity(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_capacity(p->left, var);}
}

void sales::mod_inventory_dateCreated(inventory *&p, inventory var)
{
    if (p->item_number == var.item_number)
    {
        p->month_created = var.month_created;
        p->day_created = var.day_created;
        p->year_created = var.year_created;
    }
    if (p->item_number < var.item_number){mod_inventory_dateCreated(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_dateCreated(p->left, var);}
}

void sales::mod_inventory_dateModified(inventory *&p, inventory var)
{
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    unsigned m = timePtr->tm_mon+1; 
    unsigned d = timePtr->tm_mday;
    unsigned y = timePtr->tm_year+1900;
    
    if (p->item_number == var.item_number)
    {
        p->month_modified = m;
        p->day_modified = d;
        p->year_modified = y;
    }
    if (p->item_number < var.item_number){mod_inventory_dateModified(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_dateModified(p->left, var);}
}

void sales::mod_inventory_minStock(inventory *&p, inventory var)
{
    if (p->item_number == var.item_number){p->min_stock = var.min_stock;}
    if (p->item_number < var.item_number){mod_inventory_minStock(p->right, var);}
    if (p->item_number > var.item_number){mod_inventory_minStock(p->left, var);}
}

bool sales::itemExist(inventory *&p, inventory n)
{
    bool x = false;
    if(p == NULL){return x;}
    if(p->item_number == n.item_number)
    {
        x = true;
        return x;
    }
    if(p->item_number < n.item_number){return itemExist(p->right, n);}
    if(p->item_number > n.item_number){return itemExist(p->left, n);}
    return x;
}

void sales::build_inventory(inventory *& newNode, inventory node)
{   
    
    if(newNode == NULL)       // Checks if the tree is empty
    {
        newNode = new inventory;
        newNode->item_number = node.item_number;
        newNode->description = node.description;
        newNode->onHand = node.onHand;
        newNode->capacity = node.capacity;
        newNode->price = node.price;
        newNode->month_created = node.month_created;
        newNode->day_created = node.day_created;
        newNode->year_created = node.year_created;
        newNode->year_modified = node.year_modified;
        newNode->month_modified = node.month_modified;
        newNode->day_modified = node.day_modified;
        newNode->min_stock = node.min_stock;
        newNode->quantity = newNode->onHand*newNode->capacity;
        newNode->left = NULL;
        newNode->right = NULL; 
    }    
    else if(newNode->item_number > node.item_number)
    {
        build_inventory(newNode->left, node);
    }
    else if(newNode->item_number < node.item_number)
    {
        build_inventory(newNode->right, node);
    }
}// insert inventory items

void sales::add_inventory(inventory *& newNode, inventory node)
{   
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

    unsigned m = timePtr->tm_mon+1; 
    unsigned d = timePtr->tm_mday;
    unsigned y = timePtr->tm_year+1900;
    
    if(newNode == NULL)       // Checks if the tree is empty
    {
        newNode = new inventory;
        newNode->item_number = node.item_number;
        newNode->description = node.description;
        newNode->onHand = node.onHand;
        newNode->capacity = node.capacity;
        newNode->price = node.price;
        newNode->month_created = m;
        newNode->day_created = d;
        newNode->year_created = y;
        newNode->year_modified = y;
        newNode->month_modified = m;
        newNode->day_modified = d;
        newNode->min_stock = node.min_stock;
        newNode->quantity = newNode->onHand*newNode->capacity;
        newNode->left = NULL;
        newNode->right = NULL; 
    }    
    else if(newNode->item_number > node.item_number)
    {
        add_inventory(newNode->left, node);
    }
    else if(newNode->item_number < node.item_number)
    {
        add_inventory(newNode->right, node);
    }
}// insert new inventory

inventory* minValueNode(inventory* node) 
{ 
    inventory* current = node;
    
    while (current->left != NULL){ current = current->left;}
  
    return current; 
} 

inventory* sales::deleteNode(inventory *root, int key) 
{
    if (root == NULL) return root;
    
    if (key < root->item_number) 
        root->left = deleteNode(root->left, key); 
   
    else if (key > root->item_number) 
        root->right = deleteNode(root->right, key); 
  
    else
    {
        if (root->left == NULL) 
        { 
            inventory *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            inventory *temp = root->left; 
            free(root); 
            return temp; 
        } 
        
        inventory* temp = minValueNode(root->right); 
   
        root->item_number = temp->item_number; 
  
        root->right = deleteNode(root->right, temp->item_number); 
    } 
    return root; 
}

//create mod inventory items




int main()
{
    sales T;
    account act;
    inventory inv;
    inventory cart[cart_max];
    int invNum = 1;
    
    for(int j=0; j<cart_max; j++)
    {
        cart[j].item_number = -1;
        cart[j].quantity = -1;
        cart[j].price = -1;
        cart[j].price_total = -1;
        cart[j].description = "-1";
    }
    
    string account_data = "account.txt";
    string inventory_data = "inventory.txt";
    string account_r = "accountReport.txt";
    string inventory_r = "inventoryReport.txt";
    string reorder_r = "reorderReport.txt";
    string Pspecific = "Specific_invoice.txt";
    string Prange = "Range_invoice.txt";
    string Paccount = "Account_invoice.txt";
    string Pondate = "Ondate_invoice.txt";
    ofstream Psp, Pr, Pacc, PD;
    
    ifstream inF;
    ofstream outF;
    
    
    inF.open(account_data.c_str());
    while(inF >> act.account_number >> act.credit_limit >> act.active >> act.first_name >> act.last_name >> act.balance >> act.address >> act.city >> act.state >> act.zip)
    {
        T.insert_account_table(act);
    }inF.close();
    
    
    inF.open(inventory_data.c_str());
    inventory *root = T.getRoot();
    while(inF >> inv.item_number >> inv.description >> inv.onHand >> inv.capacity >> inv.price >> inv.year_created >> inv.month_created >> inv.day_created >> inv.year_modified >> inv.month_modified >> inv.day_modified >> inv.min_stock)
    {
        T.build_inventory(root, inv);
    }inF.close();
    
    char cmd;
    bool running = true;
    
    while(isdigit(cmd) != 5 && running == true)
    {
        Menu();
        cout << " Enter Command: ";
        cin >> cmd;
        cout << endl;
        switch (cmd)
        {
            case '1'://edit inventory
                {
                    char command;
                    bool run = true;
                    
                    while(isalpha(command) != 'D' && run == true)
                    {
                        Edit_inventory_menu();
                        cout << " Enter Command: ";
                        cin >> command;
                        //toupper(command);
                        cout << endl;
                        switch(toupper(command))
                        {
                            case 'A':
                                {
                                    cout << "Enter item number: ";
                                    cin >> inv.item_number;
                                    if(T.itemExist(root, inv) == true){T.deleteNode(root, inv.item_number);}
                                    else{ cout << "INVALID ITEM NUMBER..." << endl; break;}
                                }break;
                            case 'B':
                                {
                                    cout << "Enter item number: ";
                                    cin >> inv.item_number;
                                    if(T.itemExist(root, inv) == true){cout << "ITEM NUMBER ALREADY EXIST..." << endl; break;}
                                    else
                                    {
                                        cout << "Enter item description: ";
                                        cin >> inv.description;
                                        cout << "Enter on hand: ";
                                        cin >> inv.onHand;
                                        cout << "Enter item capacity: ";
                                        cin >> inv.capacity;
                                        cout << "Enter item price: ";
                                        cin >> inv.price;
                                        cout << "Enter min stock: ";
                                        cin >> inv.min_stock;
                                        T.add_inventory(root, inv);
                                    }
                                }break;
                            case 'C':
                                {
                                    cout << "Enter item number: ";
                                    cin >> inv.item_number;
                                    if(T.itemExist(root, inv) == true)
                                    {
                                        char option;
                                        bool active = true;
                                        while(isalpha(option) != 'E' && active == true)
                                        {
                                            mod_item_menu();
                                            cout << "Enter command: ";
                                            cin >> option;
                                            switch(toupper(option))
                                            {
                                                case 'A':
                                                    {
                                                        cout << "Enter new description: ";
                                                        cin >> inv.description;
                                                        T.mod_inventory_description(root, inv);
                                                    }break;
                                                case 'B':
                                                    {
                                                        cout << "Enter new on hand: ";
                                                        cin >> inv.onHand;
                                                        T.mod_inventory_onHand(root, inv);
                                                    }break;
                                                case 'C':
                                                    {
                                                        cout << "Enter new capacity: ";
                                                        cin >> inv.capacity;
                                                        T.mod_inventory_capacity(root, inv);
                                                    }break;
                                                case 'D':
                                                    {
                                                        cout << "Enter new min stock: ";
                                                        cin >> inv.min_stock;
                                                        T.mod_inventory_minStock(root, inv);
                                                    }break;
                                                case 'E':
                                                    {
                                                        T.mod_inventory_dateModified(root, inv); active = false;
                                                    }break;
                                                default:   cout << " UNKNOWN Command '" << option << "' ... retry" << endl;
                                            }//mod_item_menu switch
                                        }//mod_item_menu while
                                        
                                    }
                                    else{ cout << "INVALID ITEM NUMBER" << endl; break;}
                                }break;
                            case 'D':
                                {
                                    run = false;
                                }break;
                            default:   cout << " UNKNOWN Command '" << command << "' ... retry" << endl;
                        }//inventory switch
                    }//inventory while
                    
                }break;
            case '2'://edit account
                {
                    char command;
                    bool run = true;
                    
                    while(isalpha(command) != 'D' && run == true)
                    {
                        Edit_account_menu();
                        cout << " Enter Command: ";
                        cin >> command;
                        cout << endl;
                        switch(toupper(command))
                        {
                            case 'A':
                                {
                                    cout << "Enter account number: ";
                                    cin >> act.account_number;
                                    if(T.exist(act) == true){ cout << "INVALID ACCOUNT NUMBER" << endl; break;}
                                    else
                                    {
                                        cout << "Enter credit_limit: ";
                                        cin >> act.credit_limit;
                                        cout << "Enter active/inactive[1|0]: ";
                                        cin >> act.active;
                                        cout << "Enter first_name: ";
                                        cin >> act.first_name;
                                        cout << "Enter last_name: ";
                                        cin >> act.last_name;
                                        cout << "Enter Address [xxx_xxxx_xx]: ";
                                        cin >> act.address;
                                        cout << "Enter city: ";
                                        cin >> act.city;
                                        cout << "Enter state: ";
                                        cin >> act.state;
                                        cout << "Enter zip: ";
                                        cin >> act.zip;
                                        T.insert_account_table(act);
                                    }
                                }break;
                            case 'B':
                                {
                                    cout << "Enter account number: ";
                                    cin >> act.account_number;
                                    if(T.exist(act) == true)
                                    {
                                        T.disable_account(act.account_number);
                                    }
                                    else{ cout << "INVALID ACCOUNT NUMBER" << endl; break;}
                                }break;
                            case 'C':
                                {
                                    cout << "Enter account_number: ";
                                    cin >> act.account_number;
                                    if(T.exist(act) == true)
                                    {
                                        char option;
                                        bool active = true;

                                        while(isalpha(option) != 'J' && active == true)
                                        {
                                            mod_account_menu();
                                            cout << " Enter Command: ";
                                            cin >> command;
                                            cout << endl;
                                            switch(toupper(command))
                                            {
                                                case 'A':
                                                    {
                                                        cout << "Enter new credit_limit: ";
                                                        cin >> act.credit_limit;
                                                        T.mod_credit_limit(act);
                                                    }break;
                                                case 'B':
                                                    {
                                                        cout << "Enter active/inactive[1|0]: ";
                                                        cin >> act.active;
                                                        T.mod_active(act);
                                                    }break;
                                                case 'C':
                                                    {
                                                        cout << "Enter new first name: ";
                                                        cin >> act.first_name;
                                                        T.mod_account_nameF(act);
                                                    }break;
                                                case 'D':
                                                    {
                                                        cout << "Enter new last name: ";
                                                        cin >> act.last_name;
                                                        T.mod_account_nameL(act);
                                                    }break;
                                                case 'E':
                                                    {
                                                        cout << "Enter amount to deposit: ";
                                                        cin >> act.balance;
                                                        if(act.balance < 0){cout << "INVALID AMOUNT" << endl; break;}
                                                        else{ T.mod_account_balance(act);}
                                                    }break;
                                                case 'F':
                                                    {
                                                        cout << "Enter new address[xxx_xxxx_xx]: ";
                                                        cin >> act.address;
                                                        T.mod_account_address(act);
                                                    }break;
                                                case 'G':
                                                    {
                                                        cout << "Enter new city: ";
                                                        cin >> act.city;
                                                        T.mod_account_city(act);
                                                    }break;
                                                case 'H':
                                                    {
                                                        cout << "Enter new state: ";
                                                        cin >> act.state;
                                                        T.mod_account_state(act);
                                                    }break;
                                                case 'I':
                                                    {
                                                        cout << "Enter new zip: ";
                                                        cin >> act.zip;
                                                        T.mod_account_zip(act);
                                                    }break;
                                                case 'J':
                                                    {
                                                        active = false;
                                                    }break;
                                                 default:   cout << " UNKNOWN Command '" << option << "' ... retry" << endl;
                                            }//mod account switch
                                        }//mod account while
                                    }// if acct exist
                                    else{ cout << "INVALID ACCOUNT NUMBER" << endl; break;}
                                }break;
                            case 'D':
                                {
                                    run = false;
                                }break;
                            default:   cout << " UNKNOWN Command '" << command << "' ... retry" << endl;
                        }//edit account switch
                    }//edit account while
                }break;
            case '3'://shop
                {
                    char command;
                    bool run = true;
                    bool out = false;
                    while(isalpha(command) != 'E' && run == true)
                    {
                        
                        Shop_menu();
                        cout << " Enter Command: ";
                        cin >> command;
                        cout << endl;
                        switch(toupper(command))
                        {
                                
                            case 'A':
                                {
                                    T.show_items(root);
                                }break;
                            case 'B':
                                {
                                    cout << "Enter item number: ";
                                    cin >> inv.item_number;
                                    cout << "Enter quantity: ";
                                    cin >> inv.quantity;
                                    if(T.addCart(root, inv, cart) == true){ cout << "ITEM ADDED" << endl;}
                                    else{ cout << " UNABLE TO ADD TO CART" << endl;}
                                }break;
                            case 'C':
                                {
                                    cout << "Enter account number: ";
                                    cin >> act.account_number;
                                    if(T.exist(act) == true)
                                    {
                                        out = T.checkout(cart, act, invNum);
                                        if(out == true)
                                        { 
                                            cout << "YOU HAVE SUCCESSFULLY CHECKED OUT" << endl;
                                            for(int j=0; j<cart_max; j++)
                                            {
                                                cart[j].item_number = -1;
                                                cart[j].quantity = -1;
                                                cart[j].price = -1;
                                                cart[j].price_total = -1;
                                                cart[j].description = "-1";
                                            }
                                            invNum++;
                                        }
                                        else{ cout << "UNABLE TO CHECKOUT" << endl;}
                                    }
                                    else{ cout << "INVALID ACCOUNT NUMBER" << endl; break;}
                                    
                                }break;
                            case 'D':
                                {
                                    cout << "Enter item_number: ";
                                    cin >> inv.item_number;
                                    if(T.itemExist(root, inv) == true)
                                    {
                                        T.remove_item(root, inv, cart);
                                    }
                                    else{ cout << "INVALID ITEM NUMBER" << endl; break;}
                                }break;
                            case 'E':
                                {
                                    if(out == false){ T.emptyCart(root, cart);}
                                    run = false;
                                }break;
                        }//shop switch
                    }//shop while
                }break;
            case '4'://print invoices
                {
                    char command;
                    bool run = true;
                    
                    while(isalpha(command) != 'E' && run == true)
                    {
                        bool out = false;
                        Print_invoice_menu();
                        cout << " Enter Command: ";
                        cin >> command;
                        cout << endl;
                        switch(toupper(command))
                        {
                                
                            case 'A':
                                {
                                    invoice v;
                                    cout << "Enter invoice number";
                                    cin >> v.invoice_number;
                                    Psp.open(Pspecific.c_str());
                                    T.print_Specific(v, Psp);
                                    Psp.close();
                                }break;
                            case 'B':
                                {
                                    int s ,e;
                                    cout << "Enter range start: ";
                                    cin >> s;
                                    cout << "Enter range end: ";
                                    cin >> e;
                                    Pr.open(Prange.c_str());
                                    T.print_range(s, e, Pr);
                                    Pr.close();
                                }break;
                            case 'C':
                                {
                                    invoice v;
                                    cout << "Enter account_number";
                                    cin >> v.account_number;
                                    Pacc.open(Paccount.c_str());
                                    T.print_account(v, Pacc);
                                    Pacc.close();
                                }break;
                            case 'D':
                                {
                                    invoice v;
                                    cout << "Enter date [MM DD YR]: ";
                                    cin >> v.month >> v.day >> v.year;
                                    PD.open(Pondate.c_str());
                                    T.print_onDate(v, PD);
                                    PD.close();
                                }break;
                            case 'E':
                                {
                                    run = false;
                                }break;
                        }//print invoice switch
                    }//print invoice while
                }break;
            case '5'://exit
                {
                    outF.open(account_r.c_str());
                    T.account_report(outF);
                    outF.close();
                    outF.open(inventory_r.c_str());
                    T.inventory_report(outF, root);
                    outF.close();
                    outF.open(reorder_r.c_str());
                    T.reorder_report(outF, root);
                    outF.close();
                    
                    running = false;
                }break;
            default:   cout << " UNKNOWN Command '" << cmd << "' ... retry" << endl;
                
        }//main switch
    }//while
    
    
    return 0;
}
