import numpy as np
nummern = np.random.rand(5,1)*100
nummern = nummern.astype(int) #make it nicer to read
print('This list must be sorted')
print(nummern)

# Preprocessing
# create vector that can be divided by two
added=(nummern.size%2)
if added != 0:
    added=1
    while(added<nummern.size):
        added = 2*added
    added = added - nummern.size
    nummern = np.concatenate([nummern,np.zeros((added,1))])

def mergesort(nen):
    if nen.size>1:
        half = int(nen.size/2)
        nen = merge(mergesort(nen[:half]), mergesort(nen[half:]))
    return nen

def merge(left,right):
    leng = int(left.size)
    nen = np.zeros((leng*2,1))
    l,r,n = 0,0,0
    while(l<leng and r < leng):
        if(left[l]<right[r]):
            nen[n]=left[l]
            l +=1
        else:
            nen[n]=right[r]
            r +=1
        n += 1

    while(l<leng):
        nen[n] = left[l]
        l += 1
        n += 1

    while(r<leng):
        nen[n] = right[r]
        r += 1
        n += 1

    return nen

nummern = mergesort(nummern)

print('\nAfter sorting')
print(nummern[added:])