TITLE N conductances driven by regularly-distributed spikes

COMMENT
A synaptic current with due to N alpha conductances due to
regularly-distributed spike trains with independent random phases.
BPG 12-6-06
ENDCOMMENT

DEFINE SSIZE 201
					       
NEURON {
	POINT_PROCESS gNReg
	RANGE gtot, gmax, gsum, e, N, freq, tau, rseed, async, i
	NONSPECIFIC_CURRENT i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	dt (ms)
    	rseed = 0   	: random number seed
    	async=0		: set to 1 if random phases required
	gmax=0 	(uS)	<0,1e9>
	e=0	(mV)
	N=1		: number of synapses
	freq=10	(/s)	: mean frequency of spikes per synapse
	tau=3	(ms)	: synaptic alpha time constant
}

ASSIGNED { 
	v (mV) 
	i (nA)
	isi (ms)	: interspike interval
	ts[SSIZE] (ms)	: start time per synapse
	tprev[SSIZE] (ms)	: time of previous spike
	gtot	(uS)
	gsum	(uS)
	g[SSIZE] (uS)
	z[SSIZE] (uS)
	fdt (1)
	fac (1)
}

INITIAL {
    	set_seed(rseed)
	isi = 1000/freq
    	gtot = 0
    	gsum = 0
    	FROM i = 0 TO SSIZE-1 {
      		g[i] = 0
      		z[i] = 0
      		if (async == 0) {
      			ts[i] = 0
      			tprev[i] = 0
      		} else {
      			ts[i] = isi*unirand()
      			tprev[i] = ts[i]
      		}
    	}
	fdt = exp(-dt/tau)
	fac=tau*(1-fdt)
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
  		if (t >= tprev[i]+isi) { 
  			spike = 1
  			tprev[i] = t
  		}
  		g[i] = (g[i]*fdt) + (z[i]*fac)
  		z[i] = (z[i]*fdt) + (fac/dt)*spike
  		gsum = gsum + g[i]
  	}
	gsum = gsum*(exp(1)/tau)	: normalise each synaptic conductance

}


FUNCTION unirand() {    : uniform random numbers between 0 and 1
        return(scop_random())
}
