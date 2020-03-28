#bubblesort
#countsort
#radixsort
#mergesort
#quicksort

def generare_vector(nr_numere, nr_max):
    import random
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

def radixsort(lista, nr_max):
    return lista

l=generare_vector(10,100)
print(l)
lb=bubblesort(l)
print(lb)

nr=100
lc=countsort(l,nr)

print(lc)
