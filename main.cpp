#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// ==================================================
// CONSTANTES : MODIFIER N POUR CHOISIR LA TAILLE
// ==================================================

const string NOM_FICHIER = "mots.txt";
const int N = 1000000;                  // Modifier cette valeur
const int NB_INSERTIONS = 1000;      // Nombre d'insertions/suppressions
const int REPETITIONS = 10;         // Nombre de recherches et modifications

// ==================================================
// CHARGEMENT DES DONNEES
// ==================================================

bool chargerVector(vector<string>& v, int nombreMax)
{
    ifstream fichier(NOM_FICHIER);

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir " << NOM_FICHIER << endl;
        return false;
    }

    string mot;
    int compteur = 0;

    v.clear();

    while (compteur < nombreMax && fichier >> mot)
    {
        v.push_back(mot);
        compteur++;
    }

    fichier.close();
    return true;
}

bool chargerList(list<string>& l, int nombreMax)
{
    ifstream fichier(NOM_FICHIER);

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir " << NOM_FICHIER << endl;
        return false;
    }

    string mot;
    int compteur = 0;

    l.clear();

    while (compteur < nombreMax && fichier >> mot)
    {
        l.push_back(mot);
        compteur++;
    }

    fichier.close();
    return true;
}

// ==================================================
// AFFICHAGE DES RESULTATS
// ==================================================

void afficherResultats(string operation, double tempsVector, double tempsList)
{
    cout << "\nOperation : " << operation << endl;
    cout << "Vector : " << tempsVector << " microsecondes" << endl;
    cout << "List   : " << tempsList << " microsecondes" << endl;

    if (tempsVector < tempsList)
        cout << "Plus rapide : vector" << endl;
    else if (tempsList < tempsVector)
        cout << "Plus rapide : list" << endl;
    else
        cout << "Temps identiques" << endl;
}

// ==================================================
// 1. INSERTION AU DEBUT
// ==================================================

void testerInsertionDebut(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = min(NB_INSERTIONS, max(1, 1000000 / max(n, 1)));

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.insert(v.begin(), "nouveau");

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
        l.push_front("nouveau");

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Insertion au debut", tempsV, tempsL);
}

// ==================================================
// 2. INSERTION A LA FIN
// ==================================================

void testerInsertionFin(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = NB_INSERTIONS;

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.push_back("nouveau");

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
        l.push_back("nouveau");

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Insertion a la fin", tempsV, tempsL);
}

// ==================================================
// 3. INSERTION AU MILIEU
// ==================================================

void testerInsertionMilieu(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = min(NB_INSERTIONS, max(1, 1000000 / max(n, 1)));

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.insert(v.begin() + v.size() / 2, "nouveau");

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
    {
        auto it = l.begin();
        advance(it, l.size() / 2);
        l.insert(it, "nouveau");
    }

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Insertion au milieu", tempsV, tempsL);
}

// ==================================================
// 4. SUPPRESSION AU DEBUT
// ==================================================

void testerSuppressionDebut(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = min(NB_INSERTIONS, n);

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.erase(v.begin());

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
        l.pop_front();

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Suppression au debut", tempsV, tempsL);
}

// ==================================================
// 5. SUPPRESSION A LA FIN
// ==================================================

void testerSuppressionFin(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = min(NB_INSERTIONS, n);

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.pop_back();

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
        l.pop_back();

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Suppression a la fin", tempsV, tempsL);
}

// ==================================================
// 6. SUPPRESSION AU MILIEU
// ==================================================

void testerSuppressionMilieu(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    int nb = min(NB_INSERTIONS, n);

    auto debutV = steady_clock::now();

    for (int i = 0; i < nb; i++)
        v.erase(v.begin() + v.size() / 2);

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < nb; i++)
    {
        auto it = l.begin();
        advance(it, l.size() / 2);
        l.erase(it);
    }

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Suppression au milieu", tempsV, tempsL);
}

// ==================================================
// 7. RECHERCHE
// ==================================================

void testerRecherche(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    if (v.empty() || l.empty())
    {
        cout << "\nRecherche impossible : fichier vide." << endl;
        return;
    }

    // Recherche d'un mot present vers la fin des conteneurs.
    string motRecherche = v.back();

    auto debutV = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
    {
        auto it = find(v.begin(), v.end(), motRecherche);
        if (it == v.end())
            cout << "";
    }

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
    {
        auto it = find(l.begin(), l.end(), motRecherche);
        if (it == l.end())
            cout << "";
    }

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Recherche", tempsV, tempsL);
}

// ==================================================
// 8. MODIFICATION
// ==================================================

void testerModification(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    if (v.empty() || l.empty())
    {
        cout << "\nModification impossible : fichier vide." << endl;
        return;
    }

    auto debutV = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
        v[v.size() / 2] = "modifie";

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
    {
        auto it = l.begin();
        advance(it, l.size() / 2);
        *it = "modifie";
    }

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Modification au milieu", tempsV, tempsL);
}

// ==================================================
// 9. PARCOURS
// ==================================================

void testerParcours(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    size_t totalV = 0;
    size_t totalL = 0;

    auto debutV = steady_clock::now();

    for (const string& mot : v)
        totalV += mot.size();

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (const string& mot : l)
        totalL += mot.size();

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Parcours complet", tempsV, tempsL);

    // Afficher les sommes pour utiliser les resultats du parcours.
    cout << "Verification : " << totalV << " / " << totalL << endl;
}

// ==================================================
// 10. ACCES A UNE POSITION
// ==================================================

void testerAccesPosition(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    if (v.empty() || l.empty())
    {
        cout << "\nAcces impossible : fichier vide." << endl;
        return;
    }

    size_t totalV = 0;
    size_t totalL = 0;

    auto debutV = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
    {
        string mot = v[v.size() / 2];
        totalV += mot.size();
    }

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    for (int i = 0; i < REPETITIONS; i++)
    {
        auto it = l.begin();
        advance(it, l.size() / 2);
        totalL += it->size();
    }

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Acces a une position au milieu", tempsV, tempsL);
    cout << "Verification : " << totalV << " / " << totalL << endl;
}

// ==================================================
// 11. TRI
// ==================================================

void testerTri(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    auto debutV = steady_clock::now();

    sort(v.begin(), v.end());

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    l.sort();

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Tri alphabetique", tempsV, tempsL);
}

// ==================================================
// 12. INVERSION
// ==================================================

void testerInversion(int n)
{
    vector<string> v;
    list<string> l;

    if (!chargerVector(v, n) || !chargerList(l, n))
        return;

    auto debutV = steady_clock::now();

    reverse(v.begin(), v.end());

    auto finV = steady_clock::now();

    auto debutL = steady_clock::now();

    l.reverse();

    auto finL = steady_clock::now();

    double tempsV = duration<double, micro>(finV - debutV).count();
    double tempsL = duration<double, micro>(finL - debutL).count();

    afficherResultats("Inversion de l'ordre", tempsV, tempsL);
}

// ==================================================
// PROGRAMME PRINCIPAL
// ==================================================

int main()
{
    cout << "========================================" << endl;
    cout << " COMPARAISON VECTOR ET LIST" << endl;
    cout << "========================================" << endl;

    cout << "Nombre de mots demande : " << N << endl;

    vector<string> verification;

    if (!chargerVector(verification, N))
        return 1;

    cout << "Nombre de mots charges : "
         << verification.size() << endl;

    if (verification.empty())
    {
        cout << "Erreur : le fichier ne contient aucun mot." << endl;
        return 1;
    }

    testerInsertionDebut(N);
    testerInsertionFin(N);
    testerInsertionMilieu(N);

    testerSuppressionDebut(N);
    testerSuppressionFin(N);
    testerSuppressionMilieu(N);

    testerRecherche(N);
    testerModification(N);
    testerParcours(N);
    testerAccesPosition(N);

    testerTri(N);
    testerInversion(N);

    cout << "\n========================================" << endl;
    cout << " Tous les tests sont termines." << endl;
    cout << "========================================" << endl;

    return 0;
}

