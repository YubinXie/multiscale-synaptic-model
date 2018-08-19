: PRESYN.MOD
: Presynaptic depression of release probability
: Stochastic emission of spikes for input to e.g. expsyn.mod
: Modified from intfire1.mod
: BPG 7-11-07

NEURON {
	ARTIFICIAL_CELL PreSyn
	RANGE tau, p, p0, rseed
	: p plays the role of release probability
	: weight w is the decrement in p per input spike
}

PARAMETER {
    	rseed = 0   : random number seed
	p0 = 0.5
	tau = 10 (ms)
}

ASSIGNED {
	p
	t0(ms)
}

INITIAL {
	p = p0
	t0 = t
}

NET_RECEIVE (w) {
	p = p + (p0-p)*(1-exp(-(t - t0)/tau))
	t0 = t
	if (scop_random() < p) {	: stochastic release
		p = p - w
		if (p < 0) { p = 0 }
		net_event(t)
	}
}
