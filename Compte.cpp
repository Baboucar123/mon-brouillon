#include "Compte.h"
#include <iostream>
#include <mysql/mysql.h>

Compte::Compte(int rib, double solde, const Client& proprietaire)
    : rib(rib), solde(solde), proprietaire(proprietaire) {}

Compte::Compte() : rib(0), solde(0.0), proprietaire(Client("","", "", "", 0)) {} // notre constructeur par defaut

void Compte::debiter(double montant) {

    if (montant <= solde) {

        solde -= montant;
        cout << montant << " EUR debiter. Nouveau solde : " << solde << " EUR." << endl;

    } 
    
    else {

        cout << "Solde insuffisant pour debiter." << endl;

    }
}

void Compte::crediter(double montant) {

    solde += montant;
    cout << montant << " EUR crediter. Nouveau solde : " << solde << " EUR." << endl;

}

void Compte::virement(Compte& destinataire, double montant) {

    if (montant <= solde) {

        debiter(montant);
        destinataire.crediter(montant);
        cout << "Virement de " << montant << " EUR effectue." << endl;
    }
    else {
        
        cout << "Solde insuffisant pour le virement." << endl;

    }
}

void Compte::consulterSolde() const {

    cout << "Le solde de votre compte est de : " << solde << " EUR." << endl;

}

int Compte::getRIB() const {

    return rib;

}

const Client& Compte::getProprietaire() const {

    return proprietaire;

}
