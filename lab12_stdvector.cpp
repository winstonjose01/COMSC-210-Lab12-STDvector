// COMSC 210 | Lab12 |  Winston Jose
// Github link: https://github.com/winstonjose01/COMSC-210-Lab12-STDarray

# include <iostream>
# include <array>
# include <algorithm>
# include <numeric>
# include <fstream>
# include <sstream>
# include <string>

using namespace std;

const int SIZE = 30; // Constant size for the

// Struct to store grocery item name and price
struct GroceryItem{
    string item;
    double prices;
};

//Function declarations
int openFile(fstream &, string);  // Function to open  file
bool sortbyItem (GroceryItem &, GroceryItem &); // Function to compare items alphabetically
bool sortbyPrice (GroceryItem &, GroceryItem &); // Function to compare prices

int main(){

    fstream budgetfile; // File stream object for reading from a file
    string filename = "grocery.csv"; // File name to open
    int fstat; // File status
    string line; // String to hold each line from the file
    array<GroceryItem, SIZE> list; // Array of structs to hold items and prices
 
    // Exit if file cannot be opened
    fstat = openFile(budgetfile,filename);
    if (fstat < 0){
        exit(-1);
    }
    int i = 0;

    // Read the file line by line and split each line into item and price
    while (getline(budgetfile, line) && i < SIZE){
        stringstream ss(line); // Create a stringstream to process the line
        string priceStr;

        getline(ss, list[i].item,','); // Delimit the line by comma
        getline(ss,priceStr); // Get price (after the comma)
        if (!priceStr.empty())
            try{
            list[i].prices = stod(priceStr);  // Convert price from string to double
            }
            catch(const invalid_argument &e){
            cout << "Invalid price " << priceStr << endl; // Handle invalid price input
            }
        i++;
    }

    // Report the size of the list array
    cout << "1. Size of Grocery list: " << list.size() << endl;
    cout << "\n----------------------------------------------------\n";

    // Display the values of the array of structs
    cout << "2. Accessing value of the Grocery list:\n";
    for (GroceryItem val :  list) cout << "\t" << val.item << " | $" << val.prices << endl;
     cout << "\n----------------------------------------------------\n";
    
    // Accessing individual elements in the array
    cout << "\n3. Element 11 item and price: "<< list.at(11).item << " | $" << list.at(11).prices;
    cout << "\n4. Element 29 item and price: "<< list[29].item << " | $" << list[29].prices;
    cout << "\n5. Front item and price: "<< list.front().item<< " | $" << list.front().prices;
    cout << "\n6. Back item and price: "<< list.back().item<< " | $" << list.back().prices;
    cout << "\n7. Empty ? " << (list.empty() == 0? "False" : "True");
    cout << "\n8. Address? " << list.data();
    cout << "\n----------------------------------------------------\n";

    // Sort the array by item name using the sortbyItem function
    sort(list.begin(), list.end(), sortbyItem); // Sort by item using a comparator function
    cout << "\n9.  Sorted by item :\n";
    for (GroceryItem val :  list) cout << "\t" << val.item << " | $" << val.prices << endl;
    cout << "\n----------------------------------------------------\n";

    // Sort the array by price using the sortbyPrice comparator function
    sort(list.begin(), list.end(), sortbyPrice); // use sortbyPrice() comparator
    cout << "\n10.  Sorted by price :\n";
    for (GroceryItem val :  list) cout << "\t" << val.item << " | $" << val.prices << endl;
    cout << "\n----------------------------------------------------\n";

    // Reverse sort by item (reversing the sorted array)
    sort(list.begin(), list.end(), sortbyItem); // Use sortbyItem() comparator
    cout << "\n11.  Reverse sorting by item :\n";
    sort(list.rbegin(), list.rend(), sortbyItem);
    for (GroceryItem val :  list) cout << "\t" << val.item << " | $" << val.prices << endl;
    cout << "\n----------------------------------------------------\n";

     // Find the max price using max_element - use lambda function to compare price fields
    cout << "12. Max: $" << max_element(list.begin(), list.end(),[](GroceryItem &a, GroceryItem &b)
         {return a.prices < b.prices;})->prices;

    // Find the min price using min_element  - use lambda function to compare price field
    cout << "\n13. Min: $" << min_element(list.begin(), list.end(),[](GroceryItem &a, GroceryItem &b)
         {return a.prices > b.prices;})->prices;
    
    // Sum all prices using accumulate - use the 4th argument with a lambda fn to sum the price elements
    cout << "\n13. Sum: $" << accumulate(list.begin(), list.end(),0.0,[](double sum, GroceryItem &b)
         {return sum + b.prices;});
    cout << "----------------------------------------------------\n";

    // Create several empty <array> and fill with one value
    array<GroceryItem,3> list3;
    cout << "14. Array of emppty structs and fill with one value\n";
    fill(list3.begin(), list3.end(), GroceryItem{"Butter", 5.23});
    for (GroceryItem val :  list3) cout << "\t" << val.item << " | $" << val.prices << endl;
    cout << "----------------------------------------------------\n";

    array<GroceryItem,5> list5;
    fill(list5.begin(), list5.end(), GroceryItem{"Cookies", 3.56});
    for (GroceryItem val :  list5) cout << "\t" << val.item << " | $" << val.prices << endl;
    cout << "----------------------------------------------------\n";

    budgetfile.close(); // Close the file

    return 0;

}

bool sortbyItem(GroceryItem &a, GroceryItem&b){
    return (a.item < b.item);
}

bool sortbyPrice(GroceryItem &a, GroceryItem&b){
    return (a.prices < b.prices);
}

int openFile(fstream &f, string fname){
    f.open(fname.data(), ios::in);
    if(!f){
        cout << "Error opening file. Program aborting\n";
        return 0;
    }
    else{
        return 1;    
    }
}
