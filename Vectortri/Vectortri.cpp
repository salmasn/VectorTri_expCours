#include <iostream>
#include <vector>
#include <cstdlib> // Pour rand()
#include <algorithm> // Pour swap()

using namespace std;

// Fonction pour rétablir la propriété du min-heap après insertion (sift-up)
void echange(vector<int>& heap, int index) {
    while (index > 0) 
    {
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

int main() 
{
    vector<int> vectorBase;
    vector<int> vectorHeap;
        
    //exemple qu'on a fait dans la sceance
    
    vectorBase.push_back(10);
    vectorBase.push_back(7); 
    vectorBase.push_back(11); 
    vectorBase.push_back(1); 
    vectorBase.push_back(5); 
    vectorBase.push_back(4); 
    vectorBase.push_back(16);
    vectorBase.push_back(6);
    
    /*
    for (int i = 0; i < 20; i++)
    {
        vectorBase.push_back(rand()%20);
    }
    */
    


    // Afficher les éléments de vectorBase
    cout << "VectorBase : ";
    for (auto& valeur : vectorBase) {
        cout << valeur << " ";
    }
    cout << endl;



    // Insérer les éléments dans vectorHeap en maintenant un min-heap
    for (auto& valeur : vectorBase) {
        vectorHeap.push_back(valeur); // Ajouter l'élément à la fin
        echange(vectorHeap, vectorHeap.size() - 1); // Réparer la propriété du min-heap
    }



    // Afficher les éléments de vectorHeap
    cout << "VectorHeap : ";
    for (auto& valeur : vectorHeap) {
        cout << valeur << " ";
    }
    cout << endl;

    return 0;
}
