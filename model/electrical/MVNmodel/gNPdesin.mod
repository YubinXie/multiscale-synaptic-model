TITLE N conductances driven by Poisson-distributed, sinusoidally-modulated spikes

COMMENT
A synaptic current with due to N dual exponential conductances due to independent
Poisson-distributed spike trains. Spike rates varied sinusoidally after a
specified delay.
BPG 2-8-06
ENDCOMMENT

DEFINE SSIZE 201
					       
NEURON {
	POINT_PROCESS gNPdesin
	RANGE gtot, gsum, gmax, e, N, meanfr, dfr, sinfr, sinph, tstart, tdur
	RANGE tau1, tau2, rseed, i
	NONSPECIFIC_CURRENT i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
	PI = (pi) (1)
}

PARAMETER {
	dt (ms)
    	rseed = 0   : random number seed
	gmax=0 	(uS)	<0,1e9>
	e=0	(mV)
	N=100		: number of synapses
	meanfr=100	: mean frequency of spikes per synapse
	dfr=20		: frequency modulation (+-mean)
	sinfr=2		: modulation frequency
	sinph=0		: modulation phase
	tstart=1000	: start of sinusoidal modulation
	tdur = 4000	: duration of modulation
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
	freq (Hz)
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
	sp = (meanfr*dt)/1000	: spike probability per time step
    	set_seed(rseed)
}

BREAKPOINT {
	SOLVE conductances
	gtot = gmax*gsum
	i = gtot*(v - e)
}


PROCEDURE conductances() { LOCAL i, spike  : synaptic conductances
	gsum = 0
	if (t >= tstart && t <= tstart+tdur) {
		freq = meanfr + dfr*sin((sinph*2*PI/360)+(sinfr*2*PI/1000)*t)
	} else {
		freq = meanfr
	}
	sp = (freq*dt)/1000	: spike probability per time step
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
