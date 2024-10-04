#ifndef COMPTE_H
#define COMPTE_H

#include "Client.h"

class Compte {

private:

int rib;
double solde;
Client proprietaire;

public:

Compte(int rib, double solde, const Client& proprietaire); 
Compte(); // notre Cconstructeur par défaut
void debiter(double montant);
void crediter(double montant);
void virement(Compte& destinataire, double montant);
void consulterSolde() const;
int getRIB() const;
const Client& getProprietaire() const;

};

#endif
