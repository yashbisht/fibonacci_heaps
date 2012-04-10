//fibonacci and binomial heap implementation and efficiency comparision for dijikstra algorithm on a graph of 500 nodes and different edge density
// author @yashbisht

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int ArrayWeight[501][501];
int AdjecencyList[501][501];
int MAX=0, flag = 0;
clock_t init = 0,T1;

class BNode
{

public:
    int value, degree, vertex, childCut;
    BNode *child, *sibling, *parent, *node;

    BNode(int v, int d, int ve, int cC, BNode* c, BNode* s, BNode* p, BNode* bs)
    {
        value = v;
        degree = d;
        vertex = ve;
        cC = childCut;
        child = c;
        sibling = s;
        parent = p;
        node = bs;
    }
};

BNode* root = new BNode(-1,-1,-1,0, NULL,NULL,NULL,NULL) ;

BNode* vertexPointer[500] = {NULL};
int vertexDis[2][500] ;

class BHeapCase
{



    // BNode* BinomialMeld(BNode* p1, BNode* p2);
public:

    void binomialInsert(int value, int ver)
    {


        BNode* one = new BNode(value,0,ver,0,NULL,NULL,root,NULL) ;
        vertexPointer[ver] = one;

        one->sibling = one;
        one->node = one;
        BNode* ptr = root->child;

        if(ptr!=NULL)
        {
//        while(ptr->sibling !=NULL)
//            ptr = ptr->sibling;

            BNode* t ;
            t= ptr->sibling;
            ptr->sibling = one;
            one->sibling = t;
            t->node = one;
            one->node = ptr;
            if (root->child->value > one->value)
                root->child= one;

        }
        else
            root->child = one;

//    cout << root->child->value<<"\n";

    }
    void MakeChild(BNode* parent, BNode* ch)
    {
        BNode* b = ch->node;
        BNode* n = ch->sibling;
        b->sibling = n;
        n->node = b;
        //  delete(root->child);   // delete min
        //root->child = n;
        ch->parent = parent;
        ch->node = ch;
        ch->sibling=ch;


        parent->child = BinomialMeld(parent->child,ch);
        //increase the dergee of parent by one.
        (parent->degree)++;

    }
    void PairwiseCombine()
    {
        BNode* a[20] = {NULL}; // merge use it in meld
        BNode* p = root->child;
        do
        {
            if(a[p->degree] == NULL)
            {
                //cout<<"degree"<<p->degree<<" ";
                a[p->degree] = p;
                p = p->sibling;
            }

            else
            {
                //combine a[p->degree], p and put it back;
                int t = p->degree;

                BNode* x = p->sibling;
                {
                    while(a[t] != NULL)
                    {
                        // cout<<"degreeww"<<p->degree<<" ";
                        BNode* c = a[p->degree];


                        if(p->value< c->value)
                        {
                            MakeChild(p,c);
                            a[t]= NULL;
                            t= p->degree;// set parent pointer after chnages....
                            p=p;
                        }
                        else
                        {
                            MakeChild(c,p);
                            a[t]= NULL;
                            t=c->degree;
                            p=c;
                        }


                    }
                    a[p->degree] = p;
                    p= p->sibling;

                }
//            else
//                MakeChild(c,p);

            }

        }
        while(p!= a[p->degree]);
        while(root->child->parent != NULL && root->child->parent != root)
        {
            root->child = root->child->parent;
        }
    }


    BNode* BinomialMeld(BNode* p1, BNode* p2)
    {
        // when p1 is null and when p2 is null
        //cout<<"here";
        if(p1 == NULL)
        {
            if(p2 != NULL)
                return p2;
        }
        else if(p1!= NULL)
        {
            if(p2 != NULL)
            {
                BNode* n = p1->sibling;
                p1->sibling = p2->sibling;
                p2->sibling->node = p1;
                p2->sibling = n;
                n->node = p2;

                //cout << "here 222222222";
                if(p1->value<=p2->value)
                    p2 = p1;

                return p2;
            }
            else
            {
                //print(root->child);
                return p1;
            }
        }





        //PairwiseCombine(root);


    }
    int BinomialDeleteMin ()
    {
        //print(root->child);
        // if there is just one node. or no nodes
        int v = root->child->vertex;

        if(root->child != NULL)
        {
            vertexDis[0][root->child->vertex] = root->child->value;
            vertexPointer[root->child->vertex] = NULL;

            if(root->child->sibling == root->child)
            {
                /// TODO: try to put root = root->child;
                if(root->child->child == NULL)
                {
                    delete(root->child);
                    root->child = NULL;
                    return v;

                }

                BNode*t = root->child;
                root->child = root->child->child;
                if(root->child != NULL)
                {
                    root->child->parent = root;
                    BNode* p9 = root->child->sibling;
                    while(p9!= root->child)
                    {
                        p9->parent = root;
                        p9 = p9->sibling;
                    }
                }
                delete(t);
            }

            else
            {
                BNode* p = root->child->child;

                BNode* b = root->child->node;
                BNode* n = root->child->sibling;
                b->sibling = n;
                n->node = b;
                delete(root->child);   //update the vertex array before this delete min
                root->child = n;


                BNode* p1 = root->child;
                BNode* t2 = root->child;
                do
                {
                    if(p1->value < t2->value)
                        t2 = p1;
                    p1 = p1->sibling;
                }
                while(p1!= root->child);  /// do this after meld in the loop used for etting parent.. or try to put set the root parent after pairwise ..
                root->child = t2;

                //cout<< root->child->value<<" ";
                // change the sibling pointer that points to root child  to root child->sibling

                //if(p!=NULL)
                //print(root->child);
                root->child = BinomialMeld(root->child, p);  // implement this

                //print(root->child);
                // cout<< root->child->value<<"after\n";
                p1 = root->child->sibling;
                t2 = root->child;
                t2->parent = root;
                while(p1!= root->child)
                {
                    p1->parent = root;
                    p1 = p1->sibling;
                }

            }

            PairwiseCombine();

        }


        return v;
    }

    void BinomialDecrease(int ver, int newvalue)
    {
        int CC = 0;
        BNode* p = vertexPointer[ver];
        p->value = newvalue;
        BNode* t = p->parent;
        p->childCut = 0;

        if(p->sibling == p)
        {
            //cout<<ver;
            t->child = NULL;
            p->parent = root;
            root->child = BinomialMeld(root->child,p);
            CC = t->childCut;


//        if(root->child->value > ->value)
//                t2 = p1;
//                p1 = p1->sibling;
//            }
//        t->child = t2;

            // print(root->child);

            if(CC == 1)
                BinomialDecrease(t->vertex,t->value);
            else if(CC ==0)
            {
                if(t != root)
                    t->childCut =1;
            }

        }
        else
        {
            BNode* b = p->node;
            BNode* n = p->sibling;
            b->sibling = n;
            n->node = b;
            p->sibling = p;
            p->node = p;
            p->parent = root;
            t->child = n;

            BNode* p1 = t->child->sibling;
            BNode* t2 = t->child;
            while(p1 != t->child)
            {
                if(p1->value < t2->value)
                    t2 = p1;
                p1 = p1->sibling;

            }
            t->child = t2;
            //set min value;
            //print(root->child);
            root->child = BinomialMeld(root->child,p);
            // print(root->child);
            CC = t->childCut;
            if(CC == 1)
//        while(CC != 0)
//        {
//            CC = t->parent->childCut;
                BinomialDecrease(t->vertex,t->value);

            else if(CC ==0)
            {
                if(t != root)
                    t->childCut =1;
            }
            // CC = 1;
        }

    }

    void BinomialDecrease1(int ver, int newvalue)
    {
        //cout << ver <<" "<< newvalue<<"  ";
        if(vertexDis[0][ver] != 1000000)
        {
            //cout<<"dddddddddddddddddddddddddddd"<< vertexDis[0][ver]<<"\n";
            return;
        }
        BNode* p = vertexPointer[ver];
        p->value = newvalue;
        BNode* t = p->parent;
        // cout<<" print inside binomial decrease"<<t->value<<"\n";
        //print(root->child);
        while(t != root)
        {
            if(t->value > p->value)
            {
                int vt = t->vertex;
                t->vertex = p->vertex;
                p->vertex = vt;
                vt = t->value;
                t->value = p->value;
                p->value = vt;

                vertexPointer[p->vertex] = p;
                vertexPointer[t->vertex] = t;

                t->child = p;
                //update vertex array
                t = t->parent;
                p = p->parent;
            }
            else
                break;
            // t= t->parent;
        }
        //p = t->child->sibling;
//        do
//        {
        if(p->value< t->child->value)
            t->child = p;
//            p = p->sibling;
//        }
//        while(p!=t->child);
    }

    void print(BNode* t)
    {
        if(t != NULL)
        {
            BNode* t2 = t;
            // t2 = t->child;
            if(t->parent != NULL)
                cout<<"( " <<t->parent->value<<" )";
            do
            {
                cout<< " "<<t2->value<<"["<<t2->degree<<"] ";
                t2 = t2->sibling;
            }
            while(t2!= t);
            cout<<"\n";


            BNode* p1 = t;
            // t2 = t->child;
            do
            {
                print(p1->child);
                p1 = p1->sibling;
            }
            while(p1!= t);
        }

        cout<<"\n";
    }


    void Dijikstra()
    {

        int l=0,count=0, temp;

        //cout << "in";

        for(int k =1 ; k <= MAX; k++)
        {
            count =0;

            T1 = clock();
            for(int i=1; i<=MAX; i++)
            {
                binomialInsert(1000000,i);
                vertexDis[0][i]=1000000;
                vertexDis[1][i]=0;
            }
            init += clock() - T1;
            //cout<<"here";
            //print(root->child);
            BinomialDecrease(k,0);
            int last_ver = 1;
            //cout<<"here";
            //print(root->child);


            while(count<MAX)
            {
                //cout<<last_ver<<" after delete min....     ..  \n";
                last_ver = BinomialDeleteMin();


                //cout<<" "<<last_ver<<" "<<count<<"\n";
                //print(root->child);


                //      s[++count]=u;
                vertexDis[1][last_ver] = 1;
                if(vertexDis[0][last_ver] != 1000000)
                    for(int l = 1; l <= AdjecencyList[last_ver][0]; l++)
                    {

                        int u = AdjecencyList[last_ver][l];
                        //cout<<" in"<<u;
                        //cout << "++++++" <<u << "   "<< vertexDis[last_ver] + ArrayWeight[last_ver][u]<<"\n";
                        if(vertexDis[1][u] != 1)
                        {

                            {
                                temp = vertexDis[0][last_ver] + ArrayWeight[last_ver][u];
                                if((vertexPointer[u])->value > temp)

                                {
                                    //cout << "ASASASAAS" <<"\n";
                                    // cout << "++++++" <<u << "   "<< vertexDis[last_ver] + ArrayWeight[last_ver][u]<<"\n";
                                    BinomialDecrease1(u,temp);
                                    // print(root->child);

                                }
                            }
                        }

                    }
                //cout<< "out   ";
                count++;

            }
            if(flag ==1)
            {
                cout << " ["<<k<<"] -  ";
                for(int j=1; j<= MAX; j++)
                {
                    l = (vertexDis[0][j] == 1000000)? -1 :vertexDis[0][j];

//                if(l == -1)
//                cout << "!@ ";
//                else
                    cout<<l<<"  ";
                }
                cout<<"\n";
            }

            root->child = NULL;
        }

    }
};


//******************Fibbonacci class***********************************************


class FNode
{

public:
    int value, degree, vertex, childCut;
    FNode *child, *sibling, *parent, *back_sib;

    FNode(int v, int d, int ve, int cC, FNode* c, FNode* s, FNode* p, FNode* bs)
    {
        value = v;
        degree = d;
        vertex = ve;
        cC = childCut;
        child = c;
        sibling = s;
        parent = p;
        back_sib = bs;
    }
};

FNode* Froot = new FNode(-1,-1,-1,0, NULL,NULL,NULL,NULL) ;

FNode* FvertexPointer[500] = {NULL};
class FHeapCase
{



    // FNode* FibonacciMeld(FNode* p1, FNode* p2);
public:

    void FibonacciInsert(int value, int ver)
    {


        FNode* one = new FNode(value,0,ver,0,NULL,NULL,Froot,NULL) ;
        FvertexPointer[ver] = one;

        one->sibling = one;
        one->back_sib = one;
        FNode* ptr = Froot->child;

        if(ptr!=NULL)
        {
//        while(ptr->sibling !=NULL)
//            ptr = ptr->sibling;

            FNode* t ;
            t= ptr->sibling;
            ptr->sibling = one;
            one->sibling = t;
            t->back_sib = one;
            one->back_sib = ptr;
            if (Froot->child->value > one->value)
                Froot->child= one;

        }
        else
            Froot->child = one;

//    cout << Froot->child->value<<"\n";

    }
    void MakeChild(FNode* parent, FNode* ch)
    {
        FNode* b = ch->back_sib;
        FNode* n = ch->sibling;
        b->sibling = n;
        n->back_sib = b;
        //  delete(Froot->child);   // delete min
        //Froot->child = n;
        ch->parent = parent;
        ch->back_sib = ch;
        ch->sibling=ch;


        parent->child = FibonacciMeld(parent->child,ch);
        //increase the dergee of parent by one.
        (parent->degree)++;

    }
    void PairwiseCombine()
    {
        FNode* a[20] = {NULL}; // merge use it in meld
        FNode* p = Froot->child;
        do
        {
            if(a[p->degree] == NULL)
            {
                //cout<<"degree"<<p->degree<<" ";
                a[p->degree] = p;
                p = p->sibling;
            }

            else
            {
                //combine a[p->degree], p and put it back;
                int t = p->degree;

                FNode* x = p->sibling;
                {
                    while(a[t] != NULL)
                    {
                        // cout<<"degreeww"<<p->degree<<" ";
                        FNode* c = a[p->degree];


                        if(p->value< c->value)
                        {
                            MakeChild(p,c);
                            a[t]= NULL;
                            t= p->degree;// set parent pointer after chnages....
                            p=p;
                        }
                        else
                        {
                            MakeChild(c,p);
                            a[t]= NULL;
                            t=c->degree;
                            p=c;
                        }


                    }
                    a[p->degree] = p;
                    p= p->sibling;

                }
//            else
//                MakeChild(c,p);

            }

        }
        while(p!= a[p->degree]);
        while(Froot->child->parent != NULL && Froot->child->parent != Froot)
        {
            Froot->child = Froot->child->parent;
        }
    }


    FNode* FibonacciMeld(FNode* p1, FNode* p2)
    {
        // when p1 is null and when p2 is null
        //cout<<"here";
        if(p1 == NULL)
        {
            if(p2 != NULL)
                return p2;
        }
        else if(p1!= NULL)
        {
            if(p2 != NULL)
            {
                FNode* n = p1->sibling;
                p1->sibling = p2->sibling;
                p2->sibling->back_sib = p1;
                p2->sibling = n;
                n->back_sib = p2;

                //cout << "here 222222222";
                if(p1->value<=p2->value)
                    p2 = p1;

                return p2;
            }
            else
            {
                //print(Froot->child);
                return p1;
            }
        }





        //PairwiseCombine(Froot);


    }
    int FibonacciDeleteMin ()
    {
        //print(Froot->child);
        // if there is just one node. or no nodes
        int v = Froot->child->vertex;

        if(Froot->child != NULL)
        {
            vertexDis[0][Froot->child->vertex] = Froot->child->value;
            FvertexPointer[Froot->child->vertex] = NULL;

            if(Froot->child->sibling == Froot->child)
            {
                /// TODO: try to put Froot = Froot->child;
                if(Froot->child->child == NULL)
                {
                    delete(Froot->child);
                    Froot->child = NULL;
                    return v;

                }

                FNode*t = Froot->child;
                Froot->child = Froot->child->child;
                if(Froot->child != NULL)
                {
                    Froot->child->parent = Froot;
                    FNode* p9 = Froot->child->sibling;
                    while(p9!= Froot->child)
                    {
                        p9->parent = Froot;
                        p9 = p9->sibling;
                    }
                }
                delete(t);
            }

            else
            {
                FNode* p = Froot->child->child;

                FNode* b = Froot->child->back_sib;
                FNode* n = Froot->child->sibling;
                b->sibling = n;
                n->back_sib = b;
                delete(Froot->child);   //update the vertex array before this delete min
                Froot->child = n;


                FNode* p1 = Froot->child;
                FNode* t2 = Froot->child;
                do
                {
                    if(p1->value < t2->value)
                        t2 = p1;
                    p1 = p1->sibling;
                }
                while(p1!= Froot->child);  /// do this after meld in the loop used for etting parent.. or try to put set the Froot parent after pairwise ..
                Froot->child = t2;

                //cout<< Froot->child->value<<" ";
                // change the sibling pointer that points to Froot child  to Froot child->sibling

                //if(p!=NULL)
                //print(Froot->child);
                Froot->child = FibonacciMeld(Froot->child, p);  // implement this

                //print(Froot->child);
                // cout<< Froot->child->value<<"after\n";
                p1 = Froot->child->sibling;
                t2 = Froot->child;
                t2->parent = Froot;
                while(p1!= Froot->child)
                {
                    p1->parent = Froot;
                    p1 = p1->sibling;
                }

            }

            PairwiseCombine();

        }


        return v;
    }

    void FibonacciDecrease(int ver, int newvalue)
    {
        int CC = 0;
        FNode* p = FvertexPointer[ver];
        p->value = newvalue;
        FNode* t = p->parent;
        p->childCut = 0;

        if(p->sibling == p)
        {
            //cout<<ver;
            t->child = NULL;
            p->parent = Froot;
            Froot->child = FibonacciMeld(Froot->child,p);
            CC = t->childCut;


//        if(Froot->child->value > ->value)
//                t2 = p1;
//                p1 = p1->sibling;
//            }
//        t->child = t2;

            // print(Froot->child);

            if(CC == 1)
                FibonacciDecrease(t->vertex,t->value);
            else if(CC ==0)
            {
                if(t != Froot)
                    t->childCut =1;
            }

        }
        else
        {
            FNode* b = p->back_sib;
            FNode* n = p->sibling;
            b->sibling = n;
            n->back_sib = b;
            p->sibling = p;
            p->back_sib = p;
            p->parent = Froot;
            t->child = n;

            FNode* p1 = t->child->sibling;
            FNode* t2 = t->child;
            while(p1 != t->child)
            {
                if(p1->value < t2->value)
                    t2 = p1;
                p1 = p1->sibling;

            }
            t->child = t2;
            //set min value;
            //print(Froot->child);
            Froot->child = FibonacciMeld(Froot->child,p);
            // print(Froot->child);
            CC = t->childCut;
            if(CC == 1)
//        while(CC != 0)
//        {
//            CC = t->parent->childCut;
                FibonacciDecrease(t->vertex,t->value);

            else if(CC ==0)
            {
                if(t != Froot)
                    t->childCut =1;
            }
            // CC = 1;
        }

    }

    void print(FNode* t)
    {
        if(t != NULL)
        {
            FNode* t2 = t;
            // t2 = t->child;
            if(t->parent != NULL)
                cout<<"( " <<t->parent->value<<" )";
            do
            {
                cout<< " "<<t2->value<<"["<<t2->degree<<"] ";
                t2 = t2->sibling;
            }
            while(t2!= t);
            cout<<"\n";


            FNode* p1 = t;
            // t2 = t->child;
            do
            {
                print(p1->child);
                p1 = p1->sibling;
            }
            while(p1!= t);
        }

        cout<<"\n";
    }


    void Dijikstra()
    {

        int l=0,count=0, temp;

        //cout << "in";

        for(int k =1 ; k <= MAX; k++)
        {
            count =0;

            T1 = clock();
            for(int i=1; i<=MAX; i++)
            {
                FibonacciInsert(1000000,i);
                vertexDis[0][i]=1000000;
                vertexDis[1][i]=0;
            }
            init += clock() - T1;
            //cout<<"here";
            //print(Froot->child);
            FibonacciDecrease(k,0);
            int last_ver = 1;
            //cout<<"here";
            //print(Froot->child);


            while(count<MAX)
            {
                //cout<<last_ver<<" after delete min....     ..  \n";
                last_ver = FibonacciDeleteMin();


                //cout<<" "<<last_ver<<" "<<count<<"\n";
                //print(Froot->child);


                //      s[++count]=u;
                vertexDis[1][last_ver] = 1;
                if(vertexDis[0][last_ver] != 1000000)
                    for(int l = 1; l <= AdjecencyList[last_ver][0]; l++)
                    {

                        int u = AdjecencyList[last_ver][l];
                        //cout<<" in"<<u;
                        //cout << "++++++" <<u << "   "<< vertexDis[last_ver] + ArrayWeight[last_ver][u]<<"\n";
                        if(vertexDis[1][u] != 1)
                        {

                            {
                                temp = vertexDis[0][last_ver] + ArrayWeight[last_ver][u];
                                if((FvertexPointer[u])->value > temp)

                                {
                                    //cout << "ASASASAAS" <<"\n";
                                    // cout << "++++++" <<u << "   "<< vertexDis[last_ver] + ArrayWeight[last_ver][u]<<"\n";
                                    FibonacciDecrease(u,temp);
                                    // print(Froot->child);

                                }
                            }
                        }

                    }
                //cout<< "out   ";
                count++;

            }
            if(flag ==1)
            {
                cout << " ["<<k<<"] -  ";
                for(int j=1; j<= MAX; j++)
                {
                    l = (vertexDis[0][j] == 1000000)? -1 :vertexDis[0][j];

//                if(l == -1)
//                cout << "!@ ";
//                else
                    cout<<l<<"  ";
                }
                cout<<"\n";
            }


            Froot->child = NULL;
        }


//        cout<<"\n\n";


    }
};



//*************** Simple CASE Class and implementation *****************************************************

class simpleCase
{
public:
    int Array[2][501],s[501];
    int N_Ver;
    simpleCase(int N)
    {
        N_Ver = N;
    }

    void Initialise()
    {
        for(int j=1; j<=N_Ver; j++)
        {
            Array[1][j]=0;
            Array[0][j]=1000000;
        }
    }

    void Dijikstra()
    {



        //*******initializing source*******************//
        for(int k =1 ; k <= N_Ver; k++)
        {
            Initialise();
            int count =0,u=0;
            Array[0][k]=0;
            //Array[1][k]=1;


            while(count<N_Ver)
            {
                u = ArrayMinimum(Array[0],Array[1],N_Ver);

                //      s[++count]=u;
                Array[1][u]=1;
                for(int i=1; i<=N_Ver; i++)
                {
                    if(ArrayWeight[u][i]>0)
                    {
                        if(Array[1][i]!=1)
                        {
                            if(Array[0][i]>Array[0][u]+ArrayWeight[u][i])
                            {
                                Array[0][i]=Array[0][u]+ArrayWeight[u][i];
                            }
                        }
                    }
                }
                count++;
//
            }
            if(flag == 1)
            {
                cout << " ["<<k<<"] -  ";
                for(int j=1; j<= N_Ver; j++)
                {
                    int l = (Array[0][j] == 1000000)? -1 : Array[0][j];
                    cout<<l<<" ";
                }
  	cout<<"\n";
            }


//            cout<<"\n";
        }
    }

    int ArrayMinimum(int dis[],int marked[],int k)
    {
        int min=1000000,index = 0;
        for(int i=1; i<=k; i++)
        {
            if(marked[i]!=1)
            {
                if(min>=dis[i])
                {
                    index=i;
                    min=dis[i];
                }
            }
        }
        return index;
    }

};

void readFromInput()
{
    int u,v,d;
    cout<<"Input edges and weights line by line, put -1 to end  e.g [E1] [E2] [cost]\n";
    while(true)
    {
        cin>>u;
        //cout << u;

        if(u != -1)
        {
            MAX = (MAX<u)?u:MAX;
            cin>>v;
            MAX = (MAX<v)?v:MAX;
            cin>>d;
            //cout<<v;
            //

            ArrayWeight[u][v]  = d;
            AdjecencyList[u][0] += 1;
            AdjecencyList[u][AdjecencyList[u][0]] = v;

        }
        else
            break;
    }
    //cout<<"outhere"<<u<<v<<d;

}

void ReadfromFile(char path[])
{
    string line,ss;
    int u,v,D,j=0;
//	string path2 = "/cise/homes/ysbisht/Desktop/ads_project/in.txt";

    ifstream myfile(path);
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            //cout<<"good";
            u = -1;
            v = -1;
            D = -1;
            getline (myfile,line);
            if(line.compare("*"))          //return 0 if matched
            {
                j=0;
                for(int i = 0; i< line.length(); i++)
                {
                    if(line[i] == ' ')
                    {
                        if(u == -1)
                        {
                            u = atoi(line.substr(j,i).c_str());
                            if(MAX < u) MAX = u;
                        }
                        else if (v == -1)
                        {
                            v = atoi(line.substr(j,i).c_str());
                            if(MAX < v) MAX = v;
                        }

                        j= i+1;
                    }

                }

                D = atoi(line.substr(j,line.length()-1).c_str());
                ArrayWeight[u][v]  = D;
                AdjecencyList[u][0] += 1;
                AdjecencyList[u][AdjecencyList[u][0]] = v;
                // u = atoi(ss.substr(1,-2).c_str());
                //cout<<"in.txt"<< u<<" "<<v<<" "<<D<<"\n";

            }
		else
			break;
        }
	//cout<<"not good";
        myfile.close();

    }
    else
        cout<<"unable to open"<<path;

	//cout<<"out of read file";
}

int randGenerator(int range)
{
    return (rand() % range) ;
}


int main(int argc, char* argsv[])
{

    //cout<<argc;
	flag =0;
    for(int i = 0; i< 501; i++)
        for(int j = 0; j< 501; j++)
        {
            ArrayWeight[i][j] = 1000000;
            AdjecencyList[i][j] = -1;
        }
    for(int u=0; u<501; u++)
        AdjecencyList[u][0] = 0;


    //*************************************** Using Arguments to define the mode **********************************//
   // cout<<"yash";

    //if(strcmp(argsv[1], "-r") == 0)
    if(strcmp(argsv[1], "-r") == 0)
    {
        cout<<"random mode"<<endl;



        int v1,v2,cost;
        int vnum = 0, density = 0;
        clock_t Simple_time, Binomial_time, Fibonacci_time, TT;

        cout<< " No. of Ver.       Density      SimpleCase         BinomialCase        FibonacciCase \n";

        for(int N_V = 100; N_V < 501 ; N_V = N_V+100)
        {
            for(int t =1 ; t<=10 ; t++ )
            {
                vnum = 0;
                int N_e = (N_V*(N_V-1)/10)*(t) ;            // Defining no. of edges in the graph
                if(t == 10)
                    N_e -= N_V*2;
                // cout<<N_e<<"\n";
                while(vnum != N_e)                          // generating edges with vertices v1, v2 and weight cost
                {
                    v1 = randGenerator(N_V-1)+1;
                    v2 = randGenerator(N_V-1)+1;
                    if(ArrayWeight[v1][v2] == 1000000 && v1!= v2)
                    {
                        int st = (v1>v2)?v1:v2;
                        MAX = (MAX > st)? MAX : st ;
                        cost = randGenerator(1000) + 1;
                        ArrayWeight[v1][v2] = cost;                        //storing the edge weights
                        AdjecencyList[v1][0] += 1;                       // creating the sdjecency list
                        AdjecencyList[v1][AdjecencyList[v1][0]] = v2;
                        vnum++;
                    }
                }
                //cout<<"yyyy";


                clock_t Simple_time=0, Binomial_time=0, Fibonacci_time=0, TT=0;

                //Calculating time for simple Array Implementation
                //for(int t =0; t<1; t++)
                {
                    TT = clock();
                    simpleCase* SC = new simpleCase(MAX);
                    SC->Dijikstra();
                    Simple_time += clock() - TT;
                }



                // Calculating time for Binomial Implementation
               // for(int t =0; t<1; t++)
                {
                    TT = clock();
                    BHeapCase* BC = new BHeapCase();
                    BC->Dijikstra();
                    Binomial_time += clock() - TT;
                }



                //Calculating time for Fibonaccci Implementation
                Fibonacci_time = clock();

                //Fibonaacii ->dijikstra;
                FHeapCase* FC = new FHeapCase();
                FC->Dijikstra();

                Fibonacci_time = clock()/2 - Fibonacci_time/2;

                for(int i = 0; i< 501; i++)
                    for(int j = 0; j< 501; j++)
                    {
                        ArrayWeight[i][j] = 1000000;
                        AdjecencyList[i][j] = -1;
                    }
                for(int u=0; u<501; u++)
                    AdjecencyList[u][0] = 0;

                cout<<"       "<<N_V<<"         "<<t*10<<"%            "<<Simple_time/1000<<"                    "<<Binomial_time/1000 <<"              "<<Fibonacci_time/1000<<"\n";


            }
            cout<<"\n";
        }

    }

    if(strcmp(argsv[1], "-is") == 0)
    {
        flag = 1;
	//cout<<argsv[2];
	cout<<"simple scheme\n";
	//cout<<argsv[2];
        if(argc == 3)
        {
            //read input from the file
            cout<<"reading input from file";
          //  cout<<"argsv[2]";
		ReadfromFile(argsv[2]);
        }
        else
        {
            //get input from user
            readFromInput();
        }
        //printGraph(g);
       // cout<<"cout:"<<endl;
        //create graph using above input and call dijkstra.
        clock_t TT, Simple_timeS;

        TT = clock();
        simpleCase* SC = new simpleCase(MAX);
        SC->Dijikstra();
        Simple_timeS = clock() - TT;

        //cout<<"  "<<Simple_timeS<<"   \n";



    }

    if(strcmp(argsv[1], "-ib") == 0)
    {
        flag  = 1;
        cout<<"B-heap scheme"<<endl;
        if(argc == 3)
        {
            //read input from the file
            ReadfromFile(argsv[2]);
        }
        else
        {
            //get input from user
            readFromInput();
        }

        clock_t TT, Binomial_timeB;

        TT = clock();
        BHeapCase* BC = new BHeapCase();
        BC->Dijikstra();
        Binomial_timeB = clock() - TT;

        //cout<<"  "<<Binomial_timeB - init<<"   "<<init << "\n";


    }

    if(strcmp(argsv[1], "-if") == 0)
    {
        flag = 1;
        cout<<"F-heap scheme"<<endl;
        if(argc == 3)
        {
            //read input from the file
            ReadfromFile(argsv[2]);
        }
        else
        {
            //get input from user
            readFromInput();
        }
        clock_t TT, Fibonacci_timeF;

        TT = clock();
        FHeapCase* FC = new FHeapCase();
        FC->Dijikstra();
        Fibonacci_timeF = clock() - TT;

        //cout<<"  "<<Fibonacci_timeF - init<<"   "<<init << "\n";



    }




    //**********************************************************************************************************//





    return 1;
}


