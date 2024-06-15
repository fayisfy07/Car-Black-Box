#ifndef MAIN
#define MAIN

#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
#define MENU_ENTER              3

#define VIEWLOG                 0
#define DOWNLOADLOG             1
#define CLEARLOG                2
#define SETTIME                 3
#define CHANGEPASS              4

#define TIME_ARR_SIZE           9
#define PASS_SIZE               5
#define EVENT_ARR_SIZE          11

void dashboard( void );               
void store_event( int event_index );
void password();
char password_compare( char *key, char *pwd);
void menu();
void view_logs();
void download_log();
void clear_log();
void settime();
void save_time_to_RTC();
void change_pass(char );
void store_password( char *pwd );
void read_password_eeprom( char *password );
void get_time(void);

#endif