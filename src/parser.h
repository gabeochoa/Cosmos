#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> output;
string input = "";
string token; 

/* declarations to allow arbitrary recursion */
void raw(void);
void inputmessage(void);
string dealerid(void);
string command(void);
int commodity(void);
int post(void);
int revoke(void);
int check(void);
int list(void);
int agress(void);

int isadigit(char c) {
  return (c >= '0' && c <= '9');
}

void error(void) { 
  printf("parse error\n");
  exit(1);
}

void getToken(void) { 
    /* tokens are words */
    cout << input << endl;
    size_t startpos = input.find_first_not_of(" \t\n\r");
    if( string::npos != startpos )
    {
        input = input.substr( startpos );
    }
    cout << input << endl;
    startpos = input.find_first_of(" \t\n\r");
    token = input.substr(0, startpos);
    cout << token << endl;
}

void raw(void) { 
  inputmessage();
  getToken();
  if (token.size() == 0) {
    return;
  } else {
    error();
  }
}

void inputmessage(void) { 
  output.push_back(dealerid());
  getToken();
  output.push_back(command());
}

string valid_dealers[] = {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
string dealerid(void) { 
  string result;
  for(string vd : valid_dealers)
  {
    if(token == vd)
      return vd;
  }
  std::cout << "ERROR: NO DEALER ID MATCH" << endl;
  error();
  return "";
}

string valid_commands[] = 
{
  ""
}
string command(void)
{

  return "";
}
/*
int commodity(void){}
int post(void){}
int revoke(void){}
int check(void){}
int list(void){}
int agress(void){}
*/

void parse() { 
  getToken(); /* get the first token */
  raw(); /* call the parsing procedure for the start symbol */
}

bool isValid(std::string& myin, std::vector<std::string>& myout)
{
    input = myin;
    output = myout;
    parse();
    return false;
}






