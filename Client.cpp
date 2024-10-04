#include "Client.h"

Client::Client(const string& cin, const string& nom, const string& prenom, const string& telephone, int code_secret)
    : cin(cin), nom(nom), prenom(prenom), telephone(telephone), code_secret(code_secret) {}

bool Client::verifierCodeSecret(int code) const { 

    return code_secret == code;

}

string Client::getNom() const {

    return nom;

}

string Client::getPrenom() const {

    return prenom;
    
}
