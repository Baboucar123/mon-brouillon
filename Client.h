#ifndef CLIENT_H
#define CLIENT_H

#include <string>
using namespace std;

class Client {

private:

string cin;
string nom;
string prenom;
string telephone;
int code_secret;

public:


Client(const string& cin, const string& nom, const string& prenom, const string& telephone, int code_secret);
bool verifierCodeSecret(int code) const; 
string getNom() const;
string getPrenom() const;
};

#endif
