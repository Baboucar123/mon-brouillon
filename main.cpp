#include <iostream>
#include "Client.h"

using namespace std;

int main() {

    // mot de passe pour acceder à son espace client 
    int pass_client , nombre_essai = 0 ;
    cout << "------------Bienvenue chez votre distributeur de billet  automatique---------"  <<endl ;

    while (nombre_essai < 3){
    cout << " veuillez saisir le mot de passe pour acceder a votre espace client " << endl ;
    cin >> pass_client ;

    if (pass_client == 8910){
    // Création d'un client avec 2 comptes et leurs codes secrets respectifs
    Client client1("Baboucar", "Coly", 1234, 5678);

    // Affichage du menu du client
    client1.menu_client();
    return 0;
}
else {

    cout << " le mot de passe saisi pouur accceder a l'espace client est incorrect " << endl;
}

nombre_essai++ ;

}
    return 0;
}
