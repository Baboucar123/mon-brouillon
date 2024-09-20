#include <iostream>
#include "Client.h"

using namespace std;

int choix;

Client::Client(string n, string p, int code1, int code2)
    : nom(n), prenom(p), compte1(1, 1000.0, code1), compte2(2, 500.0, code2) {
        
    }

bool Client::demander_operation() {
    char reponse;
    cout << "Souhaitez-vous effectuer une operation sur vos comptes ? (y/n) : ";
    cin >> reponse;
    
    if (reponse == 'y' || reponse == 'Y') {
        return true;
    } else {
        cout << "Au revoir et a la prochaine !" << endl;
        return false;
    }
}

void Client::menu_client() {

    cout << "Bienvenue " << prenom << " " << nom << " !\n";
    // Demander d'abord si l'utilisateur veut faire une opération
    if (!demander_operation()) {
        return;  // Si l'utilisateur dit non, on arrête ici.
    }

  
    
    cout << "Que souhaitez-vous faire ?\n";
    cout << "1. Gerer le compte 1\n";
    cout << "2. Gerer le compte 2\n";

    cin >> choix;

    if (choix == 1) {
        gerer_compte(compte1);
    } else if (choix == 2) {
        gerer_compte(compte2);
    } 
   
  else {
        cout << "Choix non valide.\n";
    }

    // Demander à nouveau si l'utilisateur veut faire une autre opération
    menu_client();  // Réappelle la méthode pour permettre une autre opération
}

void Client::gerer_compte(Compte &compte) {
    int code, option;
    double montant;

    cout << "Veuillez saisir le code secret du compte : ";
    cin >> code;

    if (compte.verifier_code(code)) {
        do {
            cout << "\nQue voulez-vous faire ?\n";
            cout << "1. Consulter le solde\n";
            cout << "2. Crediter le compte\n";
            cout << "3. Debiter le compte\n";
            cout << "4. effectuer un virement vers un autre compte\n";
            cout << "0. Quitter\n";
            cin >> option;

            switch (option) {
                case 1:
                    compte.consulter_solde();
                    break;
                case 2:
                    cout << "Montant a crediter : ";
                    cin >> montant;
                    compte.crediter(montant);
                    break;
                case 3:
                    cout << "Montant a debiter : ";
                    cin >> montant;
                    compte.debiter(montant);
                    break;
                    case 4 :
                    virement_entre_comptes() ;
                    break; 
                case 0:
                    cout << "Deconnexion du compte.\n";
                    break;
                default:
                    cout << "Option non valide.\n";
                    break;
            }
        } while (option != 0);
    } else {
        cout << "Code secret incorrect.\n";
    }
}

void Client::virement_entre_comptes() {
    
    double montant;
        cout << "Montant du virement : ";
        cin >> montant;
      

        if (choix== 1) {
            compte1.virement(compte2, montant);  // Virement de compte1 à compte2
        } else if (choix== 2) {
            compte2.virement(compte1, montant);  // Virement de compte2 à compte1
        } else {
            cout << "Option non valide.\n";
        }
    
}
