//
//  fine.cpp
//  fine
//
//  Created by Layah Vigneaud on 10/11/23.
//


#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Variables are initialized
    string identification;
    double overstatedAmount;
    string location;
    double fine = 0;
    
    // User is prompted to enter identification, overstated amount and location.
    cout << "Identification: ";
    getline(cin, identification);
    cout <<  "Overstated amount (in millions): ";
    cin >> overstatedAmount;
    cin.ignore(10000,'\n');
    cout << "Location: ";
    getline(cin, location);
    cout <<  "---" << endl;
    
    //Program checks for identification.
    if(identification == ""){
        cout << "You must enter a property identification." << endl;
    }
    //Program checks for positive overstated amount.
    else if(overstatedAmount < 0){
        cout << "The overstated amount must be positive." << endl;
    }
    //Program checks for location.
    else if(location == ""){
        cout << "You must enter a location." << endl;
    }
    //If overstated amount is less then or equal to 60, the fine is 11.11% of $60M.
    else if(overstatedAmount <= 60){
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout <<  "The fine for " << identification << " is $" << overstatedAmount * 0.1111 << " million." << endl;
    }
    //If overstated amount is less then or equal to 150, and located in florida or new york, the fine is 11.11% of $60M, plus 18.0% of $90M.
    else if((overstatedAmount <= 150) && (location == "new york" || location == "florida")){
        fine = (overstatedAmount - 60) * 0.18 + (60*0.1111);
        cout.precision(5);
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout <<  "The fine for " << identification << " is $" << fine << " million." << endl;
    }
    //If overstated amount is less then or equal to 150, the fine is 11.11% of $60M, plus 15.3% of $90M.
    else if(overstatedAmount <= 150){
        fine = (overstatedAmount - 60) * 0.153 + (60*0.1111);
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout <<  "The fine for " << identification << " is $" << fine << " million." << endl;
    }
    //If overstated amount is greater then 150, and located in florida or new york, the fine is 11.11% of $60M, plus 18.0% of $90M, plus 21.0% of whatever is left.
    else if((overstatedAmount > 150) && (location == "new york" || location == "florida")){
        fine = (overstatedAmount - 150) * 0.21 + (60*0.1111)+ (90* 0.18);
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout <<  "The fine for " << identification << " is $" << fine << " million." << endl;
    }
    //If overstated amount is greater then 150, the fine is 11.11% of $60M, plus 15.3% of $90M, plus 21.0% of whatever is left..
    else {
        fine = (overstatedAmount - 150) * 0.21 + (60*0.1111)+ (90* 0.153);
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout <<  "The fine for " << identification << " is $" << fine << " million." << endl;
    }
    
}

