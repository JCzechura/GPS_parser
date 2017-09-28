#pragma once
class GPS
{
	enum sentence { GGA, RMC, NONE };
public:
	char new_sentence[82];
	bool loc_updated;
	bool time_updated;
	bool sentence_updated;
	int locWE_deg_int;
	float locWE_min_float;
	int locNS_deg_int;
	float locNS_min_float;
	char NS;
	char WE;
	int time_hour_int;
	int time_minute_int;
	int time_sec_int;
	int char_counter;
	sentence enum_sentence;

	GPS();
	bool encode();
	void setLocation(int start_loc_SN, int end_loc_SN, int start_loc_WE, int end_loc_WE);
	bool checkData();
	void setTime();
	bool fillNewSentence(char ch);
	void clearNewSentence();
	int parse(int comma_number);
	~GPS();
};

