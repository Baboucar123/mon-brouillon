#include <iostream>
#include "Compte.h"

using namespace std;

Compte::Compte(int num, double solde_initial, int code) 
    : numero_compte(num), solde(solde_initial), code_secret(code) {}

bool Compte::verifier_code(int code) {
    return code == code_secret;
}

void Compte::consulter_solde() {
    cout << "Le solde du compte " << numero_compte << " est de " << solde << " €." << endl;
}

void Compte::crediter(double montant) {
    solde += montant;
    cout << montant << " € ont été crédités sur le compte." << endl;
}

void Compte::debiter(double montant) {
    if (montant <= solde) {
        solde -= montant;
        cout << montant << " € ont été débités du compte." << endl;
    } else {
        cout << "Solde insuffisant pour effectuer cette opération." << endl;
    }
}

// Nouvelle méthode pour effectuer un virement
bool Compte::virement(Compte &destinataire, double montant) {
    if (montant <= solde) {
        solde -= montant;  // Débiter le compte source
        destinataire.crediter(montant);  // Créditer le compte destinataire
        cout << montant << " € ont été transférés au compte " << destinataire.numero_compte << "." << endl;
        return true;
    } else {
        cout << "Solde insuffisant pour effectuer ce virement." << endl;
        return false;
    }
}
