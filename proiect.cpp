#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
using namespace std;

int tripletVal(const char *);
class ThreeChars{
public:
	char *chars;
	int introduceri;
	bool brokenInput = false;
	ThreeChars(){
		chars = new char[3]{ 'e', 'e', 'e' };
		introduceri = 0;
	}

	bool nextChar(){
		if (introduceri < 2){
			for (int i = 2; i > 0; i--){
				chars[i] = chars[i - 1];
			}
			introduceri++;
			return true;
		}
		else
			return false;
	}

	char* getChars(){
		if (introduceri == 1){
			chars[0] = chars[1];
			chars[1] = chars[2];
			chars[2] = '0';
		}
		for (int i = 0; i < 3; i++){
			if (chars[i] == 'e')
				chars[i] = '0';
		}

		return chars;
	}
	
};

istream& operator>>(istream& str, ThreeChars& e){
	char cache;
	do{
	} while (str.good() && str >> e.chars[0] && e.nextChar());
	return str;
}

bool isValid(string &input){
	int start = 0;
	if (input.c_str()[0] == '-'){
		start = 1;
	}

	for (int i = start; i < input.length(); i++){
		if (input.at(i) > '9' || input.at(i) < '0')
			return false;
	}
	return true;
}

class Unitati{
protected:
	char numar[3];
	bool isUnitati = true;
	string clasaValori = "";
	string unu = "unu";
public:
	Unitati(char *cifre){
		numar[0] = cifre[0];
		numar[1] = cifre[1];
		numar[2] = cifre[2];
		for (int i = 0; i < 3; i++)
			if (numar[i] == 'e')
				numar[i] = '0';
	}
	void citeste(){
		int valoare = tripletVal(numar);
		if (valoare == 1){
			cout << unu;
			return;
		}
		else if (valoare == 0){
			return;
		}
		switch (numar[2]){
		case '1':cout << "o suta "; break;
		case '2':cout << "doua sute "; break;
		case '3':cout << "trei sute "; break;
		case '4':cout << "patru sute "; break;
		case '5':cout << "cinci sute "; break;
		case '6':cout << "sase sute "; break;
		case '7':cout << "sapte sute "; break;
		case '8':cout << "opt sute "; break;
		case '9':cout << "noua sute "; break;
		}
		bool zecePlus = false;
		switch (numar[1]){
		case '1': if (numar[0] == '0') 
					cout << "zece"; 
				  else zecePlus = true; break;
		case '2': cout << "douazeci "; break;
		case '3': cout << "treizeci "; break;
		case '4': cout << "patruzeci "; break;
		case '5': cout << "cincizeci "; break;
		case '6': cout << "saizeci "; break;
		case '7': cout << "saptezeci "; break;
		case '8': cout << "optzeci "; break;
		case '9': cout << "nouazeci "; break;
		}
		if (!zecePlus && numar[1] != '0' && numar[0] != '0'){
			cout << "si ";
		}
		switch (numar[0]){
		case '1':
			if (zecePlus)
				cout << "un";
			else
				cout << "unu";  break;
		case '2': 
			if (isUnitati)
				cout << "doi";
			else
			    cout << "doua";
					  break;
		case '3': cout << "trei"; break;
		case '4':
			if (zecePlus)
				cout << "pai";
			else
				cout << "patru"; break;
		case '5': cout << "cinci"; break;
		case '6':
			if (zecePlus)
				cout << "sai";
			else
				cout << "sase "; break;
		case '7': cout << "sapte"; break;
		case '8': cout << "opt"; break;
		case '9': cout << "noua"; break;
		}
		if (zecePlus)
			cout << "sprezece";
		else if ((!isUnitati) && ((numar[1] > '1') || (numar[2] != '0'))){
			if ((numar[1] != '0') || (numar[2] != '0')){
				if (numar[0] != '0')
					cout << " ";
				cout << "de";
			}
		}
		if (!isUnitati && (tripletVal(numar)>0))
			cout << clasaValori;
	}
};

class Mii : public Unitati{
public:
	Mii(char *cifre) : Unitati(cifre) {
		clasaValori = " mii";
		unu = "o mie";
		isUnitati = false;
	}
};

class Milioane : public Unitati{
public:
	Milioane(char *cifre) : Unitati{ cifre }{
		clasaValori = " milioane";
		unu = "un milion";
		isUnitati = false;
	}
};

class Miliarde : public Unitati{
public:
	Miliarde(char *cifre) : Unitati{ cifre }{
		clasaValori = " miliarde";
		unu = "un miliard";
		isUnitati = false;
	}
};

void prelucrare(string &input){
	vector<char*> arrayClase;
	if (input.at(0) == '-'){
		cout << "minus ";
		input = input.substr(1);
	}
	istringstream stream{ input };
	int maxJ = ceil(input.length() / 3.0);
	if (input.length() % 3 == 1){
		char *cache = new char[3]{ '0', '0', '0' };
		stream >> cache[0];
		arrayClase.push_back(cache);
	}
	else if (input.length() % 3 == 2){
		char *cache = new char[3]{'0', '0', '0'};
		stream >> cache[1];
		stream >> cache[0];
		arrayClase.push_back(cache);
	}
	else maxJ++;
	for (int j = 0; j < maxJ; j++){
		ThreeChars preClass;
		stream >> preClass;
		arrayClase.push_back(preClass.getChars());
	}

	arrayClase.pop_back();
	for (int i = 0; i < arrayClase.size(); i++){
		Unitati* cititor = nullptr;
		switch (arrayClase.size() - i){
		case 1: {cititor = new Unitati(arrayClase[i]);  break; }
		case 2:{
			cititor = new Mii(arrayClase[i]); break;
		}
		case 3:{
			cititor = new Milioane(arrayClase[i]); break;
		}
		case 4: {
			cititor = new Miliarde(arrayClase[i]); break;
		}
		}
		if (cititor)
			cititor->citeste();
		if ((i != arrayClase.size() - 1) && (tripletVal(arrayClase[i + 1]) > 0))
			cout << ", ";
	}

}



int tripletVal(const char * triple){
	int res = 0;
	for (int i = 0; i < 3; i++){
		res += (triple[i]- '0') * pow(10, i + 1);
	}
	return res;
}


int main(){

	string input;

	cout << "Nr = ";
	cin >> input;
    
	if (isValid(input)){
        if (input == "0" || input == "-0" || input == "+0")
            cout << "zero";
        else
            prelucrare(input);
	}
	else
		cout << "Numarul are un format gresit. Posibil ati utilizat caractere interzise.";
    cout << endl;
}
