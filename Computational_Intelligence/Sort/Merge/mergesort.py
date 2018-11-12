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
    l,r = leng-1,leng-1
    m = l+r+1
    left = np.concatenate([left,np.zeros((leng,1))])
    while(r>=0):
        if(l>=0 and left[l]>right[r]):
            left[m] = left[l]
            l -= 1
        else:
            left[m] = right[r]
            r -= 1
        m -= 1

    return left

nummern = mergesort(nummern)

print('\nAfter sorting')
print(nummern[added:])