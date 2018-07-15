I. Components
1. run_Normal.hoc
NEURON file to reproduce the results. Hyperpolarisation and excited stimulation happens in 1000 s.

2.I=0EH-0.475Last=0_Normal.txt, I=0EH-0.475Last=250_Normal.txt
Raw data. Recorded the dendB[3].v(0.5)	dendB[11].v(0.5)	dendB[3].cai(0.5)	dendB[11].cai	dend[3].lva	dend[3].hva	dend[3].nmda.


3.Nromal_EG0.pzfx, Normal_EH0.475Last=250.pzfx
Prism files that take the data of Membrane potential Ca concentration and LVACC, HVACC, NMDAR Ca current in dend[3](proximal dendrites) from raw data (500s - 2000s)

3.Average_Ca.pzfx
Prism file for average Ca.

4. Normal_EH_Ca.pdf， Normal_EH_MembranePotential.pdf， Normal_Eonly_MembranePotential.pdf， Normal_Eonly_Ca.pdf，RelativeCaNormalH0.pdf
PDF version of the result.

5. Normal_Ca_Average.py
Python script to calculate the average Ca starting from 1000s to 1550s (total 550).

II. Note
1. You can directly run run_Normal.hoc in NEURON-LINUX or MAC folder.