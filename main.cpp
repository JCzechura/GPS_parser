#include<iostream>
#include "GPS.h"
#include <fstream>
using namespace std;

int main()
{
	char ch;
	GPS my_gps;
	fstream fin("test.txt", fstream::in);
	while (fin >> noskipws >> ch)
	{
		if (ch == '$')
		{
			my_gps.char_counter = 0;
			if (my_gps.sentence_updated)
			{
				cout << my_gps.new_sentence << endl;
				my_gps.encode();
				cout << my_gps.enum_sentence << endl;

				if (my_gps.loc_updated)
				{
					cout << my_gps.locNS_deg_int << " deg " << my_gps.locNS_min_float << " ' " << my_gps.NS<< ",  " << my_gps.locWE_deg_int << " deg " << my_gps.locWE_min_float << " ' " << my_gps.WE << "  " <<endl;
				}

				if (my_gps.time_updated)
				{
					cout << my_gps.time_hour_int << " h " << my_gps.time_minute_int << " min " << my_gps.time_sec_int << " sec " << endl << endl;
				}
			}	
			//my_gps.encode();
			//cout << " koniec linii  - odkodowywanie" << endl;
		}
		else
		{
			my_gps.fillNewSentence(ch);
			//cout << ch; // Or whatever
			//cout << "___";
		}
			
	}
	my_gps.encode();
	system("pause");
	return 0;
}