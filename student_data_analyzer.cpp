#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX = 100;

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

Student students[MAX];
int count = 0;
bool isSortedByRoll = false;

int linearSearchByRoll(int roll);

void addStudent() {
    if (count >= MAX) {
        cout << "Storage full! Cannot add more students.\n";
        return;
    }

    Student s;

    do {
        cout << "Enter Roll No.: ";
        cin >> s.rollNo;
        if (s.rollNo <= 0)
            cout << "Roll Number must be positive.\n";
    } while (s.rollNo <= 0);

    if (linearSearchByRoll(s.rollNo) != -1) {
        cout << "Roll Number already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    do {
        cout << "Enter Marks (0-100): ";
        cin >> s.marks;
        if (s.marks < 0 || s.marks > 100)
            cout << "Invalid marks! Please enter marks between 0 and 100.\n";
    } while (s.marks < 0 || s.marks > 100);

    students[count++] = s;
    isSortedByRoll = false;
    cout << "Student added successfully!\n";
}

void displayAll() {
    if (count == 0) {
        cout << "No records to display.\n";
        return;
    }
    cout << "\n" << left << setw(10) << "Roll No" << setw(20) << "Name" << setw(10) << "Marks\n";
    cout << "---------------------------------------------\n";
    for (int i=0;i<count;i++)
        cout << left << setw(10) << students[i].rollNo << setw(20) << students[i].name << setw(10) << students[i].marks << "\n";
}

int linearSearchByRoll(int roll){
    for(int i=0;i<count;i++) if(students[i].rollNo==roll) return i;
    return -1;
}
int linearSearchByName(const char name[]){
    for(int i=0;i<count;i++) if(strcmp(students[i].name,name)==0) return i;
    return -1;
}
int binarySearchByRoll(int roll){
    int low=0,high=count-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(students[mid].rollNo==roll) return mid;
        if(students[mid].rollNo<roll) low=mid+1;
        else high=mid-1;
    }
    return -1;
}
void bubbleSortByMarks(){
    for(int i=0;i<count-1;i++){
        bool swapped=false;
        for(int j=0;j<count-1-i;j++){
            if(students[j].marks<students[j+1].marks){
                Student t=students[j]; students[j]=students[j+1]; students[j+1]=t; swapped=true;
            }
        }
        if(!swapped) break;
    }
    isSortedByRoll=false;
    cout<<"Sorted by Marks (Bubble Sort, descending).\n";
}
void selectionSortByRoll(){
    for(int i=0;i<count-1;i++){
        int min=i;
        for(int j=i+1;j<count;j++)
            if(students[j].rollNo<students[min].rollNo) min=j;
        if(min!=i){ Student t=students[i]; students[i]=students[min]; students[min]=t; }
    }
    isSortedByRoll=true;
    cout<<"Sorted by Roll No (Selection Sort, ascending).\n";
}
void printMenu(){
    cout<<"\n===== Student Data Analyzer =====\n";
    cout<<"1. Add Student\n2. Display All Students\n3. Linear Search by Roll No\n4. Linear Search by Name\n5. Sort by Roll No (Selection Sort)\n6. Binary Search by Roll No\n7. Sort by Marks (Bubble Sort)\n8. Exit\nEnter your choice: ";
}
int main(){
    int choice;
    do{
        printMenu();
        cin>>choice;
        switch(choice){
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3:{
                int roll; cout<<"Enter Roll No to search: "; cin>>roll;
                int idx=linearSearchByRoll(roll);
                if(idx!=-1) cout<<"Found: "<<students[idx].name<<" | Marks: "<<students[idx].marks<<"\n";
                else cout<<"Student not found.\n"; break;}
            case 4:{
                char name[50];
                cin.ignore();
                cout<<"Enter Name to search: ";
                cin.getline(name,50);
                int idx=linearSearchByName(name);
                if(idx!=-1) cout<<"Found: Roll No "<<students[idx].rollNo<<" | Marks: "<<students[idx].marks<<"\n";
                else cout<<"Student not found.\n"; break;}
            case 5: selectionSortByRoll(); displayAll(); break;
            case 6:{
                if(!isSortedByRoll){ cout<<"Please sort by Roll Number first using Option 5.\n"; break; }
                int roll; cout<<"Enter Roll No to search: "; cin>>roll;
                int idx=binarySearchByRoll(roll);
                if(idx!=-1) cout<<"Found: "<<students[idx].name<<" | Marks: "<<students[idx].marks<<"\n";
                else cout<<"Student not found.\n"; break;}
            case 7: bubbleSortByMarks(); displayAll(); break;
            case 8: cout<<"Exiting program. Goodbye!\n"; break;
            default: cout<<"Invalid choice, try again.\n";
        }
    }while(choice!=8);
    return 0;
}







































