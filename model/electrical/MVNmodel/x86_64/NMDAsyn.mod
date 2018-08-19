COMMENT
Two state kinetic scheme synapse described by rise time tau1,
and decay time constant tau2. The normalized peak condunductance is 1.
Decay time MUST be greater than rise time.

The solution of A->G->bath with rate constants 1/tau1 and 1/tau2 is
 A = a*exp(-t/tau1) and
 G = a*tau2/(tau2-tau1)*(-exp(-t/tau1) + exp(-t/tau2))
	where tau1 < tau2

If tau2-tau1 -> 0 then we have a alphasynapse.
and if tau1 -> 0 then we have just single exponential decay.

The factor is evaluated in the
initial block such that an event of weight 1 generates a
peak conductance of 1.

Because the solution is a sum of exponentials, the
coupled equations can be solved as a pair of independent equations
by the more efficient cnexp method.

**************************************************************************
BPG 14-8-07
Modified from Exp2Syn to give NMDA-type synapse producing a calcium current.
I-V relationship as measured in DCN neurons by Anchisi et al, 
J. Neurophysiol. 85:323-331, 2001.
Note that only fast decay component measured by Anchisi is used (no slow.)
GHK equation for calcium current not used (ok for experiments when neuron
is largely near resting potential.)
**************************************************************************
ENDCOMMENT

NEURON {
	POINT_PROCESS NMDAsyn
	RANGE tau1, tau2, e, i
	: NONSPECIFIC_CURRENT i
	USEION ca WRITE  ica

	RANGE g
	GLOBAL total
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
	FARADAY = (faraday) (kilocoulombs)
	R = (k-mole) (joule/degC)
}

PARAMETER {
	tau1=12.5 (ms) <1e-9,1e9>
	tau2 = 20 (ms) <1e-9,1e9>	: fast component at -60mV
	e=-0.5	(mV)
    	a=5.3 (mM)
    	Mg=1 (mM)
    	delta=0.69 (1)
}

ASSIGNED {
	v (mV)
	ica (nA)
	i (nA)
	g (uS)
	factor
	total (uS)
	gamma (/mV)	: (delta*z*F)/(R*T)
	celsius (degC)	: set to room temp (22-26 degC) in HOC
}

STATE {
	A (uS)
	B (uS)
}

INITIAL {
	LOCAL tp
	total = 0
	if (tau1/tau2 > .9999) {
		tau1 = .9999*tau2
	}
	A = 0
	B = 0
	tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
	factor = -exp(-tp/tau1) + exp(-tp/tau2)
	factor = 1/factor
	gamma = (delta*2*FARADAY)/(R*(273.15+celsius))
}

BREAKPOINT {
	SOLVE state METHOD cnexp
	g = B - A
    	g = (g*a) / (a + (Mg*exp(-gamma*v)))
	i = g*(v - e)
	ica = i	: (will be added to all other Ca currents in a segment)
}

DERIVATIVE state {
	A' = -A/tau1
	B' = -B/tau2
}

NET_RECEIVE(weight (uS)) {
	state_discontinuity(A, A + weight*factor)
	state_discontinuity(B, B + weight*factor)
	total = total+weight
}
