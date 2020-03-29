#bubblesort
#countsort
#radixsort
#mergesort
#quicksort

import random
import datetime


def generare_vector(nr_numere, nr_max):
    lista = []
    for i in range(0,nr_numere):
        element = random.randint(1,nr_max)
        lista.append(element)
    return lista

def bubblesort(lista):
    lungime=len(lista)
    for i in range(lungime):
        for j in range(lungime-i-1):
            if lista[j]>lista[j+1]:
                lista[j],lista[j+1]=lista[j+1],lista[j]
    return lista

def countsort(lista, nr_max):
    aparitii=[0]*(nr_max+1)
    for i in lista:
        aparitii[i]+=1
    lista.clear()
    for i in range(nr_max+1):
        while aparitii[i]:
            lista.append(i)
            aparitii[i]-=1
    return lista

def radixsort10(lista, nr_max):
    maxi=nr_max
    cifre=0
    while(maxi!=0):
        maxi=maxi//10
        cifre+=1
    for exp in range(0,cifre):
        bucket = [[] for p in range(10)]
        for i in lista:
            bucket[(i//(10**exp))%10].append(i)
        index=0
        for i in range(10):
            for j in range(len(bucket[i])):
                lista[index] = bucket[i][j]
                index += 1
    return lista

def radixsort256(lista):
    for exp in range(0, 32, 8):
        bucket = [[] for p in range(256)]
        for i in lista:
            bucket[(i >> exp) & 255].append(i)
        index = 0
        for i in range(256):
            for j in range(len(bucket[i])):
                lista[index] = bucket[i][j]
                index += 1
    return lista

def mergesort(lista):
    if len(lista) <= 1:
        return lista
    else:
        mij=len(lista)//2
        stanga=mergesort(lista[:mij])
        dreapta=mergesort(lista[mij:])
        return  interclasare(stanga,dreapta)

def interclasare(stanga,dreapta):
    st=dr=0
    both=[]
    while st<len(stanga) and dr<len(dreapta):
        if stanga[st] <= dreapta[dr]:
            both.append(stanga[st])
            st+=1
        else:
            both.append(dreapta[dr])
            dr+=1
    both.extend(stanga[st:])
    both.extend(dreapta[dr:])
    return both

#voi face quicksort varianta cu median of three:
def quicksort(lista, stanga, dreapta):
    if stanga < dreapta:
        p=partition(lista,stanga,dreapta)
        quicksort(lista,stanga,p-1)
        quicksort(lista,p+1,dreapta)
    return lista

def partition(lista,stanga,dreapta):
    p=pivot(lista,stanga,dreapta)
    comp=lista[p]
    lista[p],lista[stanga]=lista[stanga],lista[p]
    poz=stanga
    for i in range(stanga,dreapta+1):
        if lista[i]<comp:
            poz+=1
            lista[i],lista[poz]=lista[poz],lista[i]
    lista[stanga],lista[poz]=lista[poz],lista[stanga]
    return poz

def pivot(lista,stanga,dreapta):
    mij=(stanga+dreapta)//2
    p=dreapta
    if lista[stanga]<lista[mij]:
        if lista[mij]<lista[dreapta]:
            p=mij
    elif lista[stanga]<lista[dreapta]:
        p=stanga
    return p

def testare(lista):
    n = len(lista)
    for i in range(1, n):
        if lista[i] < lista[i - 1]:
            return 0
    return 1


lista=generare_vector(10,100)

l=list(lista)

t1=datetime.datetime.now()
l.sort()
t2=datetime.datetime.now()

print("Functia implicita sort: ")
print(t2-t1)

l=list(lista)
t1=datetime.datetime.now()
lb=bubblesort(l)
t2=datetime.datetime.now()
print(lb)

nr=100
lc=countsort(l,nr)

print(lc)

lr1=radixsort10(l,100)
print(lr1)

lr2=radixsort256(l)
print(lr2)

lm=mergesort(l)
print(lm)

lq=quicksort(l,0,len(l)-1)
print(lq)
