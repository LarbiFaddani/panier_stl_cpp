#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> 
using namespace std;

class Article {
private:
    int ref, quantite_stock;
    double prix;

public:
    Article(int ref = 0, int quantite_stock = 0, double prix = 0) : ref(ref), quantite_stock(quantite_stock), prix(prix) {
    }

    // Methodes getter et setter pour ref, quantite_stock et prix
    int getRef() const { return ref; }
    int getQuantiteStock() const { return quantite_stock; }
    double getPrix() const { return prix; }
    void setQuantiteStock(int qte) { quantite_stock = qte; }
    void setPrix(double prix_) { prix = prix_; }

    // Surcharge des operateurs == et <
    bool operator==(const Article &A1) const { return this->ref == A1.ref; }
    bool operator<(const Article &A1) const { return this->prix < A1.prix; }

    // Surcharge de l'operateur << pour afficher un objet Article
    friend ostream& operator<<(ostream& os, const Article& article) {
        os << "Ref: " << article.ref << ", Stock: " << article.quantite_stock << ", Prix: " << article.prix;
        return os;
    }
};

class Panier {
private:
    map<Article, int> panier;
public:
    Panier() {
        cout << "Panier cre" << endl;
    }

    void ajouterArticle(Article &article, int quantite_commande) {
        if (panier.find(article) != panier.end()) {
        cout << "Oups! L'article avec la référence " << article.getRef() << " est déjà dans le panier." << endl;
        cout << "Veuillez le modifier en tapant choix 3" << endl;
        return;
        }
        while (article.getQuantiteStock() < quantite_commande) {
            cout << "Quantite insuffisante en stock pour ajouter cet article au panier." << endl;
            cout << "Entrez une nouvelle quantite: ";
            cin >> quantite_commande;
        }
        if (quantite_commande <= article.getQuantiteStock()) { // Verifie si la quantite commandee est disponible en stock
        // Appliquer la remise si la quantite commandee depasse 10 unites
        double prix_unitaire =  quantite_commande> 10 ? article.getPrix() * 0.8 : article.getPrix();

        // Calculer le montant total avec la remise
        double montant_total = prix_unitaire * quantite_commande;

        // Mettre e jour la quantite en stock de l'article !!
        article.setQuantiteStock(article.getQuantiteStock() - quantite_commande);

        // Ajouter l'article au panier avec la quantite specifiee et le montant total calcule
        panier[article] = panier[article] + quantite_commande;



        cout << "Article ajoute . Montant Total : "<< montant_total << endl;
    } else {
        cout << "L'article n'est pas disponible en quantite suffisante." << endl;
    }
    }
void modifierArticle(Article& A1, int nouvelle_quantite) {
    for (auto it = panier.begin(); it != panier.end(); it++) {
        if (it->first == A1) { // Trouver l'article dans le panier
            // Verifier si la nouvelle quantite est disponible en stock (incluant l'ancienne quantite dans le panier)
            if (nouvelle_quantite <= it->first.getQuantiteStock() + it->second) {
                // Mettre e jour la quantite en stock de l'article
                int quantite_stock_initiale = it->first.getQuantiteStock();
                int quantite_actuelle_panier = it->second;

                // Creer une nouvelle copie de l'article avec la quantite mise e jour
                Article article_mis_a_jour = it->first;
                article_mis_a_jour.setQuantiteStock(quantite_stock_initiale + quantite_actuelle_panier - nouvelle_quantite);

                // Mettre e jour le panier en inserant l'article mis e jour
                panier.erase(it); // Supprimer l'article actuel
                panier[article_mis_a_jour] = nouvelle_quantite; // Inserer l'article mis e jour

                // Calculer le montant total
                double montant_total = article_mis_a_jour.getPrix() * nouvelle_quantite;

                // Appliquer la remise si la nouvelle quantite depasse 10 unites
                if (nouvelle_quantite > 10) {
                    double montant_remise = montant_total * 0.8; // Appliquer une remise de 20%
                    cout << "Article modifie avec succes. Montant Total avec remise : " << montant_remise << endl;
                } else {
                    cout << "Article modifie avec succes. Montant Total : " << montant_total << endl;
                }
            } else {
                cout << "Quantite demandee superieure au stock disponible." << endl;
            }
            break; // Sortir de la boucle une fois que l'article a ete trouve et modifie
        }
    }
}


    // Fonction pour afficher les articles du panier tries par prix croissant
    void afficherArticlesTriesParPrix() const {
        vector<Article> articles_sorted;
        for (const auto &pair : panier) {
            articles_sorted.push_back(pair.first);
        }
        sort(articles_sorted.begin(), articles_sorted.end());
        for ( auto& article : articles_sorted) {
          cout << article << std::endl;
        }
    }


//
    Article trouverArticleLePlusCher() const {
    if (panier.empty()) {
        cout << "Le panier est vide." << endl;
    } else {
        auto it = max_element(panier.begin(), panier.end());//deja declare l'operator <
        return it->first;
    }
}

    //

    void viderPanier() {
           if (panier.empty()) {
                cout << "Panier est vide !" << endl;
            } else {
                int choix;

                cout << "Souhaitez-vous vider le panier ?" << endl;
                cout << "1 : Oui" << endl;
                cout << "2 : Non" << endl;
                cout <<"Entrez votre choix :" ;
                cin >> choix;

                if (choix == 1) {
                    panier.clear();
                    cout << "Le panier a ete vider avec succes." << endl;
                } else {
                    cout << "Le panier n'a pas ete vide." << endl;
                }
            }
      }
      ///
    void afficherPanier() const{
        if (panier.empty()) {
            cout << "Le panier est vide." << endl;
        } else {
             cout<< "----------------------------Panier--------------------------"<<endl;
            for (auto it = panier.begin(); it != panier.end(); it++) {
                cout << "Article : " << it->first << ", Quantite : " << it->second << endl;
            }
        }
    }
    void afficherArticlesEntre(double min_prix, double max_prix) const {
        for (const auto &pair : panier) {
            if (pair.first.getPrix() >= min_prix && pair.first.getPrix() <= max_prix) {
                cout <<"Al: "<< pair.first << ", Quantite : " << pair.second << endl;
            }
        }
    }

    ///
 double calculerMontantTotalAvecRemise() const {
    double montant_total = 0.0;
    for (const auto &item : panier) {
        double prix_unitaire;
        if (item.second > 10) {
            prix_unitaire = item.first.getPrix() * 0.8;
        } else {
            prix_unitaire = item.first.getPrix();
        }
        montant_total = montant_total + prix_unitaire * item.second;
    }
    return montant_total;
}
};

/////
class Client {
    private:
        string email, nom;
    public:
        Client(string email="",string nom=""):email(email), nom(nom){}

        friend ostream& operator<<(ostream& out,const Client& cl){
            out << "Nom client: " << cl.nom << " ,Email: " << cl.email << endl;
            return out;
        }

};

class Commande {
private:
    int num_Cmd;
    Client clt;
    Panier panier;
    string etat;

public:
    Commande(int num_Cmd=0, const Client& client=Client(), const Panier& panier=Panier(), const string& etat="En attente de traitement"): num_Cmd(num_Cmd), clt(client), panier(panier), etat(etat) {}
    void mettreAJourPanier(const Panier& panier) {
        this->panier = panier;
    }
    void afficherDetails() const {
        cout << "---------Numero de commande : " << num_Cmd <<"----------"<< endl;
        cout << "Etat de la commande : " << etat << endl;
        cout << "Informations sur le client : " << clt ;
        cout << "Contenu du panier :" << endl;
        panier.afficherPanier();
        cout << "-------------------------" << endl;
    }

};

int main() {
    Article A1(1, 10, 100.99);
    Article A2(2, 20, 200.99);
    Article A3(3, 30, 300.99);
    Panier panierA;



    Client Cl("faddanilarbi@hotmail.com", "faddani");
    Commande commande(1, Cl, panierA);

    int choix;
    do {
        cout << "Menu:"<<endl;
        cout << "1. Ajouter article au panier"<<endl;
        cout << "2. Modifier article dans le panier"<<endl;
        cout << "3. Afficher le panier"<<endl;
        cout << "4. Vider le panier"<<endl;
        cout << "5. Afficher articles entre deux prix"<<endl;
        cout << "6. Afficher article le plus cher"<<endl;
        cout << "7. Afficher articles tries par prix"<<endl;
        cout << "8. Afficher details de la commande"<<endl;
        cout << "9. Afficher montant total de la commande"<<endl;
        cout << "10. Quitter"<<endl;
        cout << "Choisissez une option: ";
        cin >> choix;

        switch (choix) {
            case 1: {
                int ref, qte_commande;
                cout<<"1 : "<<A1<<endl;
                cout<<"2 : "<<A2<<endl;
                cout<<"3 : "<<A3<<endl;
                cout << "Entrez reference: ";
                cin >> ref ;
                cout << "Entrez la quantite commandee: ";
                cin >> qte_commande;
                if (ref == A1.getRef()) {
                    panierA.ajouterArticle(A1, qte_commande);
                } else if (ref == A2.getRef()) {
                    panierA.ajouterArticle(A2, qte_commande);
                } else if (ref == A3.getRef()) {
                    panierA.ajouterArticle(A3, qte_commande);
                } else {
                    cout << "Reference d'article invalide." << endl;
                }
                break;
            }
            case 2: {
                int ref, nouvelle_quantite;
                cout << "Entrez reference: ";
                cin >> ref ;
                cout << "Entrez la nouvelle quantite: ";
                cin >> nouvelle_quantite;
                Article article(ref);
                panierA.modifierArticle(article, nouvelle_quantite);
                break;
            }
            case 3:
                panierA.afficherPanier();
                break;
            case 4:
                panierA.viderPanier();
                break;
            case 5: {
                double min_prix, max_prix;
                cout << "Entrez le prix minimum "<<endl;
                cin >> min_prix;
                cout << "Entrez le prix maximum "<<endl;
                cin >> max_prix;
                panierA.afficherArticlesEntre(min_prix, max_prix);
                break;
            }
            case 6: {
                Article articlePlusCher = panierA.trouverArticleLePlusCher();
                cout << "l'Article le plus cher : " << articlePlusCher << endl;
                break;
            }
            case 7:
                panierA.afficherArticlesTriesParPrix();
                break;
            case 8:
                commande.mettreAJourPanier(panierA);
                commande.afficherDetails();
                break;
            case 9:
                cout << "Montant total de commande: " << panierA.calculerMontantTotalAvecRemise() << endl;
                break;
            case 10:
                cout << "Au revoir!" << endl;
                break;
            default:
                cout << "Option invalide. Veuillez reessayer." << endl;
        }
    } while (choix != 10);

    return 0;
}
