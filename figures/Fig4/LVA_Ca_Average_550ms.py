import numpy as np
import matplotlib.pyplot as plt
firstcommonname ="./outputs/I=0EH-0.32Last="
lastcommonname ="_LTS.txt"
start_time = 1000
end_time = 1550

for i in range(2):
	print (lastcommonname)
	k=250*i
	filename=firstcommonname+str(k)+lastcommonname
	Array=np.genfromtxt(filename,delimiter="\t",dtype=("f8"),skip_header=start_time*40+2,skip_footer=40*(2000-end_time),usecols=(0,3,5,6,7))
	fig=plt.figure(facecolor="white")
	Time=Array[:,0]-start_time
	CaAverage=np.average(Array[:,1])
	LVAAverage=np.average(Array[:,2])
	HVAAverage=np.average(Array[:,3])
	NMDARAverage=np.average(Array[:,4])
	print (Array[0,0])
	print (Array[-1,0])
	print (k)
	print ("Ca=",CaAverage,"\n","LVA=",LVAAverage,"\n","HVA=",HVAAverage,"\n","NMDAR=",NMDARAverage)
	plt.plot(Time,Array[:,1])
	#plt.title(species)
	#plt.xlabel("Time (ms)")

firstcommonname ="./outputs/I=0E0H-0.32Last=0"
filename=firstcommonname+lastcommonname
Array=np.genfromtxt(filename,delimiter="\t",dtype=("f8"),skip_header=start_time*40+2,skip_footer=40*(2000-end_time),usecols=(0,3,5,6,7))
fig=plt.figure(facecolor="white")
Time=Array[:,0]-start_time
CaAverage=np.average(Array[:,1])
LVAAverage=np.average(Array[:,2])
HVAAverage=np.average(Array[:,3])
NMDARAverage=np.average(Array[:,4])
print (Array[0,0])
print (Array[-1,0])
print ("Ca=",CaAverage,"\n","LVA=",LVAAverage,"\n","HVA=",HVAAverage,"\n","NMDAR=",NMDARAverage)
plt.plot(Time,Array[:,1])
	#plt.title(species)
	#plt.xlabel("Time (ms)")

firstcommonname ="./outputs/I=0EH-0.475Last="
lastcommonname ="_Reduced.txt"

for i in range(2):
	print (lastcommonname)
	k=250*i
	filename=firstcommonname+str(k)+lastcommonname
	Array=np.genfromtxt(filename,delimiter="\t",dtype=("f8"),skip_header=start_time*40+2,skip_footer=40*(2000-end_time),usecols=(0,3,5,6,7))
	fig=plt.figure(facecolor="white")
	Time=Array[:,0]-start_time
	CaAverage=np.average(Array[:,1])
	LVAAverage=np.average(Array[:,2])
	HVAAverage=np.average(Array[:,3])
	NMDARAverage=np.average(Array[:,4])
	print (Array[0,0])
	print (Array[-1,0])
	print ("Hyperpolarisation=",k)
	print ("Ca=",CaAverage,"\n","LVA=",LVAAverage,"\n","HVA=",HVAAverage,"\n","NMDAR=",NMDARAverage)
	plt.plot(Time,Array[:,1])
	#plt.title(species)
	#plt.xlabel("Time (ms)")

firstcommonname ="./outputs/I=0E0H-0.475Last=0"
filename=firstcommonname+lastcommonname
Array=np.genfromtxt(filename,delimiter="\t",dtype=("f8"),skip_header=start_time*40+2,skip_footer=40*(2000-end_time),usecols=(0,3,5,6,7))
fig=plt.figure(facecolor="white")
Time=Array[:,0]-start_time
CaAverage=np.average(Array[:,1])
LVAAverage=np.average(Array[:,2])
HVAAverage=np.average(Array[:,3])
NMDARAverage=np.average(Array[:,4])
print (Array[0,0])
print (Array[-1,0])	
print ("Ca=",CaAverage,"\n","LVA=",LVAAverage,"\n","HVA=",HVAAverage,"\n","NMDAR=",NMDARAverage)
plt.plot(Time,Array[:,1])
	#plt.title(species)
	#plt.xlabel("Time (ms)")


def main():
	

	plt.show()



main()