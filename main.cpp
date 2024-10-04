#include <iostream>
#include "Client.h"
#include "Compte.h"
#include <mysql/mysql.h>

using namespace std;

// etape 1 nous allons nous connecter à la base de donnée 
// connexion à la base de donnée 

MYSQL* connectDB() {

MYSQL *conn = mysql_init(NULL);
if (conn == NULL) {
        cerr << "mysql_init() a echoue." << endl;
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "ciel2024", "Ciel@2024", "banque", 0, NULL, 0) == NULL) {
        cerr << "mysql_real_connect() a echoue." << endl;
        cerr << "Erreur : " << mysql_error(conn) << endl;
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    cout << "Connexion a la base de donnees reussie !" << endl;
    return conn;

}


// charger les comptes dans la base de donnée 

void chargerComptesDepuisBDD(MYSQL* conn, Compte comptes[], int& nombreComptes) {

    MYSQL_RES *res;
    MYSQL_ROW row;
    string query = "SELECT Compte.rib, Compte.solde, Client.cin, Client.nom, Client.prenom, Client.telephone, Client.code_secret FROM Compte JOIN Client ON Compte.client_cin = Client.cin";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Echec de la requete : " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);

    if (res == NULL) {

        cerr << "Erreur de recuperation des resultats : " << mysql_error(conn) << endl;
        return;

    }

    nombreComptes = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {

        // créer un client et un compte dans la base de donnée 

        Client client(row[2], row[3], row[4], row[5], stoi(row[6]));
        Compte compte(stoi(row[0]), stod(row[1]), client);
        comptes[nombreComptes++] = compte;

    }

    mysql_free_result(res);
}

// fonctions pour afficher le menu 

void afficherMenu(Compte& compte, Compte comptes[], int nombreComptes) { 

    int choix;
    double montant;

    do {
        cout << "\nChoisissez une operation : " << endl;
        cout << "1. Debiter" << endl;
        cout << "2. Crediter" << endl;
        cout << "3. Virement" << endl;
        cout << "4. Consulter le solde" << endl;
        cout << "5. Se deconnecter" << endl;
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Montant a debiter : ";
                cin >> montant;
                compte.debiter(montant);
                break;
            case 2:
                cout << "Montant a crediter : ";
                cin >> montant;
                compte.crediter(montant);
                break;
            case 3: {
                cout << "RIB du beneficiaire : ";
                int ribDestinataire;
                cin >> ribDestinataire;

                Compte* destinataire = nullptr;

                // Utilisez le numéro de compte 

                for (int j = 0; j < nombreComptes; ++j) {

                    if (comptes[j].getRIB() == ribDestinataire) {

                        destinataire = &comptes[j];
                        break;

                    }

                }

                if (destinataire != nullptr) {

                    cout << "Montant a transferer : ";
                    cin >> montant;
                    compte.virement(*destinataire, montant);

                } 
                else {

                    cout << "Beneficiaire introuvable." << endl;

                }

                break;
            }
            case 4:
                compte.consulterSolde();
                break;
            case 5:
                cout << "Deconnexion." << endl;
                break;
            default:
                cout << "Choix invalide." << endl;

        }

    } while (choix != 5);
}


int main() {
    // connexion à la base de donnée 

    MYSQL *conn = connectDB();

    // chargement des comptes dans la base de donnée 
    // le nombre de compte maximum est de 10 
    Compte comptes[10];  
    int nombreComptes;
    chargerComptesDepuisBDD(conn, comptes, nombreComptes);

    cout << "Bienvenue dans notre distributeur LCL !" << endl;

    bool fin = false;
    while (!fin) {
        int essaisRestants = 3;
        bool codeValide = false;

        // boucle while pour le nombres d'essaies qui est de 3 

        while (essaisRestants > 0) {

            cout << "\nVeuillez insérer votre carte bancaire et entrer votre code secret (4 chiffres) : " << endl;
            int codeSecret;
            cin >> codeSecret;

            // verifie le code pour chaque compte 

            for (int i = 0; i < nombreComptes; ++i) {
                if (comptes[i].getProprietaire().verifierCodeSecret(codeSecret)) { //verification du code s'il existe 
                    cout << "Bienvenue " << comptes[i].getProprietaire().getNom() << " "
                         << comptes[i].getProprietaire().getPrenom() << " !" << endl;

                    // Affichez le solde après la connexion

                    comptes[i].consulterSolde();

                    // Affichez le menu des opérations
                    afficherMenu(comptes[i], comptes, nombreComptes); 
                    codeValide = true;
                    break;
                }
            }
            if (codeValide) {

                break; // Sortie de la boucle de vérification du code

            } 
            else {

                essaisRestants--;
                cout << "Code incorrect. Il vous reste " << essaisRestants << " essai(s)." << endl;

            }
        }

        if (!codeValide) {

            cout << "Votre carte a été retenue pour des raisons de sécurité. Veuillez contacter votre banque." << endl;
            break;

        }

        // demander au client s'il veut quitter 

        cout << "\nSouhaitez-vous quitter ? (o/n) : ";
        char quitter;
        cin >> quitter;
        if (quitter == 'o' || quitter == 'O') {
            fin = true;
            cout << "Veuillez retirer votre carte bancaire." << endl;
        }
    }

    cout << "Merci de votre visite. À la prochaine !" << endl;

    //on quitte la base de  la base de donnée 
    mysql_close(conn);

    return 0;
}
