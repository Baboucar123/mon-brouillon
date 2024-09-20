#include <iostream>
#include "Client.h"

using namespace std;

int main() {
    // Création d'un client avec 2 comptes et leurs codes secrets respectifs
    Client client1("Baboucar", "Coly", 1234, 5678);

    // Affichage du menu du client
    client1.menu_client();

    return 0;
}
