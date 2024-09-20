
#include <iostream>
using namespace std ;

class Compte {
private:
    int numero_compte;
    double solde;
    int code_secret;

public:
    Compte(int num, double solde_initial, int code);

    // Méthode pour vérifier le code secret
    bool verifier_code(int code);

    // Méthodes pour les opérations de base
    void consulter_solde();
    void crediter(double montant);
    void debiter(double montant);
    
    // Nouvelle méthode pour effectuer un virement
    bool virement(Compte &destinataire, double montant);
};

