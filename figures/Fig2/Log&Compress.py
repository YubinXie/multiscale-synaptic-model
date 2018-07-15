import numpy as np
import matplotlib.pyplot as plt
import math

#print np.logspace(-11,-6,101)
#a=np.logspace(-11,-6,101)
#a=str(a)
#open("abc.txt","w").write(a)

lists=[]
expression=""

# file name #
input_file="7.14E-9-800S-0.0001s.txtcompress.txt"

a=open(input_file,"r").readline()
print a
Array=np.genfromtxt(input_file,delimiter="\t",dtype=("f8"),skip_header=2,usecols=(0,143,171))
print len(Array)
for i in range (len(Array)):
	if i%1000==0:
		lists.append(Array[i,:].tolist())
		expression=expression+str(Array[i,0])+"\t"+str(Array[i,1])+"\t"+str(Array[i,2])+"\t"+str(Array[i,3])+"\n"
#print lists

#arraylists=np.array(lists)
open(input_file+"compress.txt","w").write(expression)
print "finished"