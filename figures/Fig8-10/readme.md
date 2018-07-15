
# Figure 7-9

## Content 

### **.hoc
	- NEURON protocol scripts to generate NEURON simulation results.
	- xx is for Figure 7
	- xx is for Figure 8
	- xx is for Figure 9

### SetupFolders.py
	- run the script on the local machine in the directory containing NEURON input files and 
	the intial COPASI model 
	-the script loops through both the COPASI model and NEURON input files generating new models 
	in seperate folders

### allruns.sh  
	- The script automatically submits all the COPASI models to the queue on the computer cluster 
	- Run the script in the directory containing folders with the COPASI models

### Graphs.py 
	- After downloading the results into the local machine, the script visualises the results 
	- line 11: inputPath='Data directory path.../Strength/*.csv' - select the path were the results are stored 
	- line 17: insert the first part of the file name before the viarble
	- line 19: insert the second part of the file name after the viarble
	- line 20 and 21 - choose appropriate units 
	- lines 32-39 - select these lines creating the graphs for the timing experiment 
	- lines 28-30 - use these lines for the strength and duration experiments
	- line 61: Choose the appropriate set of data to plot 
	- line 72: choose Y axis title 
	- line 73: choose graph title 
	- line 76: choose a graph name and a format

## Procedure 
	- Copy the NEURON protocol script into the NEURON folder (model/electrical/MVNmodel)
	- Run the NEURON protocol script to generate corresponding NEURON output that recording membrane potential and calcium concentration in MVN neurons.
	- Copy the initial COPASI model () into xxx, which is in biochemistry equilibrium under normal firing MVN B neurons condition.
	- Copy the SetupFolders.py to xxx and run the scritp to generate new COPASI file with controled calcium concentration from NEURON output.
	- Copy SetupFolders.py to xx and Run allruns.sh to run all the COPASI model and outputs will be automatically recorded.
	- Run Graphs.py to plot the recorded biochemistry dynamics under certain electrial simulation.