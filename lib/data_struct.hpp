//should move to main program(server)
#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

using namespace std;
struct Data
{
    int user_id;
	char first_name[100];
	char last_name[100];
	char email[100];
	char subscription_time[50];
	char last_entry_time[50];
	unsigned long view_time;
    /* data */
};



#endif
