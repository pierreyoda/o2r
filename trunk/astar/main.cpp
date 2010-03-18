/*
Copyright (C) 2006 BEYLER SCHWARTZ Pierre

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include <map>
#include <list>
#include <utility>
#include "noeud.h"

using namespace std;

Uint32 BLANC, NOIR, BLEU, ROUGE;
SDL_Surface *s;


typedef map< pair<int,int>, noeud> l_noeud;

l_noeud liste_ouverte;
l_noeud liste_fermee;
list<point> chemin;

struct point arrivee;
noeud depart;

float distance(int, int, int, int);
void ajouter_cases_adjacentes(pair<int,int>&);
bool deja_present_dans_liste( pair<int,int>,
                              l_noeud&);
pair<int,int> meilleur_noeud(l_noeud&);
void ajouter_liste_fermee(pair<int,int>&);
void ecrire_bmp();
void colorerPixel(int, int, Uint32);
void retrouver_chemin();


int main(int argc, char **argv){
	s = SDL_LoadBMP("big.bmp");
	if(!s){
        cerr << "erreur lors du chargement du bmp de départ" << endl;
        return 1;
	}
    NOIR  = SDL_MapRGB(s->format, 0        , 0        , 0);
    BLEU  = SDL_MapRGB(s->format, 0        , 0        , (char)255);
    BLANC = SDL_MapRGB(s->format, (char)255, (char)255, (char)255);
    ROUGE = SDL_MapRGB(s->format, (char)255, 0        , 0);

    arrivee.x = s->w-1;
    arrivee.y = s->h-1;

    depart.parent.first  = 0;
    depart.parent.second = 0;

    pair <int,int> courant;

    /* déroulement de l'algo A* */

    courant.first  = 0;
    courant.second = 0;
    // ajout de courant dans la liste ouverte

    liste_ouverte[courant]=depart;
    ajouter_liste_fermee(courant);
    ajouter_cases_adjacentes(courant);


    while( !((courant.first == arrivee.x) && (courant.second == arrivee.y))
            &&
           (!liste_ouverte.empty())
         ){

        // on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
        courant = meilleur_noeud(liste_ouverte);

        // on le passe dans la liste fermee, il ne peut pas déjà y être
        ajouter_liste_fermee(courant);

        ajouter_cases_adjacentes(courant);
    }

    if ((courant.first == arrivee.x) && (courant.second == arrivee.y)){
        retrouver_chemin();

        ecrire_bmp();
    }else{
            /* pas de solution */
    }

	return 0;
}


float distance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    //return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}


/*
ajoute toutes les cases adjacentes à n dans la liste ouverte
*/
void ajouter_cases_adjacentes(pair <int,int>& n){
    noeud tmp;

    // on met tous les noeud adjacents dans la liste ouverte (+vérif)
    for (int i=n.first-1; i<=n.first+1; i++){
        if ((i<0) || (i>=s->w))
            continue;
        for (int j=n.second-1; j<=n.second+1; j++){
            if ((j<0) || (j>=s->h))
                continue;
            if ((i==n.first) && (j==n.second))  // case actuelle n
                continue;

            if (*((Uint8 *)s->pixels + j * s->pitch + i * s->format->BytesPerPixel) == NOIR)
                // obstace, terrain non franchissable
                continue;

            pair<int,int> it(i,j);

            if (!deja_present_dans_liste(it, liste_fermee)){
                /* le noeud n'est pas déjà présent dans la liste fermée */

                tmp.cout_g = liste_fermee[n].cout_g + distance(i,j,n.first,n.second);
                tmp.cout_h = distance(i,j,arrivee.x,arrivee.y);
                tmp.cout_f = tmp.cout_g + tmp.cout_h;
                tmp.parent = n;

                if (deja_present_dans_liste(it, liste_ouverte)){
                    /* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
                    if (tmp.cout_f < liste_ouverte[it].cout_f){
                        /* si le nouveau chemin est meilleur, on update */
                        liste_ouverte[it]=tmp;
                    }

                    /* le noeud courant a un moins bon chemin, on ne change rien */


                }else{
                    /* le noeud n'est pas présent dans la liste ouverte, on l'ajoute */
                    liste_ouverte[pair<int,int>(i,j)]=tmp;
                }
            }
        }
    }
}

bool deja_present_dans_liste(pair<int,int> n, l_noeud& l){
    l_noeud::iterator i = l.find(n);
    if (i==l.end())
        return false;
    else
        return true;
}

/*
    fonction qui renvoie la clé du meilleur noeud de la liste
*/
pair<int,int> meilleur_noeud(l_noeud& l){
    float m_coutf = l.begin()->second.cout_f;
    pair<int,int> m_noeud = l.begin()->first;

    for (l_noeud::iterator i = l.begin(); i!=l.end(); i++)
        if (i->second.cout_f< m_coutf){
            m_coutf = i->second.cout_f;
            m_noeud = i->first;
        }

    return m_noeud;
}

/*
    fonction qui passe l'élément p de la liste ouverte dans la fermée
*/
void ajouter_liste_fermee(pair<int,int>& p){
    noeud& n = liste_ouverte[p];
    liste_fermee[p]=n;

    // il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
    if (liste_ouverte.erase(p)==0)
        cerr << "n'apparait pas dans la liste ouverte, impossible à supprimer" << endl;
    return;
}

/*
    fonction qui met
        en bleu toutes les cases du chemin final
*/
void ecrire_bmp(){
    list<point>::iterator j;

    for (j=chemin.begin(); j!=chemin.end(); j++)
        colorerPixel(j->x,j->y,BLEU);

    cout << "chemin final de longueur " << chemin.size() << endl;
    cout << "dernière liste ouverte : " << liste_ouverte.size() << " éléments" << endl;
    cout << "dernière liste fermee : " << liste_fermee.size() << " éléments" << endl;

    SDL_SaveBMP(s, "resultat.bmp");
}

void colorerPixel(int x, int y, Uint32 pixel){
    /* p est l'adresse du pixel que l'on veut modifier */
    Uint8 *p = (Uint8*)s->pixels + y * s->pitch + x * s->format->BytesPerPixel;

    if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
    }else{
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
    }
}


void retrouver_chemin(){
    // l'arrivée est le dernier élément de la liste fermée.
    noeud& tmp = liste_fermee[std::pair<int, int>(arrivee.x,arrivee.y)];

    struct point n;
    pair<int,int> prec;
    n.x = arrivee.x;
    n.y = arrivee.y;
    prec.first  = tmp.parent.first;
    prec.second = tmp.parent.second;
    chemin.push_front(n);

    while (prec != pair<int,int>(depart.parent.first,depart.parent.first)){
        n.x = prec.first;
        n.y = prec.second;
        chemin.push_front(n);

        tmp = liste_fermee[tmp.parent];
        prec.first  = tmp.parent.first;
        prec.second = tmp.parent.second;
    }
}

// end of file

