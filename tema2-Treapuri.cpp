#include <iostream>
#include<time.h>
#include<limits.h>

using namespace std;

struct TreapNode {
    int key, priority;
    TreapNode* left, * right;
};

TreapNode* Search(TreapNode* tr, int key) {
    //null sau cheie in radacina:
    if (tr == NULL or tr->key == key) return tr;
    //cheie<radacina:
    if (tr->key > key) return Search(tr->left, key);
    return Search(tr->right, key);
}

TreapNode* New(int key) {
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand() % 100;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreapNode* RotLeft(TreapNode* x) {
    TreapNode *y, *T2;
    y = x->right;
    T2 = y->left;
    //rotatia:
    y->left = x;
    x->right = T2;

    return y;
}

TreapNode* RotRight(TreapNode* y) {
    TreapNode* x, * T2;
    x = y->left;
    T2 = x->right;
    //rotatia:
    x->right = y;
    y->left = T2;
    
    return x;
}

TreapNode* Insert(TreapNode* tr, int key) {
    //null-> facem un nodd nou:
    if (tr == NULL) return New(key);
    //cheie<=radacina:
    if (key <= tr->key) {
        //inseram in partea stanga:
        tr->left = Insert(tr->left, key);
        if (tr->left->priority > tr->priority)
            tr = RotRight(tr);

    }
    else {
        //inseram in partea dreapta:
        tr->right = Insert(tr->right, key);
        if (tr->right->priority > tr->priority)
            tr = RotLeft(tr);

    }

    return tr;

}

TreapNode* Delete(TreapNode* tr, int key) {
    if (tr == nullptr) return tr;
    if (key < tr->key)
        tr->left = Delete(tr->left, key);
    else if (key > tr->key)
        tr->right = Delete(tr->right, key);
    else if (tr->left == NULL)
    {
        // Copilul din dreapta=radacina:
        TreapNode* temp = tr->right;
        delete(tr);
        tr = temp;  
    }
    else if (tr->right == NULL)
    {
        //Copilul din stanga=radacina:
        TreapNode* temp;
        temp= tr->left;
        delete(tr);
        tr = temp;  
    }

    // Daca cheia este in radacina si left si right nu sunt nule:
    else if (tr->left->priority < tr->right->priority)
    {
        tr = RotLeft(tr);
        tr->left = Delete(tr->left, key);
    }
    else
    {
        tr = RotRight(tr);
        tr->right = Delete(tr->right, key);
    }

    return tr;
}

int Min(TreapNode* tr) {
    //base case:
    if (tr == NULL) return INT_MAX;
    TreapNode* copy;
    copy = tr;
    //frunza cea mai din stg:
    while (copy->left != NULL) {
        copy = copy->left;
    }
    return(copy->key);
}

int Max(TreapNode* tr) {
    //base case:
    if (tr == NULL)
        return INT_MIN;

    //Max a 3 valori:
    //cheia radacinii, max din stg si max din dr
    int Max1 = tr->key;
    int Max2 = Max(tr->left);
    int Max3 = Max(tr->right);
    if (Max2 > Max1)
        Max1 = Max2;
    if (Max3 > Max1)
        Max1 = Max3;
    return Max1;
}

void Succesor(TreapNode* tr, TreapNode*& succ, int key) {
    //base case:
    if (tr == NULL or Max(tr) <= key) return;
    ///Daca cheia se afla in radacina:
    if (tr->key == key)
    {

        if (tr->right != NULL)
        {
            TreapNode* temp = tr->right;
            while (temp->left)
                temp = temp->left;
            succ = temp;
        }
        return;
    }

    if (tr->key > key)
    {
        succ = tr;
        Succesor(tr->left, succ, key);
    }
    else
    {
        Succesor(tr->right, succ, key);
    }
}

void Predecesor(TreapNode* tr, TreapNode*& pred, int key) {
    //base case:
    if (tr == NULL or Min(tr) >= key)  return;

    ///Daca cheia se afla in radacina:
    if (tr->key == key)
    {
        ///Val max din stanga este predecesor:
        if (tr->left != NULL)
        {
            TreapNode* temp = tr->left;
            while (temp->right)
                temp = temp->right;
            pred = temp;
        }
        return;
    }

    ///Daca cheia din radacina > cheie, cautam in dreapta:
    if (tr->key > key)
    {
        Predecesor(tr->left, pred, key);
    }
    else
    {
        pred = tr;
        Predecesor(tr->right, pred, key);
    }
}

void AfisOrd(TreapNode* tr){
    if (tr)
    {
        AfisOrd(tr->left);
        cout << "Key: " << tr->key << " | Priority: "<< tr->priority;
        if (tr->left)
            cout << " | Left Child: " << tr->left->key;
        if (tr->right)
            cout << " | Right Child: " << tr->right->key;
        cout << endl;
        AfisOrd(tr->right);
    }
}

void AfisCresc(TreapNode* tr){
    if (tr == NULL) return;
    if (tr != NULL)
    {
        AfisCresc(tr->left);
        cout << tr->key << "  ";
        AfisCresc(tr->right);
    }
}

void AfisInterval(TreapNode* tr, int x, int y){
    if(tr)
    {
        AfisInterval(tr->left,x,y);
        if(tr->key >= x and tr->key <=y) cout<<tr->key<<" ";
        AfisInterval(tr->right,x,y);
    }
    return;
}

int main()
{
    srand(time(0));
    struct TreapNode* tr = NULL;
    bool ok = 0;
    int q, alg, val, i, x, y;
    cin >> q;
    for (i = 1; i <= q; i++) {
        //1=cautare, 2=inserare, 3=stergere, 4=succesor, 5=predecesor, 6=afisare elemente interval
        cin >> alg;
        switch (alg) {
        case 1: {
            cout << "Valoare cautata:";
            cin >> val;
            TreapNode* res = Search(tr, val);
            if (res == NULL) cout << "Nu a fost gasita.";
            else cout << "A fost gasita";
            cout << endl;
            break;
        }
        case 2: {
            cout << "Valoare de inserare:";
            cin >> val;
            tr = Insert(tr, val);
            cout << "Valoarea a fost inserata." << endl;
            break;
        }
        case 3: {
            if (tr == nullptr) {
                cout << "Nu e niciun element de sters." << endl;
                continue;
            }
            cout << "Valoare de sters: ";
            cin >> val;
            TreapNode* res = Search(tr, val);
            if (res != nullptr) ok = 1;
            else {
                cout << "Valoarea nu a fost gasita." << endl;
                continue;
            }
            tr = Delete(tr, val);
            if (ok == 1 and res != nullptr) cout << "Valoarea a fost stearsa." << endl;
            break;
        }
        case 4: {
            TreapNode* succ = NULL;
            cout << "Valoare pt care se cauta succesorul:";
            cin >> val;
            Succesor(tr, succ, val);
            if (succ == NULL) cout << "Valoarea nu are succesor." << endl;
            else cout << "Succesorul este: " << succ->key << endl;
            break;
        }
        case 5: {
            TreapNode* pred = NULL;
            cout << "Valoarea pt care se cauta predecesorul:";
            cin >> val;
            Predecesor(tr, pred, val);
            if (pred == NULL) cout << "Valoarea nu are predecesor." << endl;
            else cout << "Predecesorul este: " << pred->key << endl;
            break;
        }
        case 6: {
            cout<<"Intervalul:";
            cin>>x>>y;
            cout<<"Numerele sunt:";
            AfisInterval(tr,x,y);
            cout << endl;
            break;
        }
        }

    }
    return 0;
}


