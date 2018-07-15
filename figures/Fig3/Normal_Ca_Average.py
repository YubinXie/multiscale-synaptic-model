import numpy as np
import matplotlib.pyplot as plt
firstcommonname ="I=0EH-0.475Last="
lastcommonname ="_Normal.txt"

for i in range(2):
	k=250*i
	filename=firstcommonname+str(k)+lastcommonname
	Array=np.genfromtxt(filename,delimiter="\t",dtype=("f8"),skip_header=40002,skip_footer=138000,usecols=(0,3,5,6,7))
	fig=plt.figure(facecolor="white")
	Time=Array[:,0]-1000
	CaAverage=np.average(Array[:,1])
	LVAAverage=np.average(Array[:,2])
	HVAAverage=np.average(Array[:,3])
	NMDARAverage=np.average(Array[:,4])
	print Array[0,0]
	print Array[-1,0]
	print "Ca=",CaAverage,"\n","LVA=",LVAAverage,"\n","HVA=",HVAAverage,"\n","NMDAR=",NMDARAverage
	plt.plot(Time,Array[:,1])
	#plt.title(species)
	#plt.xlabel("Time (ms)")


def main():
	

	plt.show()



main()