import os

pwd = os.getcwd() 
filenames = os.listdir(pwd)
train,val=[],[]

# Split Dataset into ratio 99:1
for i in range(len(filenames)):
    if i%100==0 and i!=0:
        if filenames[i][-1]!='y' and filenames[i][-1]!='t': # Do not copy python file or txt file
            val.append(filenames[i])
    else:
        if filenames[i][-1]!='y' and filenames[i][-1]!='t': # Do not copy python file or txt file
            train.append(filenames[i])

# Write Train set
with open('train.txt', 'w') as f:
    for item in train:
        f.write("%s\n" % item)

# Write Validation set
with open('val.txt', 'w') as f:
    for item in val:
        f.write("%s\n" % item)

print('train.txt and val.txt have been created successfully')
