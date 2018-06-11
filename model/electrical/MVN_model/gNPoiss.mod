TITLE N conductances driven by Poisson-distributed spikes

COMMENT
A synaptic current from N alpha conductances due to independent
Poisson-distributed spike trains
BPG 22-5-06
ENDCOMMENT

DEFINE SSIZE 201
					       
NEURON {
	POINT_PROCESS gNPoiss
	RANGE gtot, gsum, gmax, e, N, freq, tau, rseed, i
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
	tau=3	(ms)	: synaptic alpha time constant
}

ASSIGNED { 
	v (mV) 
	i (nA)
	gsum (uS)
	gtot (uS)
	g[SSIZE] (uS)
	z[SSIZE] (uS)
	fdt (1)
	fac (1)
	sp (1)
}

INITIAL {
    	gtot = 0
    	gsum = 0
    	FROM i = 0 TO SSIZE-1 {
      		g[i] = 0
      		z[i] = 0
    	}
	fdt = exp(-dt/tau)
	fac=tau*(1-fdt)
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
  		g[i] = (g[i]*fdt) + (z[i]*fac)
  		z[i] = (z[i]*fdt) + (fac/dt)*spike
  		gsum = gsum + g[i]
  	}
	gsum = gsum*(exp(1)/tau)	: normalise each synaptic conductance

}


FUNCTION unirand() {    : uniform random numbers between 0 and 1
        return(scop_random())
}
