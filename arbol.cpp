//Programa que define el tipo arbol y realiza las funciones elementales (insertar, eliminar, mostrar)
//Algoritmos y Estructuras de Datos

// Prof. Rosa Barrera Capot

#include<iostream>
using namespace std;
// Declaraci�n del tipo de dato.
struct arbol
{
    int dato;
    arbol *izq;
    arbol *der;
};



// Declaraci�n de funciones

arbol* eli(arbol* A, int x);      // Elimina un arbol, recibe como par�metro la ra�z y el elemento a eliminar
arbol *ing_arbol(arbol* A,int x);    // Crea un arbol, recibe como par�metro la ra�z y el elemento a ingresar
void inorden(arbol *A);         // Recorre el �rbol en inorden
void preorden(arbol *A);      // Recorre el �rbol en preorden
void postorden(arbol *A);    // Recorre el �rbol en postorden
int MayorElem(arbol *A);    // Encuentra el mayor elemento de un �rbol
int esta(arbol *A, int x);       // Retorna un 1 si el elemento est� en el �rbol y un 0 si no �sta
void mostrar();		    //Muestra los elementos del arbol
int contar(arbol *A);
int suma(arbol *A);

// Una de las pocas funciones que se pueden realizar sin recursividad.
int MayorElem(arbol *A)
{
    while(A->der)
        A=A->der;
    return(A->dato);
}


// Funci�n que elimina un arbol del �rbol (tres casos)
arbol* eli(arbol* A, int x)
{
    arbol *p;
    int Mayor;
    if(A->dato == x)
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
arbol* ing_arbol(arbol *A,int x)
{
    if(A==NULL)
    {
        A= new arbol;
        if(!A)
        {
            cout<< "NO HAY SUFICIENTE MEMORIA ";
            return A;
        }
        A->dato=x;
        A->izq=A->der=NULL;
    }
    else    if(A->dato < x)
        A->der=ing_arbol(A->der,x);
    else if (A->dato > x)
        A->izq=ing_arbol(A->izq,x);
    else
    {
        cout << "EL ELEMENTO YA EXISTE, NO PUEDE ESTAR REPETIDO";
        cin.get();
    }
    return A;
}
// Funci�n que determina si el elemento x est� en el arbol (retorna 1) o no esta (retorna 0)
int esta(arbol *A, int x)
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
arbol *elimina(int x, arbol *R)
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


void inorden(arbol *A)    // Funci�n que recorre el arbol IRD
{
    if(A)
    {
        inorden(A->izq);
        cout << A->dato <<"\t";
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

int suma(arbol *A)
{
    if(A)
        return (suma(A->izq)+suma(A->der)+A->dato);
}

int contar(arbol *A)
{
    int cont;
    if(A)
        cont=contar(A->izq)+contar(A->der)+1;
    return cont;
}

// Funci�n que elige la forma de mostrar los datos
void mostrar(arbol *a)
{
    int op,x, sum,cont;
    do
    {
        cout <<endl<<"\t\tMENU"<<endl;
        cout <<"\t 1. Inorden"<<endl;
        cout <<"\t 2. Preorden"<<endl;
        cout <<"\t 3. Posorden"<<endl;
        cout <<"\t 4. Para eliminar un elemento"<<endl;
        cout <<"\t 5. Para saber cuantos elementos hay"<<endl;
        cout <<"\t 6. Para sumar lo elementos"<<endl;
        cout <<"\t 7. Salir"<<endl;
        cout <<"      Opcion:  ";
        cin >> op;
        switch(op)
        {
        case 1 :
            inorden(a);
            cout << endl<<"Presione una tecla para continuar";
            cin.get();
            break;
        case 2 :
            preorden(a);
            cout << endl<<"Presione una tecla para continuar";
            cin.get();
            break;
        case 3 :
            postorden(a);
            cout <<endl<< "Presione una tecla para continuar";
            cin.get();
            break;
        case 4 :
            cout << "Ingrese elemento a eliminar :   ";
            cin >> x;
            a=elimina(x,a);
        case 5 :
            cont=contar(a);
            cout<<cont;
        case 6 :
            sum=suma(a);
            cout<<sum;
        }
    }
    while(op!=7);
}


// programa principal
int main()
{
    arbol *a;
    int n,x;
    a= NULL;
    cout <<"Cuantos datos desea ingresar : ";
    cin >> n;
    do
    {
        cout <<"Ingrese dato a arbol :" ;
        cin >> x;
        a=ing_arbol(a,x);
        n--;
    }
    while(n!=0);
    mostrar(a);
    while (a)
        a=eli(a,a->dato);
    return 0;
}
