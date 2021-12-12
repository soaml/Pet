#include <iostream>
#include <iomanip>  
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct animals {
public:
	animals(string text) 
	{
		int result;
		result = text.find(',');
		names_of_owners = text.substr(0, result);
		text.erase(0, result + 1);
		if (text[0] == ' ') {
			text.erase(0, 1);
		}
		result = text.find(',');
		types_of_pets = text.substr(0, result);
		text.erase(0, result + 1);
		if (text[0] == ' ') {
			text.erase(0, 1);
		}
		result = text.find(',');
		if (result != 0) {
			names_of_pets = text.substr(0, result);
			text.erase(0, result + 1);
		}
		else {
			names_of_pets = "";
			text.erase(0, 1);
		}
		if (text[0] == ' ') {
			text.erase(0, 1);
		}
		age = stoi(text);
	}
	int age;
	string names_of_owners;
	string types_of_pets;
	string names_of_pets;	
};
bool comp(animals first, animals second) {
	return first.types_of_pets < second.types_of_pets;
}
int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string str;
	vector<animals> pets;
	
	if (!fin.is_open()) {
		cout << "error";
		return 1;
	}

	while (getline(fin, str)) {
		pets.push_back(animals(str));
	}

	bool done;
	do {
		cout << "Select an item from the menu: " << endl;
		cout << "1. Count the number of different types of pets each owner has: " << endl;
		cout << "2. For a specific type of pet, display all its owners and nicknames: " << endl;
		cout << "3. Determine how many species of pets have a certain nickname: " << endl;
		cout << "4. Display information about the age of the oldest and youngest animal of each species: " << endl;
		int menu;
		cin >> menu;

		if (menu == 1) {
			set <string> names_of_owners;
			map<string, set<string>> number_of_pets;

			for (animals item : pets) {
				number_of_pets[item.names_of_owners].insert(item.types_of_pets);
				names_of_owners.insert(item.names_of_owners);
			}
			for (const auto& name : names_of_owners) {
				fout << name << setw(2) << number_of_pets[name].size() << endl;
			}
			cout << endl;
		}
		else if (menu == 2) {

			string kind_of_pet;
			cout << "Enter  a specific type of pet: ";
			cin >> kind_of_pet;
			set <pair<string, string>> owner_and_nickname;
			
			for (animals item : pets) {
				if (item.types_of_pets == kind_of_pet) {
					owner_and_nickname.emplace(item.names_of_owners, item.names_of_pets);
				}
			}
			if (owner_and_nickname.empty())
				fout << "No owners and nicknames for such type of pet. " << endl;
			else{
				fout << "Owners: ";
				for (const auto& item : owner_and_nickname)
					fout << item.first << " , " << endl;
				fout << "Nicknames: ";
				for (const auto& item : owner_and_nickname)
					fout << item.second << " , " << endl;
				fout << endl;
			}
		}
		else if (menu == 3) {
			string nickname_of_pet;
			cout << "Enter  a specific nickname of pet: ";
			cin >> nickname_of_pet;
			set<string> pet_kind;

			for (animals item : pets) {
				if (item.names_of_pets == nickname_of_pet) {
					pet_kind.insert(item.types_of_pets);
				}
			}

			fout << pet_kind.size() << endl;
			fout << endl;
		}
		else if (menu == 4) {
			sort(pets.begin(), pets.end(), comp);

			for (int i = 0; i < pets.size(); i++) {				
				int age_min = pets[i].age;
				int age_max = pets[i].age;
				int j = i;

				while (j < pets.size() && (pets[i].types_of_pets == pets[j].types_of_pets)) {
					if (age_min > pets[j].age)
						age_min = pets[j].age;
					if (age_max < pets[j].age)
						age_max = pets[j].age;
					j++;			
				}
				fout << pets[i].types_of_pets << setw(2) << age_min << setw(2) << age_max << endl;
				i = j;
			}
		}
		else {
			cout << "Wrong choice of menu. " << endl;
		}
		cout << "Continue? (y/n)" << endl;
		int c;
		cin >> c;
		done = (c != 'y'); 

	} while (!done);
	system("pause");
	fin.close();
	fout.close();
	return 0;
}

