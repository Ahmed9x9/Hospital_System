#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cctype>
#include <climits>

using namespace std; 
//----------------------------Global(s)-------------------------------------------
const int MAX_SIZE = 20;
const int sizemedic = 2;
int count = 0;

//----------------------Helper Functions for Input Validation-------------------------
int getValidInt(const string& prompt, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                return value;
            }
            cout << "Please enter a number between " << min << " and " << max << endl;
        } else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

char getValidGender(const string& prompt) {
    char g;
    while (true) {
        cout << prompt;
        cin >> g;
        g = toupper(g);
        if (g == 'M' || g == 'F') {
            return g;
        }
        cout << "Invalid input! Please enter M or F only." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
//------------------------------structs------------------------
struct Date{
	int day;
	int month;
	int year;
};
struct Medic{
	string medicname;
	double dose;
	double dose_perday; 
};
struct Person{
	string ID;
	string NAME;
	Date DOB;
	char gender;
	string Clinic;	
	Medic medic[sizemedic];
};
Person person[MAX_SIZE];
//----------------------prototypes-------------------------
void menu(int &);
void add_record();
void sort_records();
void show_record(int i);
void print_records();
void print_G_records(char gender);
void print_C_records();
int search();
int search(string id);
void update_record();
void delete_record();
//void Report();
//void ReadFile();
void log();
void writee();
void writee(int x);
void read();
//-------------------------main----------------------------
int main(){
	int choice,x1;
	//do-while-loop
	read();
	do{
		log();
		
		menu(choice);
		switch(choice){
			case -1://exit
				choice = -1;
				log();
				
				break;
			case 1: //Add new item
				add_record();
				
				break;
			case 2:
				delete_record();
				break;
			case 3:
				update_record();
				break;
			case 4:
				print_records();
				break;
			case 5:
				x1=search();
				if(x1>=0){
					cout<<"\nFound it!"<<" index: "<<x1;
					show_record(x1);
				}
				else{
					cout<<"\n Not Found!";
				}
				break;
			case 6:
				sort_records();	
				break;
			case 7:
				char G;
				G = getValidGender("Enter the gender (M/F): ");
				print_G_records(G);


				break;
			case 8:
				print_C_records();
				break;
			case 9: // save
				writee(choice);
				break;
			case 10:
				writee();
				break;
			default:cout<<"\nplease choose in rage of menu\n";
		}
		
		
		
	}while(choice!=-1);
	
return 0;}
//-----------------------------functions-----------------
void menu(int & choice)
{
  cout<<"\n\nPlease choose a task:"
    <<"\n1  - Add a person"
    <<"\n2  - Delete a person"
    <<"\n3  - Update a person"
    <<"\n4  - View all records"
    <<"\n5  - Find the person by ID"
    <<"\n6  - Sort records by max ID "
    <<"\n7  - Show person by gender"   
    <<"\n8  - Show person by Clinic"
    <<"\n9  - Save Hospital Data (append to existing)"
    <<"\n10 - Save Hospital Data (overwrite)"
    <<"\n\n(-1) - Exit"
    <<"\n*****";
  
  while (true) {
    cout << "\n>> ";
    if (cin >> choice) {
      return;
    } else {
      cout << "Invalid input! Please enter a number." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
    }
  }
}//menu end



void add_record(){
	// Check if we have room for more records
	if(count >= MAX_SIZE){
		cout << "\nError: Maximum number of records (" << MAX_SIZE << ") reached!\n";
		return;
	}
	
	int C, checkid;
	cout << "*\n\nEnter new patient records\n\n*";
	
	// Get valid ID
	while(true){
		cout << "\n\nEnter ID of patient (10 digits): ";
		cin >> person[count].ID;
		
		if(person[count].ID.length() != 10){
			cout << "Please enter exactly 10 digits.";
			continue;
		}
		
		// Check if ID contains only digits
		bool validID = true;
		for(int i = 0; i < 10; i++){
			if(!isdigit(person[count].ID[i])){
				validID = false;
				break;
			}
		}
		if(!validID){
			cout << "ID must contain only digits.";
			continue;
		}
		
		checkid = search(person[count].ID);
		if(checkid != -1){
			cout << "\n\nThe ID is already used..\n";
			continue;
		}
		break;
	}
	
	// Get name
	cin.ignore(10000, '\n');
	cout << "Enter name of patient: ";
	getline(cin, person[count].NAME);
	
	// Get DOB with validation
	cout << "\nEnter DOB of patient:\n";
	person[count].DOB.day = getValidInt("Day (1-31): ", 1, 31);
	person[count].DOB.month = getValidInt("Month (1-12): ", 1, 12);
	person[count].DOB.year = getValidInt("Year (1900-2025): ", 1900, 2025);
	
	// Get gender with validation
	person[count].gender = getValidGender("Enter patient gender (M/F): ");
	
	// Get clinic
	cout << "\nEnter patient clinic:\n";
	cout << "1. Dental\n2. Respiratory\n3. Family medicine\n4. Vaccine\n5. Other\n";
	C = getValidInt("Choose (1-5): ", 1, 5);
	
	switch(C){
		case 1: person[count].Clinic = "Dental"; break;
		case 2: person[count].Clinic = "Respiratory"; break;
		case 3: person[count].Clinic = "Family medicine"; break;
		case 4: person[count].Clinic = "Vaccine"; break;
		case 5:
			cin.ignore(10000, '\n');
			cout << "Enter name of clinic: ";
			getline(cin, person[count].Clinic);
			break;
	}
	
	// Get medications
	cout << "\nEnter patient Medications:\n";
	for(int i = 0; i < sizemedic; i++){
		cout << "\n--- Medication #" << i+1 << " ---\n";
		cout << "Enter medication name: ";
		cin >> person[count].medic[i].medicname;
		person[count].medic[i].dose = getValidDouble("Enter dose: ");
		person[count].medic[i].dose_perday = getValidDouble("Enter doses per day: ");
	}
	
	count++;
	cout << "\n*** Patient added successfully! ***\n\n";
}//add record end



void sort_records()
{
	
	bool ordered=false;
	Person temp;
	
	if (count < 2) 
		cout<<"\nNothing to sort!";
		
    for(int i = 0; i < count-1 && ordered==false ; ++i) 
    {	 
		ordered=true;
		for(int j = 0; j < count-1;++j)
  	     	if(person[j].ID < person[j+1].ID)     
	     	{        
			ordered=false;
	            temp = person[j];
	            person[j] = person[j+1];
	            person[j+1] = temp;
	    	}
 	}
 	cout<<"*\n\nSorting is Done\n\n*";
 }//sort record end
 
 
 
void print_records()
{
	if(count==0){
		cout<<"there is no records";
		return;
	}
	for (int i=0;i<count;i++)
	     show_record(i);
	     
	return;
}//print record end



void show_record(int i)
{
	cout<<"\n\npatient :"<<(i+1)
	    <<"\n\tName  :"<<person[i].NAME
	    <<"\n\tID    :"<<person[i].ID
	    <<"\n\tGender:"<<person[i].gender
        <<"\n\tDate of Birth (DD-MM-YYYY): "<<person[i].DOB.day<<"/"<<person[i].DOB.month<<"/"<<person[i].DOB.year
        <<"\n\tClinic:"<<person[i].Clinic
		<<"\n\tMedic's:";
	for(int j=0;j<sizemedic;j++){
		cout<<"\n\t\t#"<<j+1<<" Medic: "<<person[i].medic[j].medicname<<"	Dose: "<<person[i].medic[j].dose<<"	Perday: "<<person[i].medic[j].dose_perday<<endl;
	}
	
	
	    cout<<"\n------------------------------------------------";
}//show record end



void print_G_records(char gender)
{
	bool flag = false;
	cout<<"*\n\nPrinting By Gender\n\n*";
	for (int i=0;i<count;i++)
	    if (person[i].gender==gender){
	    	show_record(i);
	    	flag = true;
		}
	if(flag==false){
		cout<<"\n\nThe character is wrong or there is none\n";
	}
   
}//prind by gender end



void print_C_records()
{
	cout<<"*\n\nPrinting By Clinic\n\n*";
	string ccl;
	cout<<"\nEnter Clinic name:";
	cin>>ccl;
	bool flag = false;
	for (int i=0;i<count;i++)
	     if (person[i].Clinic==ccl){
		 	show_record(i);
			flag = true;
		 }
	if(flag==false){
		cout<<"\nThe clinic is wrong or there is none..\n";
	}
}//print by clinic end


void delete_record()
{
	
	if(count==0){
		cout<<"there is no records";
		return;
	}
	int index=search();
	if (index<0)
	{
		cout<<"\nNot found!!\n";
		return;  
	}
	
	
	for (int j=index; j< count-1; j++) 
		person[j]=person[j+1];
				
	count--;
	cout<<"\nPatient deleted successfully. \n";
}//delete record end



void update_record()
{
	if(count == 0){
		cout << "There are no records to update.";
		return;
	}
	
	int index = search();
	if (index < 0){
		cout << "\nNot found!!\n";
		return;  
	}
	
	int C;
	cout << "*\n\nUpdate patient record\n\n*";
	
	// Get valid ID
	while(true){
		cout << "\n\nEnter new ID of patient (10 digits): ";
		cin >> person[index].ID;
		
		if(person[index].ID.length() != 10){
			cout << "Please enter exactly 10 digits.";
			continue;
		}
		
		// Check if ID contains only digits
		bool validID = true;
		for(int i = 0; i < 10; i++){
			if(!isdigit(person[index].ID[i])){
				validID = false;
				break;
			}
		}
		if(!validID){
			cout << "ID must contain only digits.";
			continue;
		}
		break;
	}
	
	// Get name
	cin.ignore(10000, '\n');
	cout << "Enter name of patient: ";
	getline(cin, person[index].NAME);
	
	// Get DOB with validation
	cout << "\nEnter DOB of patient:\n";
	person[index].DOB.day = getValidInt("Day (1-31): ", 1, 31);
	person[index].DOB.month = getValidInt("Month (1-12): ", 1, 12);
	person[index].DOB.year = getValidInt("Year (1900-2025): ", 1900, 2025);
	
	// Get gender with validation
	person[index].gender = getValidGender("Enter patient gender (M/F): ");
	
	// Get clinic
	cout << "\nEnter patient clinic:\n";
	cout << "1. Dental\n2. Respiratory\n3. Family medicine\n4. Vaccine\n5. Other\n";
	C = getValidInt("Choose (1-5): ", 1, 5);
	
	switch(C){
		case 1: person[index].Clinic = "Dental"; break;
		case 2: person[index].Clinic = "Respiratory"; break;
		case 3: person[index].Clinic = "Family medicine"; break;
		case 4: person[index].Clinic = "Vaccine"; break;
		case 5:
			cin.ignore(10000, '\n');
			cout << "Enter name of clinic: ";
			getline(cin, person[index].Clinic);
			break;
	}
	
	// Get medications
	cout << "\nEnter patient Medications:\n";
	for(int i = 0; i < sizemedic; i++){
		cout << "\n--- Medication #" << i+1 << " ---\n";
		cout << "Enter medication name: ";
		cin >> person[index].medic[i].medicname;
		person[index].medic[i].dose = getValidDouble("Enter dose: ");
		person[index].medic[i].dose_perday = getValidDouble("Enter doses per day: ");
	}
	
	cout << "\n*** Patient updated successfully! ***\n";
}//update record end



int search()
{
	string id;
	while(true){
		cout<<"\n\nEnter ID of patient to search: ";
		cin>>id;
		if(id.length()<10 || id.length()>10){
			cout<<"please Enter 10 numbers only";
			continue;
		}
		break;
	}

	for (int i=0;i<count;i++)
		if (person[i].ID==id)
			return i;	
	
	return -1;  
}//search record end
int search(string id)
{
	for (int i=0;i<count;i++)
		if (person[i].ID==id)
			return i;	
	
	return -1;  
}//search id + overload




void writee(){
	
	ofstream outFile;
	outFile.open("Records.txt",ios::out);
	if(outFile.is_open()){
		for(int i = 0;i<count;i++){
			outFile<<person[i].ID<<"#";
			outFile<<person[i].NAME<<"#";
			outFile<<person[i].gender<<"#";
			outFile<<person[i].DOB.day<<"#";
			outFile<<person[i].DOB.month<<"#";
			outFile<<person[i].DOB.year<<"#";
			outFile<<person[i].Clinic<<"#";
			for(int j = 0;j<sizemedic;j++){
				outFile<<person[i].medic[j].medicname<<"#";
				outFile<<person[i].medic[j].dose<<"#";
				if(j!=1){
					outFile<<person[i].medic[j].dose_perday<<"#";
				}
				else{
					outFile<<person[i].medic[j].dose_perday<<endl;
				}
			}

		}

		outFile.close();
	}
	cout<<"*\n\ndelete old and save the new is done\n\n*\n";
}
void writee(int x){
	
	ofstream outFile;
	outFile.open("Records.txt",ios::app);
	if(outFile.is_open()){
		for(int i = 0;i<count;i++){
			outFile<<person[i].ID<<"#";
			outFile<<person[i].NAME<<"#";
			outFile<<person[i].gender<<"#";
			outFile<<person[i].DOB.day<<"#";
			outFile<<person[i].DOB.month<<"#";
			outFile<<person[i].DOB.year<<"#";
			outFile<<person[i].Clinic<<"#";
			for(int j = 0;j<sizemedic;j++){
				outFile<<person[i].medic[j].medicname<<"#";
				outFile<<person[i].medic[j].dose<<"#";
				if(j!=1){
					outFile<<person[i].medic[j].dose_perday<<"#";
				}
				else{
					outFile<<person[i].medic[j].dose_perday<<endl;
				}
			}

		}

		outFile.close();
	}
	cout<<"*\n\nwrite with old data is done\n\n*";
}
void read(){
	ifstream inFile;
	inFile.open("Records.txt",ios::in);
	if(inFile.is_open()){
			while(getline(inFile,person[count].ID,'#')){
			getline(inFile,person[count].NAME,'#');
			inFile.get(person[count].gender);
			inFile.ignore(1);
			inFile>>person[count].DOB.day;
			inFile.ignore(1);
			inFile>>person[count].DOB.month;
			inFile.ignore(1);
			inFile>>person[count].DOB.year;
			inFile.ignore(1);
			getline(inFile,person[count].Clinic,'#');
			for(int i = 0; i<sizemedic;i++){
				getline(inFile,person[count].medic[i].medicname,'#');
				inFile>>person[count].medic[i].dose;
				inFile.ignore(1);
				inFile>>person[count].medic[i].dose_perday;
				inFile.ignore(1);
			
			}
			
			count++;
			}
	inFile.close();
	}
	cout<<"\nNumber of records readed: "<<count<<endl;
}
void log(){
	ofstream outFile;
	outFile.open("Log.text",ios::app);
	
	if(outFile.is_open()){
		if(count>0){
			time_t now = time(0);
    		string dt = ctime(&now);
    		outFile<<"closed: (Edited): ";
    		outFile<<dt<<endl;
    		outFile<<"Number of Record:"<<count<<endl;
    		
		}
		else{
			time_t now = time(0);
    		string dt = ctime(&now);
    		outFile<<"opened: ";
    		outFile<<dt<<endl;
		}
		outFile<<"\n-------------------------------------------------------------------\n";
		outFile.close();
	}

}
