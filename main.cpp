#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
ifstream f("mergeheap.in");
ofstream g("mergeheap.out");
struct nod{
    int numar,nrCopii;
    nod* dreapta;
    nod* stanga;
    nod* parinte;
    nod* copil;
    bool mark;
    bool marcaj_cautare;
};
class Fibonacci_Heap{
    nod* minim;
    int nr_arbori;

public:
    Fibonacci_Heap() {
        minim=nullptr;
        nr_arbori=0;
    }
    Fibonacci_Heap(nod *f,int na) : minim(f),nr_arbori(na) {}
    static nod* creare_nod_nou(int valoare){
        nod* n=new nod;
        n->numar=valoare;
        n->mark= false;
        n->nrCopii=0;
        n->parinte=nullptr;
        n->copil=nullptr;
        n->dreapta=n;
        n->stanga=n;
        n->marcaj_cautare= false;
        return n;
    }
    void insert(nod* nou){

        if(minim==nullptr)
        {
            minim=nou;
        }
        else{

            (minim->stanga)->dreapta=nou;
            nou->stanga=minim->stanga;
            nou->dreapta=minim;
            minim->stanga=nou;
            if(minim->numar>nou->numar)
                minim=nou;
        }
        nr_arbori+=1;
    }
    nod* reuniune( nod* h1,nod* h2){
        nod* h;
        h=Initializare();
        if(h1->numar>h2->numar)
        {
            if(h2->numar<minim->numar)
                minim=h2;
        }
        else {
            if(h1->numar<minim->numar)
                minim=h1;
        }
        h=h1;
        (h->dreapta)->stanga=h2->stanga;
        (h2->stanga)->dreapta=h->dreapta;
        h->dreapta=h2;
        h2->stanga=h;
        return h;

    }
    static nod* Initializare(){
        nod* n;
        n=nullptr;
        return n;
    }
    void extragere_minim(){
        if(minim==nullptr)
            cout<<"Heapul este gol !";
        nod* copil=minim->copil;
        if(copil!= nullptr)
        {
            nod* x=copil;
            do{
                nod* urmatorul=copil->dreapta;
                insert(copil);
                copil=urmatorul;
            }while(copil!=x and copil->dreapta!=minim);
        }
        (minim->stanga)->dreapta=minim->dreapta;
        (minim->dreapta)->stanga=minim->stanga;

        if(minim==minim->dreapta)
        {
            minim=nullptr;
            nr_arbori=0;
        }
        else{
            nr_arbori--;
            minim=minim->dreapta;
            concatenare(minim);
        }
    }
    void concatenare(nod* minim){
        int grad_max=int((log(nr_arbori))/(log(2)))+1;
        nod* A[grad_max];
        nod* x=minim;
        for(int i=0;i<=grad_max;i++)
            A[i]=nullptr;
        nod *y;
        do
        {
            int nr=x->nrCopii;
            while(A[nr]!=nullptr)
            {
               y=A[nr];
                if(x->numar>y->numar)
                {
                    nod* swp=x;
                    x=y;
                    y=swp;
                }
                atasare(A[nr],y);
                A[nr]= nullptr;
                nr++;

            }
            A[nr]=x;
            x=x->dreapta;

        }while(x!=minim);
        minim= nullptr;

        for(int i=0;i<grad_max;i++)
        {
            if(A[i]!=nullptr)
            {
                if(minim== nullptr) {
                    minim=A[i];
                    minim->stanga=minim;
                    minim->dreapta=minim;
                }
                else {
                    insert(A[i]);
                }
            }

        }

    }
    void atasare(nod* x,nod* y){

        (y->stanga)->dreapta=y->dreapta;
        (y->dreapta)->stanga=y->stanga;
        if(x->copil== nullptr)
        {
            x->copil=y;
            y->dreapta=y;
            y->stanga=y;
            x->nrCopii=1;
            y->parinte=x;
        }
        else if((x->copil)->dreapta==nullptr)
        {
            y->stanga=x->copil;
            y->dreapta=x->copil;
            (x->copil)->stanga=y;
            (x->copil)->dreapta=y;
            y->parinte=x;
            x->nrCopii+=1;
        }
        else{
            nod* c=x->copil;
            (c->dreapta)->stanga=y;
            y->dreapta=c->dreapta;
            c->dreapta=y;
            y->stanga=c;
            y->parinte=x;
            x->numar+=1;
        }
        nr_arbori--;

    }
    int  decrease_nod(nod* minim,int x,int y){
        if(minim==nullptr)
            return 0;
        nod* nodg=cautare_nod(minim,x);
        if(nodg==nullptr)
            return 1;
        if(x<y)
            return 0;
        nodg->numar=y;
        nod* p=nodg->parinte;
        if(p!=nullptr and nodg->numar<p->numar)
        {
            cut(minim,nodg,p);
            cascade_cut(minim,p);
        }
        if(nodg->numar<minim->numar)
            minim=nodg;
        return 0;
    }
    void cut(nod* minim,nod* x,nod* y){
        if(x==x->stanga)
        {
            y->copil=nullptr;
            y->nrCopii-=1;
        }
        else{
            y->copil=x->dreapta;
            (x->dreapta)->stanga=x->stanga;
            (x->stanga)->dreapta=x->dreapta;
            y->nrCopii-=1;
        }
        x->dreapta=x;
        x->stanga=x;
        x->dreapta=minim;
        (minim->stanga)->dreapta=x;
        x->stanga=minim->stanga;
        minim->stanga=x;
        x->parinte=nullptr;
        x->mark= false;
    }
    void cascade_cut(nod* minim, nod* p){
        if(p->parinte!=nullptr and p->mark==false)
            p->mark=true;
        if(p->parinte!=nullptr and p->mark==true)
        {
            cut(minim,p,p->parinte);
            cascade_cut(minim,p->parinte);
        }

    }
    void stergere_nod(nod* k){
        decrease_nod(minim,k->numar,-2147483647);
        extragere_minim();
    }
    nod* cautare_nod(nod* minim, int x){
        nod* y;
        nod* c=minim;
        c->marcaj_cautare= true;
        if(c->numar==x)
        {
            c->marcaj_cautare= false;
            return c;
        }
        else{
            if(c->copil!=nullptr)
                y=cautare_nod(c->copil,x);
            if((c->dreapta)->marcaj_cautare==false)
                y=cautare_nod(c->dreapta,x);
        }
        c->marcaj_cautare=false;
        return y;
    }

    nod *getMinim() const {
        return minim;
    }

    void setMinim(nod *minim) {
        Fibonacci_Heap::minim = minim;
    }

    int getNrArbori() const {
        return nr_arbori;
    }

    void setNrArbori(int nrArbori) {
        nr_arbori = nrArbori;
    }
};
int main() {
   /* Fibonacci_Heap f;
    nod* p=f.creare_nod_nou(3);
    f.insert(p);
    p=f.creare_nod_nou(17);
    f.insert(p);
    p=f.creare_nod_nou(24);
    f.insert(p);
    p=f.creare_nod_nou(21);
    f.insert(p);
    p=f.getMinim();
    cout<<"minimul: "<<p->numar<<endl;

    if(p== nullptr)
        cout<<"heap gol";
    else{
        cout<<"Lista de radacini: ";
        nod* minim=p;
        cout<<p->numar<<' ';
        p=p->dreapta;
        while(p!=minim)
        {
            cout<<p->numar<<" ";
            p=p->dreapta;
        }
    }
    f.extragere_minim();
    p=f.getMinim();
    cout<<"\nminimul dupa extragere_minim: "<<p->numar<<endl;
    if(f.decrease_nod(f.getMinim(),17,2)==0)
        cout<<"S-a decrementat valoarea unui nod."<<endl;

*/
   Fibonacci_Heap h[105];
    int N,Q,op,p1,p2;
    f>>N>>Q;
    for(int i=1;i<=Q;i++)
    {
        f>>op;
        if(op==1)
        {
            f>>p1>>p2;
            cout<<p1<<p2;
            nod *p=h[p1].creare_nod_nou(p2);
            h[p1].insert(p);
        }
        else {
            if(op==2)
            {
                f>>p1;
                h[p1].extragere_minim();
                g<<h[p1].getMinim()<<endl;

            }
            else{
                if(op==3)
                {
                    f>>p1>>p2;
                    
                    h[p1].reuniune(h[p1].getMinim(),h[p2].getMinim());
                }
            }
        }

    }

    return 0;
}
