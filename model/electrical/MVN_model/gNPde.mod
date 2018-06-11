TITLE N conductances driven by Poisson-distributed spikes

COMMENT
A synaptic current with due to N dual exponential conductances due to independent
Poisson-distributed spike trains
BPG 31-7-06
ENDCOMMENT

DEFINE SSIZE 201
					       
NEURON {
	POINT_PROCESS gNPde
	RANGE gtot, gsum, gmax, e, N, freq, tau1, tau2, rseed, i, gpeak, tpeak
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
	N=1		: number of synapses
	freq=10		: mean frequency of spikes per synapse
	tau1=3	(ms)	: synaptic slow time constant
	tau2=1	(ms)	: synaptic fast time constant
}

ASSIGNED { 
	v (mV) 
	i (nA)
	gsum (uS)
	gtot (uS)
	g[SSIZE] (uS)
	z[SSIZE] (uS)
	fdt1 (1)
	fac1 (1)
	fdt2 (1)
	fac2 (1)
	fac (1)
	tpeak (ms)
	gpeak (1)
	sp (1)
}

INITIAL {
    	gtot = 0
    	gsum = 0
    	FROM i = 0 TO SSIZE-1 {
      		g[i] = 0
      		z[i] = 0
    	}
	fdt1 = exp(-dt/tau1)
	fac1=tau1*(1-fdt1)
	fdt2 = exp(-dt/tau2)
	fac2=tau2*(1-fdt2)
    	fac=tau1*tau2/(tau1-tau2)
    	tpeak=fac*log(tau1/tau2)
    	gpeak=fac*(exp(-tpeak/tau1)-exp(-tpeak/tau2))
	sp = (freq*dt)/1000	: spike probability per time step
    	set_seed(rseed)
}

BREAKPOINT {
	SOLVE conductances
	gtot = gmax*gsum
	i = gtot*(v - e)
}


PROCEDURE conductances() { LOCAL i, spike  : synaptic conductances
	gsum = 0
  	FROM i=0 TO N-1 {
  		spike = 0
  		if (unirand() <= sp) { spike = 1 }
  		g[i] = (g[i]*fdt2) + (z[i]*fac2)
  		z[i] = (z[i]*fdt1) + (fac1/dt)*spike
  		gsum = gsum + g[i]
  	}
	gsum = gsum/gpeak	: normalise each synaptic conductance

}


FUNCTION unirand() {    : uniform random numbers between 0 and 1
        return(scop_random())
}
