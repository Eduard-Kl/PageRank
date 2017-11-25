#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <set>
#include <cstdlib>

using namespace std;

int main(void){

	string link = "", outLink = "";
	unsigned int brojac = 0;
	map<string, set<string> > kolekcija;
	map<string, set<string> >::iterator it;
	set<string>::iterator setIterator;
	map<string, unsigned int> index;

	ifstream inputLinkovi("Linkovi.txt");

	if(inputLinkovi.is_open()){

		while(getline(inputLinkovi, link)){

			kolekcija[link];

			while(1){

				getline(inputLinkovi, outLink);

				if(index.find(link) == index.end()){
					index[link] = brojac++;
					//cout << link << " NJEGOV INDEX: " << index[link]<< endl;
				}
				if(index.find(outLink) == index.end()){
					index[outLink] = brojac++;
					//cout << outLink << " NJEGOV INDEX: " << index[outLink]<< endl;
				}

				if(outLink ==  "---") break;
				kolekcija[link].insert(outLink);				
			}
		}

	}else{
		cout << "Greška prilikom otvaranja datoteke." << endl;
		return EXIT_FAILURE;
	}
/*
	for(it=kolekcija.begin(); it!=kolekcija.end(); it++){
		cout << it->first << " POKAZUJE NA " << endl;
		for(setIterator=(it->second).begin(); setIterator!=(it->second).end(); setIterator++){
			cout << *setIterator << endl;
		}
		cout << "VELICINA SET-A: " << it->second.size() << endl << endl;
	}
	cout << endl;
*/
	const unsigned int n = index.size(); cout << endl << n;
	unsigned int i=0, j=0, N[n] = {0};
	double Q[n][n] = {};

	for(it=kolekcija.begin(); it!=kolekcija.end(); it++){
		N[index[it->first]] = (it->second).size();
		//cout << (it->second).size() << " " << index[it->first] << endl;
	}
/*
	for(i=0; i<n; i++){
		cout << N[i] << " ";
	}
	cout << endl << endl;
*/
	for(it=kolekcija.begin(); it!=kolekcija.end(); it++){
		for(setIterator=(it->second).begin(); setIterator!=(it->second).end(); setIterator++){

			i = index[it->first];
			j = index[*setIterator];
			//cout << it->first << " " << i << ", " << *setIterator << " " << j << endl;
			if((it->second).size() != 0){
				Q[i][j] = 1.0 / (double) (it->second).size();
				/*
				cout << "POKAZUJE: index(" << it->first << ") = " << i << endl;
				cout << "index(" << *setIterator << ") = " << j << endl;
				cout << "VELICINA: " << (it->second).size() << endl << endl;
				*/
			}
		}
	}


	// -------------------------------------------------------------
	// Ispis
	ofstream izlaz("Matrica.txt");

	// Postaviti veću vrijednost ovdje ako želimo veću preciznost
	izlaz.precision(10);

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			izlaz << Q[i][j] << "\t";
		}
		izlaz << endl;
	}

    izlaz.close();
    inputLinkovi.close();

	return EXIT_SUCCESS;
}



/*
Primjer iz članka:

prva
---
druga
prva
treca
---
treca
prva
druga
cetvrta
---
cetvrta
peta
sesta
---
peta
cetvrta
sesta
---
sesta
cetvrta
---
*/
