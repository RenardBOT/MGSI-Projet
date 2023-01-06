#include "dijkstra.hpp"
#include "cmath"

//Tableau d'analyse de Dijkstra
vector<dijSommet *> dijSommets; 
//Tableau qui enregistre la distance entre deux sommets et l'assigne en tant que poids aux half-edges
vector<halfedge_ponderee *> tabPond; 

void construire(vector<halfedge *> he, vector<vertex *> ve, int origine, int flag){
    //Pour chaque sommet, il faut une case dans le tableau
    for(long unsigned int i=0; i<ve.size(); i++){
        //Chaque sommet est initialisé avec un poids irréaliste afin de passer les tests de Dijkstra
        dijSommet *d = new dijSommet{ve[i]->id,0,1000000000,false};
        //Mis à part le sommet origine qui a un poids 0 puisqu'il est l'origine
        if(d->id == origine) d->poids=0;
        std::cout<<"DijSommet : "<<d->id<<" | "<<d->origin<<" | "<<d->poids<<" | "<<d->marque<<endl;
        dijSommets.push_back(d);
    }
    //Si le flag est à 0, on ne pondère pas les half-edge
    if(flag==0){
        std::cout<<"Nombre de Half-Edges : "<<he.size()<<endl;
        for(long unsigned int i=0; i<he.size(); i++){
            halfedge_ponderee *h = new halfedge_ponderee{he[i], 1};
            std::cout<<"hePondere : "<< h->half_edge->id<<" | "<<h->poids<<endl;
            tabPond.push_back(h);
        }
    //Sinon on les pondère
    }else{
        std::cout<<"Nombre de Half-Edges : "<<he.size()<<endl;
        //Pour chaque half-edge, on calcule la distance entre les deux sommets qu'il relie et lui assigne en tant que poids
        for(long unsigned int i=0; i<he.size(); i++){
            vertex* vert1 = he[i]->origin;
            vertex* vert2 = he[i]->next->origin;
            float distance = sqrt((pow(vert1->x-vert2->x,2)+pow(vert1->y-vert2->y,2)+pow(vert1->z-vert2->z,2)));
            halfedge_ponderee *h = new halfedge_ponderee{he[i], distance};
            std::cout<<"hePondere : "<< h->half_edge->id<<" | "<<h->poids<<endl;
            tabPond.push_back(h);
        }
    }
}

int selection(){
    //Le max est initialisé à une valeur irréaliste afin de trouver un sommet
    int max=1000000000;
    int idSommet=-1;
    std::cout<<"id|  origine| poids| marqué|"<<endl;
    //Pour chaque sommet non marqué on compare sa distance au maximum
    for(long unsigned int i=0; i<dijSommets.size(); i++){
        std::cout<<dijSommets[i]->id<<" |"<<dijSommets[i]->origin<<" |"<<dijSommets[i]->poids<<" |"<<dijSommets[i]->marque<<endl;
        if(dijSommets[i]->poids<max && !dijSommets[i]->marque){
            max = dijSommets[i]->poids;
            idSommet = dijSommets[i]->id;
        }
    }
    //On renvoit le sommet non marqué le plus proche de l'origine
    //La fonction renvoie -1 si tout les sommets atteignable sont marqué
    //La fonction renvoie -1 si il ne reste plus que des sommets non connexe aussi 
    std::cout<<"Sommet selectionné : "<<idSommet<<endl;
    return idSommet;
}

vector<int> buildDijkstra(vector<halfedge *> he, vector<vertex *> ve, int origine, int destination, int flag){
    std::cout<<"start"<<endl;
    //La fonction commence par construire le tableau de Dijkstra
    construire(he, ve, origine, flag);
    //L'origine est le premier sommet comparé dans l'algorithme
    int idCourant = origine;
    int idComparation;
    //Tant que la fonction de selection trouve un sommet à analyser :
    while(idCourant!=-1){
        std::cout<<"IdCourant : "<<idCourant<<endl;
        //Pour chaque half-edge
        for(long unsigned int i=0; i<he.size(); i++){
            std::cout<<idCourant<<" == "<<he[i]->origin->id<<"/"<<he[i]->next->origin->id<<" ?"<<endl;
            //Si l'origine de la half-edge est le sommet courant
            if(he[i]->origin->id == idCourant){
                //On compare la distance entre le sommet courant et le sommet pointé par la half-edge avec sa distance actuelle
                std::cout<<"Yes"<<endl;
                idComparation = he[i]->next->origin->id;
                std::cout<<"IdComparation : "<<idComparation<<endl;
                std::cout<<"Poids comparé  = "<<dijSommets[idComparation-1]->poids<<" vs Poids comparant = "<<dijSommets[idCourant-1]->poids+tabPond[i]->poids<<endl;
                //Si sa distance actuelle est plus petite que la distance déjà enregistré
                if(dijSommets[idComparation-1]->poids > dijSommets[idCourant-1]->poids+tabPond[i]->poids){
                    std::cout<<"Modification"<<endl;
                    //L'origine de ce sommet devient le sommet courant, et la distance est re-calculé
                    dijSommets[idComparation-1]->poids = dijSommets[idCourant-1]->poids+tabPond[i]->poids;
                    dijSommets[idComparation-1]->origin = dijSommets[idCourant-1]->id;
                }
            }
            //Si la destination de la half-edge est le sommet courant
            if(he[i]->next->origin->id == idCourant){
                std::cout<<"Yes"<<endl;
                //On compare la distance entre le sommet courant et le sommet qui pointe le sommet courant avec sa distance actuelle
                idComparation = he[i]->origin->id;
                std::cout<<"IdComparation : "<<idComparation<<endl;
                std::cout<<"Poids comparé  = "<<dijSommets[idComparation-1]->poids<<" vs Poids comparant = "<<dijSommets[idCourant-1]->poids+tabPond[i]->poids<<endl;
                //Si sa distance actuelle est plus petite que la distance déjà enregistré
                if(dijSommets[idComparation-1]->poids > dijSommets[idCourant-1]->poids+tabPond[i]->poids){
                    std::cout<<"Modification"<<endl;
                    //L'origine de ce sommet devient le sommet courant, et la distance est re-calculé
                    dijSommets[idComparation-1]->poids = dijSommets[idCourant-1]->poids+tabPond[i]->poids;
                    dijSommets[idComparation-1]->origin = dijSommets[idCourant-1]->id;
                }
            }
        }
        //Le sommet courant est marqué pour qu'il ne soit plus analysé
        dijSommets[idCourant-1]->marque = true;
        //On séléctionne le prochain sommet à analyser
        idCourant = selection();
    }
    std::cout<<"Sortie de boucle"<<endl;
    //en sortie de boucle, le tableau est construit et on peut tracer le chemin
    vector<int> chemin;
    //Le chemin part de la destination
    //on enregistre d'où vient le chemin qui mène jusqu'à la destination
    int sommet = destination;
    std::cout<<"Destination : "<<destination<<", origine : "<<origine<<endl;
    while(sommet>0){
        chemin.push_back(sommet);
        sommet = dijSommets[sommet-1]->origin;
    }
    std::cout<<"Chemin : ";
    for(long unsigned int i=0; i<chemin.size(); i++){
        std::cout<<chemin[i]<<"; ";
    }
    std::cout<<endl;
    return chemin;
}