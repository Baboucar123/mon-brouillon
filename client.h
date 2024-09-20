
#include <iostream>
using namespace std ;
#include <string>
#include "Compte.h"



class Client {
private:
    string nom;
    string prenom;
    Compte compte1; // Chaque client a deux comptes pour cet exemple
    Compte compte2;

public:
    Client(string n, string p, int code1, int code2);

    // Méthode pour afficher le menu d'opérations du client
    void menu_client();

    // Méthode pour gérer les opérations sur un compte
    void gerer_compte(Compte &compte);

    // Méthode pour faire un virement entre les comptes du client
    void virement_entre_comptes();

    // Nouvelle méthode : Demander si l'utilisateur souhaite faire une opération
    bool demander_operation();
};

