# Quadroni and Knopfel MVN Neuron Models

--------------------------------------
## Pre-requirement 

Software: NEURON 
Link: https://www.neuron.yale.edu/neuron
Note: Running of NEURON requires some 

--------------------------------------

## How to run:
** First comiple the model and then run the specific protocol file (xxx.hoc) **

mswin: double click on the xxx.hoc file to run a certain protocol after compiling the mod files with mknrndll

unix: type "nrnivmodl" and enter and then "nrngui xxx.hoc" in the expanded archive folder to run a certain protocol.

mac: after the archive is unziped drag and drop the newly created mvns folder onto the mknrndll 
     icon. Then drag and drop the xxx.hoc in the mvns folder onto the nrngui icon to run a certain protocol.

Offical DOCUMENTATION: https://www.neuron.yale.edu/neuron/faq/general-questions

-----------------------------------------
## Implementation history:

### Reimplemented from ModelDB code (BPG 14-4-06)
  - cells now constructed explicitly in HOC files mvnA.hoc and mvnB.hoc
    (replaces session files that construct CellBuilders)

Extras:
  - gclamp.mod: synaptic current in which conductance "g" is replayed from a stored vector
                (set up from hoc - see load_gtrain.hoc and run_mvnBgtr.hoc)
  - ggSBA.mod: fluctuating conductance model for synaptic bombardment
  	       (Destexhe and Rudolph - code from Obidos Example 5)
  	       example of use in run_mvnBou.hoc

------------------------------------------------------------------------------------------
### Original README from ModelDB implementation
------------------------------------------------------------------------------------------
Readme for a model from the Quadroni and Knopfel 1994 paper:

Quadroni R, Knopfel T.
Compartmental models of type A and type B guinea pig medial vestibular neurons.
J Neurophysiol. 1994 Oct;72(4):1911-24.

    Institut fur Theoretische Physik, ETH-Honggerberg, Zurich, Switzerland.

Abstract:

1. We have developed compartmental models of guinea-pig medial vestibular nuclei neurons
(MVNns). The structure and the parameters of the model cells were chosen to reproduce the
responses of type A and type B MVNns as described in electrophysiological recordings. 
2. Dynamics of membrane potentials were modeled in 46 and 61 branched electrical compartments 
for Type A and Type B MVNns, respectively. Each compartment was allowed to contain up to nine 
active ionic conductances: a fast inactivating sodium conductance, gNa, a persistent sodium 
conductance, gNap, a low-voltage activated calcium conductance, gCa(LVA), a high-voltage
activated calcium conductance, gCa(HVA), a fast-voltage activated potassium conductance, 
gK(fast), a slowly relaxing voltage activated potassium conductance, gK(slow), a fast transient 
potassium channel, gK(A), a slowly relaxing mixed sodium-potassium conductance activating at 
hyperpolarized membrane potentials, gH, and a calcium-activated potassium conductance gK(AHP). 
The kinetics of these conductances were derived from voltage-clamp studies in a variety of 
preparations. Kinetic parameters as well as distribution and density of ion channels were
adjusted to yield the reported electrophysiological behavior of medial vestibular neurons. 
3. Dynamics of intracellular free [Ca2]i were modeled by inclusion of a Ca(2+)-pump and a 
Na(+)-Ca2+ exchanger for extrusion of calcium. Diffusion of calcium between submembraneous sites 
and the center of an electrical compartment was modeled by 25 and 6 shell-like chemical 
compartments for the cell body and the proximal dendrites, respectively. These compartments also 
contained binding sites for calcium. 4. The dynamics of active conductances were the same in
both models except for gK(fast). This was necessary to achieve the different shape of spikes and 
of spike afterhyperpolarization in type A and type B MVNns. An intermediate depolarizing 
component of the spike afterhyperpolarization of type B neurons in part depended on their 
dendritic cable structure. 5. Variation of the low threshold calcium conductance, gCa(LVA), 
shows that the ability to generate low-threshold spike bursts critically depends on the density 
of this conductance. Sodium plateaus were generated when increasing the density of gNap. 
6. The type B model cell generated rhythmic bursts of spiking activity under simulation of two 
distinct experimental conditions.(ABSTRACT TRUNCATED AT 400 WORDS)

-----------------------------------------

