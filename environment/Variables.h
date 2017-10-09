#ifndef VARIABLES_INCLUDED
#define VARIABLES_INCLUDED

#define MAX_VARIABLES_COUNT 10

unsigned int  variables_count;
char* variables[MAX_VARIABLES_COUNT][2];

const char* lookup_variable( const char* key );  

void set_variable( const char* key , const char* value );

#endif // VARIABLES_INCLUDED
