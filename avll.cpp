#include <iostream>
#define IZQ 1
#define BA 0
#define DER -1
#define FALSE 0
#define TRUE 1
using namespace std;

struct AVL
{
    int info;
    int bal ;
    AVL *ri, *rd;
};

AVL *insertar(AVL *a, AVL* p, int &MasAlto);
AVL *insertarAVL(AVL* a, int elem);
AVL *roteIzq(AVL *a);
AVL *roteDerIzq(AVL *a);
AVL *balanceaDer(AVL *a);
AVL* eli(AVL* A, char x);

AVL* eli(AVL* A, char x)
{
    AVL *p;
    char Mayor;
    if(A->info == x)
    {
        if(A->izq == NULL && A->der==NULL)   // caso 1: El elemento se encuentra en una hoja
        {
            delete A;
            return NULL;
        }
        else if(A->izq == NULL)		// caso 2: La rama izquierda del dato es nula y en la derecha
        {
            p= A->der;                              //             hay informaci�n
            delete A;
            return p;
        }
        else
        {
            Mayor=MayorElem(A->izq);     // Caso 3:  Que sea un arbol interno con rama izq. y rama der.
            A->dato = Mayor;
            A->izq = eli(A->izq,Mayor);
        }
    }
    else if (A->dato > x)				// Parte recursiva para recorrer el arbol hasta encontrar elemento
        A->izq = eli(A->izq,x);
    else
        A->der = eli(A->der,x);
    return A;
}

// Funcion Ingreso
AVL* ing_arbol(AVL *A, char x, int a)
{
    if(A==NULL)
    {
        A= new arbol;
        if(!A)
        {
            cout << "NO HAY SUFICIENTE MEMORIA ";
            return A;
        }
        A->dato=x;
        A->izq=A->der=NULL;
        A->freq=a;
    }
    else    if(A->dato < x)
        A->der=ing_arbol(A->der,x,a);
    else if (A->dato > x)
        A->izq=ing_arbol(A->izq,x,a);
    else
        A->freq=A->freq+a;
    return A;
}

// Funci�n que determina si el elemento x est� en el arbol (retorna 1) o no esta (retorna 0)
int esta(AVL *A, char x)
{
    if (!A)
        return 0;
    if(A->dato==x)
        return 1;
    if(A->dato < x)
        return(esta(A->der,x));
    else
        return(esta(A->izq,x));
}


//Funci�n para eliminar un arbol del �rbol
AVL *elimina(char x,AVL *R)
{

    if (R  && esta(R,x)==1)
        R=eli(R,x);	// Elimina s�lo si el elemento se encuentra en el �rbol
    else
    {
        cout << endl <<"EL ELEMENTO NO SE ENCUENTRA, NO PUEDE SER ELIMINADO";
        cin.get();
    }
    return R;
}


void inorden(AVL *A)    // Funci�n que recorre el arbol IRD
{
    if(A)
    {
        inorden(A->izq);
        cout << A->dato <<"\t"<<A->freq<<endl;
        inorden(A->der);
    }
}

void preorden(arbol *A)        // Funci�n que recorre el arbol RID
{
    if(A)
    {
        cout << A->dato <<"\t";
        preorden(A->izq);
        preorden(A->der);
    }
}

void postorden(arbol *A)             // Funci�n que recorre el arbol IDR
{
    if(A)
    {
        postorden(A->izq);
        postorden(A->der);
        cout << A->dato <<"\t";
    }
}

AVL *insertarAVL(AVL* a, int elem)
{
    AVL *p;
    int MasAlto;
    p = new AVL;
    p->ri = p->rd = NULL;
    p->info = elem;
    p->bal = BA;
    return insertar(a,p, MasAlto);
}

AVL *insertar(AVL *a, AVL* p, int &MasAlto)
{
    if (a == NULL)
    {
        MasAlto=TRUE;
        a=p;
    }
    else if(a->info > p->info)
    {
        a->ri = insertar(a->ri,p,MasAlto);
        if(MasAlto)
            switch(a->bal)
            {
            case IZQ :
                MasAlto = FALSE;
                a=roteIzq(a);
                break;
            case BA :
                a->bal = IZQ;
                break;
            case DER :
                MasAlto = FALSE;
                a->bal = BA;
                break;
            }
    }
    else
    {
        a->rd = insertar(a->rd,p,MasAlto);
        if(MasAlto)
            switch(a->bal)
            {
            case IZQ :
                MasAlto = FALSE;
                a->bal = BA;
                break;
            case BA :
                a->bal = DER;
                break;
            case DER :
                MasAlto = FALSE;
                a = balanceaDer(a);
                break;
            }
    }
    return a;
}

// Función que genera una rotación simple a la Izquierda
AVL *roteIzq(AVL *a)
{
    AVL *q = a->rd;
    a->rd = q->ri;
    q->ri = a;
    return q;
}

// Función que genera una rotación doble Derecha Izquierda
AVL *roteDerIzq(AVL *a)
{
    a->rd=balanceaDer(a->rd);
    return roteIzq(a);
}

// Función para balancear el subárbol derecho de un arbol AVL (caso 2 ó caso 4)
AVL *balanceaDer(AVL *a)
{
    if(a->rd->bal == DER) //Caso 2
    {
        a->bal = a->rd->bal = BA;
        a=roteIzq(a);
    }
    else //Caso 4
    {
        switch(a->rd->ri -> bal)
        {
        case IZQ:
            a->bal = BA;
            a->rd->bal = DER;
            break;
        case BA:
            a->bal = a->rd->bal = BA;
            break;
        case DER :
            a->bal = IZQ;
            a->rd->bal = BA;
            break;
        }
        a->rd->ri->bal = BA;
        a=roteDerIzq(a);
    }
    return a;
}

int main()
{
    return 0;
}
