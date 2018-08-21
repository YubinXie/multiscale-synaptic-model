
# Multiscale-Synaptic-Model Figure 3

## Components

1. **run_Normal.hoc**<br/>
	NEURON file to reproduce the results. Hyperpolarisation and excited stimulation happens in 1000 s.

2. **outputs/I=0EH-0.475Last=0_Normal.txt, I=0EH-0.475Last=250_Normal.txt**<br/>
	Raw data. Recorded the dendB[3].v(0.5)	dendB[11].v(0.5)	dendB[3].cai(0.5)	dendB[11].cai	dend[3].lva	dend[3].hva	dend[3].nmda.

3. **Normal_Ca_Average.py**<br/>
	Python script to calculate the average Ca starting from 1000 ms to 1550 ms (total 550 ms) and from 750 ms to 1750 ms (total 1000 ms).

## Instruction

1. You can copy, paste and run run_Normal.hoc in NEURON software directory.

2. To run Normal_Ca_Average.py, ``python Normal_Ca_Average.py``

## Results
![alt text](./outputs/Fig-3.pdf)