://=============================================================================
://  ggSBA  -  fluctuating conductance model for synaptic bombardment
://	       (no check for negative conductances; better random 
://	       number generator)
://=============================================================================
://
://  THEORY:
://    Synaptic bombardment is represented by a stochastic model containing
://    two fluctuating conductances g_e(t) and g_i(t) descibed by:
://
://      Isyn = g_e(t) * [V - E_e] + g_i(t) * [V - E_i]
://      d g_e / dt = -(g_e - g_e0) / tau_e + sqrt(D_e) * Ft
://      d g_i / dt = -(g_i - g_i0) / tau_i + sqrt(D_i) * Ft
://
://    where E_e, E_i are the reversal potentials, g_e0, g_i0 are the average
://    conductances, tau_e, tau_i are time constants, D_e, D_i are noise
://    diffusion coefficients and Ft is a gaussian white noise of unit
://    standard deviation.
://
://    g_e and g_i are described by an Ornstein-Uhlenbeck (OU) stochastic
://    process where tau_e and tau_i represent the "correlation" (if tau_e
://    and tau_i are zero, g_e and g_i are white noise). The estimation
://    of OU parameters can be made from the power spectrum:
://
://      S(w) =  2 * D * tau^2 / (1 + w^2 * tau^2)
://
://    and the diffusion coeffient D is estimated from the variance:
://
://      D = 2 * sigma^2 / tau
://
://  NUMERICAL RESOLUTION:
://    The numerical scheme for integration of OU processes takes advantage
://    of the fact that these processes are gaussian, which led to an exact
://    update rule independent of the time step dt (see Gillespie DT,
://    Am J Phys 64: 225, 1996):
://
://      x(t+dt) = x(t) * exp(-dt/tau) + A * N(0,1)
://
://    where A = sqrt( D*tau/2 * (1-exp(-2*dt/tau)) ) and N(0,1) is a normal
://    random number (avg=0, sigma=1)
://
://  REMARKS:
://     - mechanism is implemented as a nonspecific current defined
://       as a point process.
://     - conductance cannot be negative!
://
://  PARAMETERS:
://    The mechanism takes the following parameters:
://
://    E_e = 0  (mV)            : reversal potential of excitatory conductance
://    E_i = -75 (mV)           : reversal potential of inhibitory conductance
://
://    g_e0 = 0.0121 (umho)     : average excitatory conductance
://    g_i0 = 0.0573 (umho)     : average inhibitory conductance
://
://    std_e = 0.0030 (umho)    : standard dev of excitatory conductance
://    std_i = 0.0066 (umho)    : standard dev of inhibitory conductance
://
://    tau_e = 2.728 (ms)       : time constant of excitatory conductance
://    tau_i = 10.49 (ms)       : time constant of inhibitory conductance
://
://-----------------------------------------------------------------------------
://
://  IMPROVED RANDOM NUMBER GENERATOR:
://    source: Numerical Recipes in C
://            gasdev() random generator for normal distributed random numbers
://
://-----------------------------------------------------------------------------
://
://  IMPLEMENTATION: A. Destexhe, Laval University, 1999
://
://  MODIFICATIONS: Michael Rudolph, UNIC/CNRS Paris, March 2003
://		    (implementation of improved random number generator)
://
://=============================================================================

INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
  POINT_PROCESS ggSBA
  RANGE g_e, g_i, E_e, E_i, g_e0, g_i0, g_e1, g_i1
  RANGE std_e, std_i, tau_e, tau_i, D_e, D_i
  RANGE new_seed
  NONSPECIFIC_CURRENT i
}

UNITS {
  (nA) = (nanoamp)
  (mV) = (millivolt)
  (umho) = (micromho)
}

PARAMETER {
  dt (ms)

  E_e= 0 (mV)           :// reversal potential of excitatory conductance
  E_i= -75 (mV)         :// reversal potential of inhibitory conductance

  g_e0= 0.0121 (umho)   :// average excitatory conductance
  g_i0= 0.0573 (umho)   :// average inhibitory conductance

  std_e= 0.0030 (umho)  :// standard dev of excitatory conductance
  std_i= 0.0066 (umho)  :// standard dev of inhibitory conductance

  tau_e= 2.728 (ms)     :// time constant of excitatory conductance
  tau_i= 10.49 (ms)     :// time constant of inhibitory conductance
}

ASSIGNED {
  v (mV)                :// membrane voltage
  i (nA)                :// fluctuating current
  g_e (umho)            :// total excitatory conductance
  g_i (umho)            :// total inhibitory conductance
  g_e1 (umho)           :// fluctuating excitatory conductance
  g_i1 (umho)           :// fluctuating inhibitory conductance
  D_e (umho umho /ms)   :// excitatory diffusion coefficient
  D_i (umho umho /ms)   :// inhibitory diffusion coefficient
  exp_e
  exp_i
  amp_e (umho)
  amp_i (umho)
}

INITIAL {
  g_e1 = 0
  g_i1 = 0
  if(tau_e != 0) {
    D_e = 2 * std_e * std_e / tau_e
    exp_e = exp(-dt/tau_e)
    amp_e = std_e * sqrt( (1-exp(-2*dt/tau_e)) )
  }
  if(tau_i != 0) {
    D_i = 2 * std_i * std_i / tau_i
    exp_i = exp(-dt/tau_i)
    amp_i = std_i * sqrt( (1-exp(-2*dt/tau_i)) )
  }
}

BREAKPOINT {
  SOLVE oup
  
  g_e = g_e0 + g_e1
  g_i = g_i0 + g_i1
  
  :// test for negative conductances
  if (g_e < 0) { g_e = 0 }
  if (g_i < 0) { g_i = 0 }
  
  i = g_e * (v - E_e) + g_i * (v - E_i)
}

:// decleare gasdev() and ran1() functions for random generator
VERBATIM
  float gasdev();
  float ran1(long *idem);
ENDVERBATIM

PROCEDURE oup() {       :// use "Numerical Recipes in C" function gasdev()
  if(tau_e != 0) { 
    g_e1 =  exp_e * g_e1 + amp_e * gasdev() 
  } else {
    g_e1 = std_e * gasdev()
  }
  if(tau_i!=0) { 
    g_i1 =  exp_i * g_i1 + amp_i * gasdev() 
  } else {
    g_i1 = std_i * gasdev()
  }
}

PROCEDURE update() {            :// updates internal values
  if(tau_e != 0) {
    D_e = 2 * std_e * std_e / tau_e
    exp_e = exp(-dt/tau_e)
    amp_e = std_e * sqrt( (1-exp(-2*dt/tau_e)) )
  }
  if(tau_i != 0) {
    D_i = 2 * std_i * std_i / tau_i
    exp_i = exp(-dt/tau_i)
    amp_i = std_i * sqrt( (1-exp(-2*dt/tau_i)) )
  }
}

://=============================================================================
://  IMPROVED RANDOM NUMBER GENERATOR
://    source: Numerical Recipes in C
://=============================================================================

VERBATIM

#include <math.h> 

#define IA 16807 
#define IM 2147483647 
#define AM (1.0/IM) 
#define IQ 127773 
#define IR 2836 
#define NTAB 32 
#define NDIV (1+(IM-1)/NTAB) 
#define EPS 1.2e-7 
#define RNMX (1.0-EPS)

long idum;

//------------------------------------------------------------------------------
// Minimal" random number generator of Park and Miller with Bays-Durham 
// shuffle and added safeguards. Returns a uniform random deviate between 
// 0.0 and 1.0 (exclusive of the endpoint values). Call with idum a 
// negative integer to initialize; thereafter, do not alter idum between 
// successive deviates in a sequence. RNMX should approximate the largest 
// floating value that is less than 1.
//------------------------------------------------------------------------------
float ran1(long *idum) 
{
  int j; 
  long k; 
  static long iy=0; 
  static long iv[NTAB]; 
  float temp;
  
  if (*idum <= 0 || !iy) 
  {
    if (-(*idum) < 1) *idum=1; 
    else *idum = -(*idum);
  
    for (j=NTAB+7;j>=0;j--) 
    {
      k=(*idum)/IQ; 
      *idum=IA*(*idum-k*IQ)-IR*k; 
      if (*idum < 0) *idum += IM; 
      if (j < NTAB) iv[j] = *idum; 
    } 
    
    iy=iv[0]; 
  } 

  k=(*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if (*idum < 0) *idum += IM;
  j=iy/NDIV;
  iy=iv[j];
  iv[j] = *idum;
  
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp; 
}

//------------------------------------------------------------------------------
// Returns a normally distributed deviate with zero mean and 
// unit variance, using ran1(idum) as the source of uniform deviates. 
//------------------------------------------------------------------------------
float gasdev() 
{ 
  float ran1(long *idum); 
  static int iset=0; 
  static float gset; 
  float fac,rsq,v1,v2; 
  
  if (idum < 0) iset=0;
  
  if (iset == 0) 
  {
    do 
    {
      v1=2.0*ran1(&idum)-1.0;
      v2=2.0*ran1(&idum)-1.0;    
      rsq=v1*v1+v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    
    fac=sqrt(-2.0*log(rsq)/rsq);    
    // Now make the Box-Muller transformation to get two normal
    // deviates. Return one and save the other for next time. 
    gset=v1*fac; iset=1;
    return v2*fac;
  } 
  else 
  {
    iset=0;
    return gset;
  }
}
    
ENDVERBATIM
    
://=============================================================================

PROCEDURE new_seed(seed) {      :// procedure to set the seed
  VERBATIM
    idum = _lseed;
  ENDVERBATIM
}

://=============================================================================
