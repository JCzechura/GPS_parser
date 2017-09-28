#include "GPS.h"
#include <iostream>
GPS::GPS()
{
	sentence_updated = false;
	loc_updated = false;
	time_updated = false;
	char_counter = 0;
}
bool GPS::encode()
{
	if (new_sentence[2] == 'G' &&  new_sentence[3] == 'G' && new_sentence[4] == 'A')
	{
		enum_sentence = GGA;
		if (checkData())
		{
			setLocation(parse(2), (parse(3) - 2), parse(4), (parse(5) - 2));;
			setTime();
		}

	}	
	else if (new_sentence[2] == 'R' &&  new_sentence[3] == 'M' && new_sentence[4] == 'C')
	{
		enum_sentence = RMC;
		if (checkData())
		{
			setLocation(parse(3), (parse(4) - 2), parse(5), (parse(6)-2));
			setTime();
		}
	}
	else
	{
		enum_sentence = NONE;
		loc_updated = false;
		time_updated = false;
	}

	clearNewSentence();
	return true;

}

void GPS::setLocation(int start_loc_SN, int end_loc_SN, int start_loc_WE, int end_loc_WE)
{
	NS = new_sentence[end_loc_SN + 2];
	WE = new_sentence [end_loc_WE + 2];
	float multip = 0.1;
	if ((end_loc_SN < start_loc_SN) || (end_loc_WE < start_loc_WE))
	{
		loc_updated = false;
		return;
	}
	else
	{
		locNS_deg_int = (new_sentence[start_loc_SN] - '0') * 10 + new_sentence[start_loc_SN+1] - '0';
		locWE_deg_int = (new_sentence[start_loc_WE] - '0') * 100 + (new_sentence[start_loc_WE+1] - '0')*10 + (new_sentence[start_loc_WE + 2] - '0');
		locNS_min_float = (new_sentence[start_loc_SN+2] - '0') * 10 + new_sentence[start_loc_SN+3] - '0';
		for (int i = start_loc_SN + 5; i <= end_loc_SN; i++)
		{
			locNS_min_float += (new_sentence[i] - '0') * multip;
			multip = multip * 0.1;
		}	
		multip = 0.1;
		locWE_min_float = (new_sentence[start_loc_WE + 3] - '0') * 10 + new_sentence[start_loc_WE + 4] - '0';
		for (int i = start_loc_WE + 6; i <= end_loc_WE; i++)
		{
			locWE_min_float += (new_sentence[i] - '0') * multip;
			multip = multip * 0.1;
		}
		loc_updated = true;
		return;
	}
}
bool GPS::checkData()
{
	bool good = false;
	if ((new_sentence[0] != 'G') && (new_sentence[1] != 'G'))
		return false;
	for (int i =2; i < 82; i++)
	{
		if (new_sentence[i] == '*')
			good = true;
	}
	if (!good) return false;
	if (enum_sentence == GGA)
	{
		if ((new_sentence[parse(6)] == '0') || (parse(6) == 0))
			return false;
		else return true;
	}
	else
	{
		if ((new_sentence[parse(2)] == 'V') || (parse(2) == 0))
			return false;
		else return true;
	}
}
void GPS::setTime()
{
	if (new_sentence[6] != ',')
	{
		time_hour_int = (new_sentence[6] - '0') * 10 + new_sentence[7] - '0';
		time_minute_int = (new_sentence[8] - '0') * 10 + new_sentence[9] - '0';
		time_sec_int = (new_sentence[10] - '0') * 10 + new_sentence[11] - '0';
		time_updated = true;
	}
}
bool GPS::fillNewSentence(char ch)
{
	new_sentence[char_counter] = ch;
	char_counter++;
	sentence_updated = true;
	return true;
}
void GPS::clearNewSentence()
{
	for (int i = 0; i < 82; i++)
		new_sentence[i] = 0;

}
int GPS::parse(int comma_number)
{
	int counter = 0;
	for (int i = 0; i < 82; i++)
	{
		if (new_sentence[i] == ',')
		{
			counter++;
			if (counter == comma_number)
				return (i + 1);
		}
	}
	return 0;
}

GPS::~GPS()
{
}
