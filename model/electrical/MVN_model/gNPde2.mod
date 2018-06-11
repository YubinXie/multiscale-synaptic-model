TITLE N conductances driven by Poisson-distributed spikes

COMMENT
A synaptic current with due to N dual exponential conductances due to independent
Poisson-distributed spike trains
Alternative implementation to match MRCI method.
NOTE: effect of a spike is dependent on the time step, since a spike has amplitude
of 1 and lasts for one dt (scaling amplitude by dt to give a spike area of 1,
independent of dt, seems to introduce numerical problems).
BPG 31-10-06
ENDCOMMENT

DEFINE SSIZE 201
					       
NEURON {
	POINT_PROCESS gNPde2
	RANGE gtot, gmax, spt, e, N, freq, tau1, tau2, rseed, i, tpeak, gpeak
	NONSPECIFIC_CURRENT i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	dt (ms)
    	rseed = 0   : random number seed
	gmax=0 	(uS)	<0,1e9>
	e=0	(mV)
	N=100		: number of synapses
	freq=100	: mean frequency of spikes per synapse
	tau1=2	(ms)	: synaptic slow time constant
	tau2=0.2	(ms)	: synaptic fast time constant
}

ASSIGNED { 
	v (mV) 
	i (nA)
	gtot (uS)
	tpeak (ms)
	gpeak (1)
	fac (ms)
	sp (1)
	spt (uS/ms^2)
}

STATE {
	g (uS)
	z (uS/ms)
}

INITIAL {
    	gtot = 0
      	g = 0
      	z = 0
      	spt = 0
    	fac=tau1*tau2/(tau1-tau2)
    	tpeak=fac*log(tau1/tau2)
    	gpeak=fac*(exp(-tpeak/tau1)-exp(-tpeak/tau2))
	sp = (freq*dt)/1000	: spike probability per time step
    	set_seed(rseed)
}

BREAKPOINT {
	SOLVE conductances METHOD cnexp
	gtot = gmax*g/gpeak
	i = gtot*(v - e)
}

DERIVATIVE conductances { : synaptic conductances
        spikes(N, freq)
  	z' = -(z/tau1) + spt
  	g' = -(g/tau2) + z
}

FUNCTION unirand() {    : uniform random numbers between 0 and 1
VERBATIM
        return(scop_random());
ENDVERBATIM
}

FUNCTION spikes(N (1), freq (Hz)) {
  LOCAL i, sumsp
  
  sumsp=0
  FROM i=0 TO N-1 {
    if (freq*dt/1000 >= unirand()) { sumsp=sumsp+1 }
  }
  spt=sumsp
}
