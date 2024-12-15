#include <iostream>
#include <vector>
#include <cstdlib> // Pour rand()
#include <chrono> //calculer le temp d'execution et d'insertion 

using namespace std;
using namespace chrono;

// Fonction pour rétablir la propriété du min-heap après insertion (sift-up)
void echange(vector<int>& heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) 
        {
            int intermidiare;
            intermidiare = heap[index];
            heap[index] = heap[parent];
            heap[parent] = intermidiare;
            index = parent; 
        }
        else {
            break;
        }
    }
}



// Fonction pour rétablir la propriété du min-heap après suppression (sift-down)
void reorganise(vector<int>& heap, int index) 
{
    int size = heap.size();

    while (true) 
    {
        int filsgauche = 2 * index + 1;
        int filsdroit = 2 * index + 2;
        int plusPetit = index;

        // Trouver le plus petit élément entre le nœud courant et ses enfants
        if (filsgauche < size && heap[filsgauche] < heap[plusPetit]) {
            plusPetit = filsgauche;
        }
        if (filsdroit < size && heap[filsdroit] < heap[plusPetit]) {
            plusPetit = filsdroit;
        }

        if (plusPetit != index) 
        {
            int intermidiare;
            intermidiare = heap[index];
            heap[index] = heap[plusPetit];
            heap[plusPetit] = intermidiare;
            index = plusPetit;
        }
        else {
            break;
        }
    }
}



// Fonction pour supprimer une valeur spécifique
bool supprimerValeur(vector<int>& heap, int valeur) 
{
    //chercher l'element 'valeur'
    auto it = find(heap.begin(), heap.end(), valeur); 
    if (it == heap.end()) 
    {
        //l'element à supprimer n'existe pas 
        return false; 
    }
    //si l'element existe 
    int index = distance(heap.begin(), it); // Obtenir l'index de l'element
    heap[index] = heap.back(); // Remplacer par le dernier élément
    heap.pop_back(); // Supprimer le dernier élément

    if (index < heap.size()) 
    {
        // Rétablir la propriété du min-heap
        echange(heap, index); // Cas où l'élément est plus petit
        reorganise(heap, index); // Cas où l'élément est plus grand
    }

    return true;
}

int main() 
{


    auto debutexecution= high_resolution_clock::now();

    vector<int> vectorBase;
    vector<int> vectorHeap;

    // Exemple donné dans votre code
    // je fais ce petit exemple pour tester est ce que le programme fonctionne correctement
    /*
    vectorBase.push_back(10);
    vectorBase.push_back(7);
    vectorBase.push_back(11);
    vectorBase.push_back(1);
    vectorBase.push_back(5);
    vectorBase.push_back(5);
    vectorBase.push_back(4);
    vectorBase.push_back(16);
    vectorBase.push_back(6);
    */


    auto debut_insert_reorganise = high_resolution_clock::now();

    for (int i = 0; i < 100000; i++)
    {
        vectorBase.push_back(rand() % 100);
    }


    // Construire le min-heap
    for (auto& valeur : vectorBase) 
    {
        vectorHeap.push_back(valeur); // Ajouter l'élément à la fin
        echange(vectorHeap, vectorHeap.size() - 1); // Réparer la propriété du min-heap
    }


    auto fin_insert_reorganise = high_resolution_clock::now();


    // Afficher le min-heap
    cout << "VectorHeap avant suppression : ";
    for (const auto& val : vectorHeap) {
        cout << val << " ";
    }
    cout << endl;


    auto debutSuppression = high_resolution_clock::now();

    // Supprimer la valeur 5
    int valeurASupprimer = 5;
    if (supprimerValeur(vectorHeap, valeurASupprimer)) 
    {
        cout << "Valeur " << valeurASupprimer << " supprimee avec succes." << endl;
    }
    else 
    {
        cout << "Valeur " << valeurASupprimer << " non trouvee." << endl;
    }

    auto finSuppression = high_resolution_clock::now();

    // Afficher le min-heap après suppression
    cout << "VectorHeap apres suppression : ";
    for (const auto& val : vectorHeap) {
        cout << val << " ";
    }
    cout << endl;


    auto finexecution = high_resolution_clock::now();
    auto tempexec = duration_cast<milliseconds>(finexecution - debutexecution).count();
    auto temp_insert_reorganise = duration_cast<milliseconds>(fin_insert_reorganise - debut_insert_reorganise).count();
    auto tempsSuppression = duration_cast<microseconds>(finSuppression - debutSuppression).count();
    
    // Afficher les temps mesurés
    cout << "Temps total d'execution : " << tempexec << " millisecondes" << endl;
    cout << "Temps d'insertion et de reorganisation : " << temp_insert_reorganise << " millisecondes" << endl;
    cout << "Temps pour supprimer une valeur : " << tempsSuppression << " microsecondes" << endl;

    return 0;
}
