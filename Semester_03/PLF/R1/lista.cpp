#include "lista.h"
#include <iostream>

using namespace std;


PNod creare_rec(){
  TElem x;
  cout<<"x=";
  cin>>x;
  if (x==0)
    return NULL;
  else{
    PNod p=new Nod();
    p->e=x;
    p->urm=creare_rec();
    return p;
  }
}

Lista creare(){
   Lista l;
   l._prim=creare_rec();
}

void tipar_rec(PNod p){
   if (p!=NULL){
     cout<<p->e<<" ";
     tipar_rec(p->urm);
   }
}

void tipar(Lista l){
   tipar_rec(l._prim);
}

void distrug_rec(PNod p){
   if (p!=NULL){
     distrug_rec(p->urm);
     delete p;
   }
}

bool hasEvenNumberOfElements_rec(Lista& l){
    if (l._prim == NULL) {
        return true;
    }
   else{
       l._prim = l._prim->urm;
       if (l._prim == NULL) {
           return false;
       }
       else {
           l._prim = l._prim->urm;
           return hasEvenNumberOfElements_rec(l);
       }
   }
}

void deleteAllOccurencesOfElement_rec(Lista& l, TElem x){
    if (l._prim == NULL) {
        return;
    }
    else {
        if (l._prim->e == x) {
            PNod p = l._prim;
            l._prim = l._prim->urm;
            delete p;
            deleteAllOccurencesOfElement_rec(l, x);
        }
        else {
            PNod p = l._prim;
            while (p->urm != NULL && p->urm->e != x) {
                p = p->urm;
            }
            if (p->urm != NULL) {
                PNod q = p->urm;
                p->urm = q->urm;
                delete q;
                deleteAllOccurencesOfElement_rec(l, x);
            }
        }
    }
}

void distrug(Lista l) {
	//se elibereaza memoria alocata nodurilor listei
    distrug_rec(l._prim);
}

