/*
    Authors:
        Michael Maher Nagi
        Mira Ehab Mikhail

    The purpose of the program:
        Create an Online Shopping System to help seller add, buy or find an element.

*/
#include <iostream>

using namespace std;

class Item{
private:
    string name;
    int id,quantity;
    double price;
    /* Static Member Variable */
    static int numOfItems;
public:
    friend class Seller;
    /* Constructors */
    Item();
    Item(string ,int ,double);
    Item(const Item&);
    /* Overloaded functions */
    bool operator== (const Item&);
    void operator+= (Item&);
    void operator-= (int);
    friend istream& operator>> (istream& , Item&);
    friend ostream& operator<< (ostream& , Item&);
    /* Setters */
    void setName(string n){
        name = n;
    };
    void setQuantity(int q){
        quantity = q;
    };
    void setPrice(double p){
        price = p;
    };
    /* Getters */
    string getName(){
        return name;
    };
    int getQuantity(){
        return quantity;
    };
    int getId(){
        return id;
    };
    double getPrice(){
        return price;
    };
};

int Item::numOfItems = 0;

//Default Constructor
Item::Item(){
    numOfItems++;
    name = "g";
    id = numOfItems;
    quantity = 0;
    price = 0;
}
//Parametrized Constructor
Item::Item(string _name,int _quantity,double _price){
    numOfItems++;
    name = _name;
    id = numOfItems;
    quantity = _quantity;
    price = _price;
}
//Copy constructor
Item::Item(const Item& item){
    numOfItems++;
    name = item.name;
    id = numOfItems;
    quantity = item.quantity;
    price = item.price;
}
//overloaded function that returns a bool indicating the equality or inequality.
bool Item::operator== (const Item& item){
    return (name==item.name);
}
//to increase the quantity of the item
void Item::operator+= ( Item& item){
    quantity += item.quantity;
    item.setQuantity(0);
}
//to decrease the quantity of the intem
void Item::operator-= (int _quantity){
    quantity -= _quantity;
}
istream& operator>> (istream& is ,Item& item){
    cout<<"Enter Name of the Item : ";
    is>>item.name;
    cout<<"Enter Quantity of the Item : ";
    is>>item.quantity;
    cout<<"Enter Price of the Item : ";
    is>>item.price;
    return is;
}
ostream& operator<< (ostream& os , Item& item){
    os<<"Name of the Item : "<<item.name<<endl;
    os<<"ID of the Item : "<<item.id<<endl;
    os<<"Quantity of the Item : "<<item.quantity<<endl;
    os<<"Price of the Item : "<<item.price<<endl;
    return os;
}


class Seller{
private:
    string name,email;
    int maxItems,numItems=0;
    Item *items;
public:
    /* Constructors */
    Seller(string,string,int);
    /* Destructor */
    ~Seller();
    /* Member function */
    bool AddItem(Item&);
    bool SellItem(string,int);
    void PrintItems();
    Item* FindById(int);
    friend ostream& operator<< (ostream& , Seller&);
};

//constructor
Seller::Seller(string _name, string _email,int _maxItems){
    name = _name;
    email = _email;
    maxItems = _maxItems;
    items = new Item[maxItems];
    Item::numOfItems  -= maxItems;
}
//destructor
Seller::~Seller(){
    delete []items;
}
ostream& operator<< (ostream& os, Seller& seller){
    os<<"Name of the Seller : "<<seller.name<<endl;
    os<<"Email of the Seller : "<<seller.email<<endl;
    os<<"Max  Number of  Items : "<<seller.maxItems<<endl;
    return os;
}
//to add an item in the sellers items
bool Seller::AddItem(Item& item){
    for(int i=0;i<numItems;i++){
        if(items[i] == item){
            items[i] += item;
            //i use this line because i created object of item in main and it will take an id 
            //and then add the quantity to other item
            Item::numOfItems--;   
            return true;
        }
    }
    if(numItems<maxItems){
        items[numItems]=item;
        numItems++;
        return true;
    }else{
        return false;
    }

}
//To sell an item with available quantity
bool Seller::SellItem(string name,int quantity){
    bool found = false;
    for(int i=0;i<numItems;i++){
        if(items[i].getName() == name){
            if(quantity<=items[i].getQuantity()){
                items[i]-=quantity;
                cout<<"Item Sold successfully."<<endl;
            }else{
                cout<<"There is only "<<items[i].getQuantity()<<" left for this item"<<endl;
            }
            found = true;
        }
    }
    return found;
}
void Seller::PrintItems(){
    cout<<"List of Items :\n"<<endl;
    for(int i=0;i<numItems;i++){
        cout<<"Item "<<i+1<<" :"<<endl;
        cout<<items[i]<<endl;;
    }
}
//To find an item using the id
Item* Seller::FindById(int id){
    for(int i=0;i<numItems;i++){
        if(items[i].getId() == id){
            return &items[i];
        }
    }
    return NULL;
}

int main(){
    string name, email;
    int maxitems;
    cout<<"please input your details: "<<endl;
    cout<<"enter your name: ";
    cin>>name;
    cout<<"enter your E-mail: ";
    cin>>email;
    cout<<"Enter the maximum number of items: ";
    cin>>maxitems;
    Seller s1(name,email,maxitems);
    int choice = 0;
    while(choice != 6){
        cout<<"\nChoose from the following options: (enter 1 or 2 ....)"<<endl;
        cout<<"1.Print My Info. \n2.Add An Item. \n3.Sell An Item. \n4.Print Items. \n5.Find an Item by ID \n6.Exit"<<endl;
        cout<<"your choice: ";
        cin>>choice;
        while(choice < 1 || choice > 6){
            cout<<"invalid choice! please enter another number from 1 to 6";
            cout<<"your choice: ";
            cin>>choice;
        }
        if(choice == 1) cout<<endl<<s1;
        else if(choice == 2){
            Item i;
            cout<<endl;
            cin>>i;
            if(s1.AddItem(i)) cout<<"Item Added successfully."<<endl;
            else cout<<"you exeeded the maximum number of items. this item couldn't be Added."<<endl;
        }
        else if(choice == 3){
            string name;
            int quantity;
            cout<<endl<<"Enter the item's name: ";
            cin>>name;
            cout<<"Enter the item's quantity to be sold: ";
            cin>>quantity;
            if(!s1.SellItem(name, quantity)) cout<<"Item Not found! "<<endl;
        }
        else if(choice == 4) {cout<<endl;s1.PrintItems();}
        else if(choice == 5){
            int id;
            cout<<endl<<"Enter the item's id to be found: ";
            cin>>id;
            Item* i = s1.FindById(id);
            if(i == NULL) cout<<"Item Not Found!"<<endl;
            else{
                cout<<"Item Found:"<<endl;
                cout<<*i;
            }
        }
        else if(choice == 6) return 0;
    }
    return 0;
}
