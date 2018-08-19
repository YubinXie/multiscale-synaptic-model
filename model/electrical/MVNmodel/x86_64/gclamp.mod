COMMENT
an synaptic current with conductance played from a vector
of stored values into "g" (set up in hoc file)
BPG 11-4-06
ENDCOMMENT
					       
NEURON {
	POINT_PROCESS gclamp
	RANGE onset, g, gmax, e, i
	NONSPECIFIC_CURRENT i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	onset=0 (ms)
	g=0	(uS)	<0,1e9>
	gmax=0 	(uS)	<0,1e9>
	e=0	(mV)
}

ASSIGNED { v (mV) i (nA) }

BREAKPOINT {
	i = gmax*g*(v - e)
}
