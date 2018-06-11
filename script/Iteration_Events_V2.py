## Python 2
## Created by Yubin Xie @ 6.26 2017 for the multiscale modelling paper
## Modified by Yubin Xie @ 12.13 2017 with the following features:
#### 1) The output COPASI file name is now the sum of previous COPASI file and the input data filename
#### 2) The iteration loop is set to be fraction instead of int.. The previous scripts requires the duration time to be x * 1000. Now, it can be any number. 
import numpy as np
import matplotlib.pyplot as plt
import sys, optparse
import re

usage = "python Iterration_Normal_Events_LTP.py -i Income_data_file_from_NEURON.txt  -c COPASI_File.cps -t Target_Species_Name(Ca) -n Col_Number_of_Target_Species(3) -s  StartTime(750) -r Electrical_Resolution(0.025) -d Duration(1000) -x ScalingFactor(50) -y Chemical_Resolution(1)"
parser = optparse.OptionParser(usage)

parser.add_option("-i", "--INPUT", dest="InputFile",
                 	help="Input file from Neuron that recording [Ca] or other information", metavar="FILE")
parser.add_option("-c", "--COPASI", dest="CopasiFile",
					help="COPASI file that performing chemical simulation", metavar="FILE")
parser.add_option("-t", "--Target", dest="TargetSpecies", type="string",
					help="Target Species whose concnetration that you want to control. Default=Ca", default="Ca"),
parser.add_option("-n", "--ColNumber", dest="ColNumber", default=3,
					metavar="NUMBER", type="int", help="The col of your target information in the inputfile. Default=3")
parser.add_option("-s", "--StartTime", dest="StartTime", default=750,
					metavar="NUMBER", type="int", help="Your start time in the inputfile. Unit as millisecond). Default=750")
parser.add_option("-r", "--Resolution", dest="Resolution", default=0.025,
					metavar="NUMBER", type="float", help="The resolution of NEURON output file (Unit is millisecond). Default=0.025")
parser.add_option("-d", "--Duration", dest="Duration",default=1000,
					metavar="NUMBER", type="int", help="The duration after your start time in the inputfile. Unit as millisecond. Default=1000)")
parser.add_option("-x", "--Scaling", dest="Scaling", default=50,
					metavar="NUMBER", type="int", help="The scaling number that convert electrical concentration to chemical concentration. Default=50")
parser.add_option("-y", "--ChemicalResolution", dest="ChemicalResolution", default=1,
					metavar="NUMBER", type="float", help="The resolution of COPASI file (Unit is millisecond). Default=1")

(options, args) = parser.parse_args()
InputFile=options.InputFile
CopasiFile=options.CopasiFile
TargetSpecies=options.TargetSpecies
ColNumber=options.ColNumber
StartTime=options.StartTime
Scaling=options.Scaling
Resolution=options.Resolution
Duration=options.Duration
ChemicalResolution=options.ChemicalResolution
Iteration="Iteration"


SkipHeader=int(1/Resolution*StartTime+2)
InputRow=int(1/Resolution*Duration)
#Input the file
Array=np.genfromtxt(InputFile,delimiter="\t",dtype=("f8"),skip_header=SkipHeader,max_rows=InputRow*2,usecols=(0,ColNumber))
#Reset the start time as 0
Array[:,0]=(Array[:,0]-StartTime)/1000
# Change the unit from mmol to mol 
Array[:,1:] = Array[:,1:]/1000
print (Array[:,0])
#Scaling
Array[:,1]=Array[:,1]/50

expression="    <ListOfEvents>\n"
linenumber=0
repeat_number=0
print ("Running...The duration is ", Duration, "ms")

interval=int(ChemicalResolution/Resolution)
print (interval)

#Get the target species and iteration ID
with open(CopasiFile,"r") as OpenCOPASI :
	for line in OpenCOPASI: 
		line2=re.search('key="Metabolite_(?P<h1>.+?)" name="'+TargetSpecies+'"',line)
		if(line2):
			SpeciesID=line2.group("h1")
			print ("SpeciesID of ",TargetSpecies,"is ",SpeciesID)
		line3=re.search('<ModelValue key="ModelValue_(?P<h2>.+?)" name="'+Iteration+'"',line)
		if(line3):
			IterationID=line3.group("h2")
			print ("SpeciesID of ",Iteration,"is ",IterationID)


#Convert the target species concentration from  high resolution to chemical resolution
ChemicalArray=[]
SpeciesID=int(SpeciesID)
for i in range(int(InputRow)):
	if (i%interval==0 and i>0):

		Ca_average=np.average(Array[i-interval+1:i,1])
		ChemicalArray.append([Array[i,0],Ca_average])
		linenumber=linenumber+1

New_Array=np.array(ChemicalArray)

#Plot the target time duration
def plot():
	print ("plotting")
	global New_Array
	plt.figure()
	plt.plot(New_Array[:,0],New_Array[:,1])
	plt.show()
plot()

Array=New_Array


#Generate events in COPASI language
for i in range(len(Array)-1):
	expression=expression+"      <Event key=\"Event_"+str(i)+"\" name=\"Event_"+str(i)+"\" fireAtInitialTime=\"0\" persistentTrigger=\"0\">\n"
	expression=expression+"        <TriggerExpression>\n          &lt;CN=Root,Model=Ca mediated Syanptic Plasticity,Reference=Time&gt; == "+str(Array[i,0])+ "+&lt;CN=Root,Model=Ca mediated Syanptic Plasticity,Vector=Values["+Iteration+"],Reference=Value&gt;\n        </TriggerExpression>\n"
	expression=expression+"        <ListOfAssignments>\n"
	expression=expression+"          <Assignment targetKey=\"Metabolite_"+str(SpeciesID)+"\">\n"
	expression=expression+"            <Expression>\n            " +str(Array[i,1])+"\n            </Expression>\n          </Assignment>\n"
	expression=expression+"        </ListOfAssignments>\n      </Event>\n"
	linenumber=linenumber+1
i=i+1
expression=expression+"      <Event key=\"Event_"+str(i)+"\" name=\"Event_"+str(i)+"\" fireAtInitialTime=\"0\" persistentTrigger=\"0\">\n"
expression=expression+"        <TriggerExpression>\n          &lt;CN=Root,Model=Ca mediated Syanptic Plasticity,Reference=Time&gt; == "+str(Array[i,0])+ "+&lt;CN=Root,Model=Ca mediated Syanptic Plasticity,Vector=Values["+Iteration+"],Reference=Value&gt;\n        </TriggerExpression>\n"
expression=expression+"        <ListOfAssignments>\n"
expression=expression+"          <Assignment targetKey=\"Metabolite_"+str(SpeciesID)+"\">\n"
expression=expression+"            <Expression>\n            " +str(Array[i,1])+"\n            </Expression>\n          </Assignment>\n"
expression=expression+"       <Assignment targetKey=\"ModelValue_"+IterationID+"\">\n"
expression=expression+"            <Expression>\n              &lt;CN=Root,Model=Ca mediated Syanptic Plasticity,Vector=Values["+Iteration+"],Reference=Value&gt;+"+str(Duration/1000.0)+ "\n            </Expression>\n          </Assignment>\n  "
expression=expression+"        </ListOfAssignments>\n      </Event>\n"
expression=expression+"    </ListOfEvents>\n"
#output.write(expression)

#Generate new COPASI file with new events
with open(CopasiFile,"r") as OpenCOPASI, open(CopasiFile.replace(".cps",'_' +InputFile+"s.cps"), "w") as OpenUpdatedCOPASI:
	for line in OpenCOPASI: 
		line2=re.search('</ListOfReactions(?P<h1>.+?)',line)
		if not line2:
			OpenUpdatedCOPASI.writelines(line)
		if line2:
			OpenUpdatedCOPASI.writelines(line)
			OpenUpdatedCOPASI.writelines(expression)
print ("done")



