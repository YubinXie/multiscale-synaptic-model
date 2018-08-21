
# Figure 8-10

## Figure
![alt text](./outputs/Fig-8.pdf)
![alt text](./outputs/Fig-9.pdf)
![alt text](./outputs/Fig-10.pdf)



## Components

- **\*\*.hoc**
	- NEURON protocol scripts to generate NEURON simulation results.
	- run\_Normal\_scanAmp\_Jan.hoc is for Figure 8
	- run\_Normal\_scanDur\_H\_Jan.hoc is for Figure 9
	- run\_Normal\_scanTim\_Jan.hoc is for Figure 10
- **SetupFolders.py**
	- run the script on the local machine in the directory containing NEURON input files and 
	the intial COPASI model， the script loops through both the COPASI model and NEURON input files generating new models in seperate folders
	- SetupFolders_strength_duration.py is for strength and duration, where the unit stimulation windows is 1000 ms. 
	- SetupFolders_timing.py is for timing simulation, where the unit stimulation time windows is 1500 ms.

-  **allruns.sh**  
	- The script automatically submits all the COPASI models to the queue on the  computer cluster 
	- Run the script in the directory containing folders with the COPASI models

- **\*\*\_extract_batch_info.py**
	- To visulize the results from the batch COPASI runs.

- **command_generator.py \*\*\_commands.txt**
	- command_generator.py generates \*\*\_commands.txt, which include the COPASI file to be run.

- **threading.sh**
	- Bash script to run multi COPASI file in parallel. Change the command file name in line 18 to decide which \*\*\_commands.txt to run.




## Instruction 
	- Copy the NEURON protocol script into the NEURON folder (model/electrical/MVNmodel)
	- Run the NEURON protocol script to generate corresponding NEURON output that recording membrane potential and calcium concentration in MVN neurons.
	- Copy the initial COPASI model () into the result folder of from previous NEURON model, which is in biochemistry equilibrium under normal firing MVN B neurons condition.
	- Copy the SetupFolders.py to the previous dolder and run the scritp (`python SetupFolders.py `) to generate new COPASI file with controled calcium concentration from NEURON output.
	- Run allruns.sh (if in cluster) or run command_generator.py and hreading.sh (if in a multi-core computer) to run all the COPASI model and outputs will be automatically recorded.
	- Run \*\*_extract_batch_info to plot the recorded biochemistry dynamics under certain electrial simulation.