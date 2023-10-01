#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

const int maxSize = 100;
int userCount = 0;
int bookCount = 0;
int mgnCount = 0;
int journalCount = 0;
int ngbrLibCount = 0;
int recordCount = 0;

class User{
    public:
        string userName;
        bool userType; // 0 for studet , 1 for faculty
        string dateOfIssue;
        string itemName;
        string itemType;
};

class Book{
    public:
        int bookId;
        int bookCount;
        string isbn;
        string author;
        string title;
        Book(){}
};

class Magazine{
    public:
        int rank;
        string publication;
        double mgnPrice;
        Magazine(){}
};

class Journal{
    public:
        string journalName;
        int searchCount;
        Journal(){}
};

class NeighbourLibraries{
    public:
        string bookName;
        string ISBN;
        string author;
        int bookCount;
        int rackNo;
        string libraryName;
        string address;
        NeighbourLibraries(){}
        NeighbourLibraries(const string& bookName, const string& ISBN, const string& author, int count, int rack, const string& library, const string& address)
        : bookName(bookName), ISBN(ISBN), author(author), bookCount(count), rackNo(rack), libraryName(library), address(address) {}
};

class Record{
    public:
        string userName;
        string borrowLocation;
        string bookName;
        string dueDate;
        string borrowDate;
};

class Library{
    public:
        User userArray[maxSize];
        Book bookArray[maxSize];
        Magazine mgnArray[maxSize];
        Journal journalArray[maxSize];
        NeighbourLibraries neighbourLibArray[maxSize];
        Record recordArray[maxSize];
        Library() {
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("INDIAN", "1234567", "J K Shah", 1, 10, "SVK Library", "Saket");
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("Ramcharit Manas", "1234548", "Valmiki", 3, 10, "SVK Library", "Saket");
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("Mahabharat", "1234346", "VedVyas", 5, 3, "Guru Nanak Library", "Okhla");
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("Panchtantra", "1234549", "H G Bist", 12, 2, "Public Library", "Noida");
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("Himalayan", "1234534", "J K Shah", 1, 8, "Public Library", "Noida");
            neighbourLibArray[ngbrLibCount++] = NeighbourLibraries("Ek Safar", "1234472", "H G Shah", 67, 3, "SVK Library", "Saket");

            ifstream data;
            string temp;
            data.open("books.csv", ios::in);
            string line;
            getline(data, line);
            while(getline(data, line)){
                istringstream s(line);
                getline(s, temp, ',');
                istringstream s1(temp);
                getline(s1,temp,'"');
                getline(s1,temp,'"');
                bookArray[bookCount].bookId = stoi(temp);

                getline(s, temp, ',');
                getline(s, temp, ',');
                getline(s, temp, ',');
                getline(s, temp, ',');
                bookArray[bookCount].bookCount = stoi(temp);

                getline(s, temp, ',');
                bookArray[bookCount].isbn = temp;
                getline(s, temp, ',');

                getline(s, temp, ',');
                bookArray[bookCount].author = temp;

                getline(s, temp, ',');
                getline(s, temp, ',');
                bookArray[bookCount].title = temp;

                bookCount++;
            }

            ifstream data1;
            string temp1;
            data1.open("publications_rank.csv", ios::in);
            string line1;
            getline(data1, line1);
            while(getline(data1, line1)){
                istringstream s(line1);
                getline(s, temp1, ',');
                istringstream s1(temp1);                
                getline(s1,temp1,'"');
                getline(s1,temp1,'"');
                getline(s1,temp1,'"');
                getline(s1,temp1,'"');
                mgnArray[mgnCount].publication = temp1;

                getline(s, temp1, ',');
                istringstream s2(temp1);
                getline(s2,temp1,'"');
                getline(s2,temp1,'"');
                getline(s2,temp1,'"');
                mgnArray[mgnCount].rank = stoi(temp1);

                getline(s, temp1, ',');
                istringstream s3(temp1);
                getline(s3,temp1,'"');
                getline(s3,temp1,'"');
                getline(s3,temp1,'"');
                mgnArray[mgnCount].mgnPrice = stoi(temp1);

                mgnCount++;
            }

            ifstream data2;
            string temp2;
            data2.open("journals.csv", ios::in);
            string line2;
            while(getline(data2, line2)){
                istringstream s(line2); 
                getline(s, temp2, ',');              
                journalArray[journalCount].journalName = temp2;

                journalCount++;
            }
        }
        void userRegistration(){
            string name;
            string type;
            cout << "Please enter your name:";
            cin.ignore();
            getline(cin, name);
            cout << "Please enter you are Student or Faculty:";
            cin >> type;
            userArray[userCount].userName = name;
            if(type == "Student")
                userArray[userCount].userType = 0;
            else if(type == "Faculty")
                userArray[userCount].userType = 1;
            cout << "User " << userArray[userCount].userName << " is registered successfully." << endl;
            userCount++;
        }
        void showUsers(){
            string userName;
            int userFound = 0;
            cout << "Please enter your name:";
            cin.ignore();
            getline(cin, userName);
            for(int i=0; i<userCount; i++){
                if (userArray[i].userName == userName && userArray[i].userType == 1){
                    userFound = 1;
                    for(int j=0; j<userCount; j++){
                        cout << "Name:" << userArray[j].userName << "\t Type:" << ((userArray[j].userType==1)?"Faculty":"Student") << endl;  
                    }
                }
            }
            if(userFound == 0){
                cout << "You are not authorized to view the list of users." << endl;
            }
        }
        void borrowBook(){
            string userName;
            int userFound = 0, bookFound = 0;
            cout << "Please enter your name:";
            cin.ignore();
            getline(cin, userName);
            for(int i=0; i<userCount; i++){
                if (userArray[i].userName == userName){
                    userFound = 1;
                    string itemType, searchBy, itemName, itemAuthor, itemISBN, itemPublication,borrowYesNo, borrowPurchase;
                    cout << "What do you want? (Book, Magazine or Journal):";
                    cin >> itemType;
                    cout << "Do you want to search by Name,Author,ISBN or Publication?";
                    cin >> searchBy;
                    cin.ignore(); 
                    if (searchBy == "Name"){
                        cout << "Enter the Name:";
                        getline(cin, itemName);
                    }
                    else if (searchBy == "Author"){
                        cout << "Enter the Author:";
                        getline(cin, itemAuthor);
                    }
                    else if (searchBy == "ISBN"){
                        cout << "Enter the ISBN:";
                        cin >> itemISBN;
                    }
                    else if (searchBy == "Publication"){
                        cout << "Enter the Publication:";
                        getline(cin, itemPublication);
                    }
                    if (itemType == "Book"){
                        for(int j=0; j<bookCount; j++){
                            if(bookArray[j].bookCount > 0 && (bookArray[j].author == itemAuthor || bookArray[j].isbn == itemISBN || bookArray[j].title == itemName)){
                                bookFound = 1;
                                cout << "The book is available and in the position no. " << bookArray[j].bookId << endl;
                                cout << "Title: " << bookArray[j].title << endl;
                                cout << "Author: " << bookArray[j].author << endl;
                                cout << "Do you want to borrow this book or purchase this book?";
                                cin >> borrowPurchase;
                                if (borrowPurchase == "Borrow" || borrowPurchase == "borrow"){
                                    bookArray[j].bookCount -= 1;
                                    userArray[i].itemName = userArray[i].itemName + bookArray[j].title + ",";
                                    userArray[i].itemType = userArray[i].itemType + itemType + ",";
                                    time_t currentTime = std::time(nullptr);
                                    tm* currentDateTime = std::localtime(&currentTime);
                                    int year = currentDateTime->tm_year + 1900; 
                                    int month = currentDateTime->tm_mon + 1;   
                                    int day = currentDateTime->tm_mday;   
                                    userArray[i].dateOfIssue = userArray[i].dateOfIssue + to_string(day)+"/"+to_string(month)+"/"+to_string(year) + ",";
                                    string dueDate = (userArray[i].userType == 0) ? (to_string(day)+"/"+to_string((month+1)%12)+"/"+to_string((month+1)<=12?year:year+1)) : to_string(day)+"/"+to_string((month+6)%12)+"/"+to_string((month+6)<=12?year:year+1);
                                    cout << "Due date for this book is: " << dueDate + "," << endl;
                                }
                                else if (borrowPurchase == "Purchase" || borrowPurchase == "purchase"){
                                    bookArray[j].bookCount -= 1;
                                    userArray[i].itemName = userArray[i].itemName + bookArray[j].title + ",";
                                    userArray[i].itemType = userArray[i].itemType + itemType + ",";                                    
                                    cout << "This book is given to you." << endl;;
                                }
                                else
                                    break;
                            }
                        }
                        if(bookFound == 0){
                            cout << "Book not found." << endl;
                        }
                    }
                    if (itemType == "Magazine"){
                        for(int j=0; j<mgnCount; j++){
                            if(mgnArray[j].publication == itemPublication || mgnArray[j].publication == itemName){
                                bookFound = 1;
                                cout << "The magazine is available at the position " << mgnArray[j].rank << endl;
                                cout << "Publication: " << mgnArray[j].publication << endl;
                                cout << "Price: " << mgnArray[j].mgnPrice << endl;
                                cout << "Do you want to borrow this magazine?";
                                cin >> borrowYesNo;
                                if (borrowYesNo == "Yes" || borrowYesNo == "yes"){
                                    userArray[i].itemName = userArray[i].itemName + mgnArray[j].publication + ",";
                                    userArray[i].itemType = userArray[i].itemType + itemType + ",";
                                    time_t currentTime = std::time(nullptr);
                                    tm* currentDateTime = std::localtime(&currentTime);
                                    int year = currentDateTime->tm_year + 1900; 
                                    int month = currentDateTime->tm_mon + 1;   
                                    int day = currentDateTime->tm_mday;   
                                    userArray[i].dateOfIssue = userArray[i].dateOfIssue + to_string(day)+"/"+to_string(month)+"/"+to_string(year) + ",";
                                    string dueDate = (userArray[i].userType == 0) ? (to_string(day)+"/"+to_string((month+1)%12)+"/"+to_string((month+1)<=12?year:year+1)) : to_string(day)+"/"+to_string((month+6)%12)+"/"+to_string((month+6)<=12?year:year+1);
                                    cout << "Due date for this magazine is: " << dueDate + "," << endl;;
                                }
                                else
                                    break;
                            }
                        }
                        if(bookFound == 0){
                            cout << "Magazine not found." << endl;
                        }
                    }
                    if (itemType == "Journal"){
                        for(int j=0; j<journalCount; j++){
                            if(journalArray[j].journalName == itemName || journalArray[j].journalName == itemPublication){
                                bookFound = 1;
                                journalArray[j].searchCount = journalArray[j].searchCount > 0 ? (journalArray[j].searchCount + 1) : 1;
                                cout << "The journal is availabl." << endl;
                                cout << "Title: " << journalArray[j].journalName << endl;
                                cout << "Do you want to take this journal?";
                                cin >> borrowYesNo;
                                if (borrowYesNo == "Yes" || borrowYesNo == "yes"){
                                    userArray[i].itemName = userArray[i].itemName + journalArray[j].journalName + ",";
                                    userArray[i].itemType = userArray[i].itemType + itemType + ",";
                                    cout << "The journal is given to you." << endl;;
                                }
                                else
                                    break;
                            }
                        }
                        if(bookFound == 0){
                            cout << "Journal not found." << endl;
                        }
                    }
                    break;
                }  
            }
            if(userFound == 0){
                cout << "User not found. Either entered user name is incorrect or not a registered user." << endl;
            }
        }
        void borrowOnLoan(){
            string userName;
            int userFound = 0, bookFound = 0;
            cout << "Please enter your name:";
            cin.ignore();
            getline(cin, userName);
            for(int i=0; i<userCount; i++){
                if (userArray[i].userName == userName){
                    userFound = 1;
                    string searchBy, itemName, itemAuthor, itemISBN, borrowYesNo;
                    cout << "Do you want to search book by Name,Author or ISBN?";
                    cin >> searchBy;
                    cin.ignore(); 
                    if (searchBy == "Name"){
                        cout << "Enter the Name:";
                        getline(cin, itemName);
                    }
                    else if (searchBy == "Author"){
                        cout << "Enter the Author:";
                        getline(cin, itemAuthor);
                    }
                    else if (searchBy == "ISBN"){
                        cout << "Enter the ISBN:";
                        cin >> itemISBN;
                    }
                    for(int j=0; j<ngbrLibCount; j++){
                        if(((neighbourLibArray[j].bookName == itemName) || (neighbourLibArray[j].ISBN == itemISBN) || (neighbourLibArray[j].author == itemAuthor)) && neighbourLibArray[j].bookCount > 0){
                            bookFound = 1;
                            cout << "The book is available on Rack No. " << neighbourLibArray[j].rackNo << " in " << neighbourLibArray[j].libraryName << " at " << neighbourLibArray[j].address << endl;
                            cout << "Title: " << neighbourLibArray[j].bookName << endl;
                            cout << "Author: " << neighbourLibArray[j].author << endl;
                            cout << "Do you want to borrow this book?";
                            cin >> borrowYesNo;
                            if (borrowYesNo == "Yes" || borrowYesNo == "yes"){
                                neighbourLibArray[j].bookCount -= 1;
                                recordArray[recordCount].userName = userArray[i].userName;
                                recordArray[recordCount].bookName = neighbourLibArray[j].bookName;
                                recordArray[recordCount].borrowLocation = "IIIT-Delhi";
                                time_t currentTime = std::time(nullptr);
                                tm* currentDateTime = std::localtime(&currentTime);
                                int year = currentDateTime->tm_year + 1900; 
                                int month = currentDateTime->tm_mon + 1;   
                                int day = currentDateTime->tm_mday;   
                                recordArray[recordCount].borrowDate = to_string(day)+"/"+to_string(month)+"/"+to_string(year);
                                string dueDate = (userArray[i].userType == 0) ? (to_string((day+7)%30)+"/"+to_string((day+7)<=30?(month+1)%12:(month+2)%12)+"/"+to_string(((month+1)<=12 || (month+2)<=12)?year:year+1)) : to_string((day+7)%30)+"/"+to_string((day+7)<=30?(month+6)%12:(month+7)%12)+"/"+to_string(((month+6)<=12 || (month+7)<=12)?year:year+1);
                                recordArray[recordCount].dueDate = dueDate;
                                recordCount++;
                                cout << "Due date for this book is: " << dueDate + "," << endl;
                            }
                            else
                                break;
                        }
                    }
                    if(bookFound == 0){
                        cout << "Book not found." << endl;
                    }              
                }  
            }
            if(userFound == 0){
                cout << "User not found. Either entered user name is incorrect or not a registered user." << endl;
            }
        }
        void viewRecord(){
            string userName;
            int userFound = 0;
            cout << "Please enter your name:";
            cin.ignore();
            getline(cin, userName);
            for(int i=0; i<userCount; i++){
                if (userArray[i].userName == userName && userArray[i].userType == 1){
                    userFound = 1; 
                    for(int j=0; j<recordCount; j++){
                        cout << "User Name:" << recordArray[j].userName << "\tBook Name:" << recordArray[j].bookName << "\tBorrow Location:" << recordArray[j].borrowLocation << "\tBorrow Date:" << recordArray[j].borrowDate << "\tDue Date:" << recordArray[j].dueDate << endl; 
                    }
                }
            }
            if(userFound == 0){
                cout << "You are not authorized to view the list of users." << endl;
            }
        }
        void mostRequestedJournal(){
            int mostUsed,max=INT_MIN;
            for(int i=0; i<journalCount; i++){
                if(journalArray[i].searchCount > max){
                    max = journalArray[i].searchCount;
                    mostUsed = i;
                }
            }
            cout << "Institute will subscribe : " << journalArray[mostUsed].journalName << endl;
        }
};

int main() {
    int choice;
    Library lb;    
    cout << "Welcome !!" << endl;
    while (true){
        cout << endl;
        cout << "1. For User Registration" << endl;
        cout << "2. To Borrow/Purchase Book" << endl;
        cout << "3. To View Users" << endl;
        cout << "4. To Borrow Books on Loan" << endl;
        cout << "5. To View the Records of Borrow on Loan" << endl;
        cout << "6. To Check Most Requested Journal" << endl;
        cout << "7. For Exit" << endl;
        cout << "Please enter the preference from the above list:"; 
        cin >> choice;
        switch(choice){
            case 1: // Registration
                lb.userRegistration();
                break;
            case 2: // Borrow
                lb.borrowBook();
                break;
            case 3: // Users
                lb.showUsers();
                break;
            case 4: // Loan
                lb.borrowOnLoan();
                break;
            case 5: // Record
                lb.viewRecord();
                break;
            case 6: // Journal Subscription
                lb.mostRequestedJournal();
                break;
            case 7: // Exit
                return 0;
            default: // Wrong
                cout << "You entered wrong choice." << endl;
                break;
        }
    }
    return 0;
}
