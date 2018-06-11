/* Created by Language version: 7.5.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 static void _difusfunc(ldifusfunc2_t, _NrnThread*);
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__ca_prox
#define _nrn_initial _nrn_initial__ca_prox
#define nrn_cur _nrn_cur__ca_prox
#define _nrn_current _nrn_current__ca_prox
#define nrn_jacob _nrn_jacob__ca_prox
#define nrn_state _nrn_state__ca_prox
#define _net_receive _net_receive__ca_prox 
#define factors factors__ca_prox 
#define state state__ca_prox 
#define states states__ca_prox 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define B _p[0]
#define K2f_ex _p[1]
#define K2f_ATPase _p[2]
#define ca (_p + 3)
#define CaBuffer (_p + 8)
#define Buffer (_p + 13)
#define n _p[18]
#define ica _p[19]
#define i_Na_Ca_ex _p[20]
#define i_ATPase _p[21]
#define cai _p[22]
#define Kd _p[23]
#define B0 _p[24]
#define Dca (_p + 25)
#define DCaBuffer (_p + 30)
#define DBuffer (_p + 35)
#define Dn _p[40]
#define _g _p[41]
#define _ion_cai	*_ppvar[0]._pval
#define _ion_ica	*_ppvar[1]._pval
#define _style_ca	*((int*)_ppvar[2]._pvoid)
#define _ion_dicadv	*_ppvar[3]._pval
#define diam	*_ppvar[4]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_factors(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_ca_prox", _hoc_setdata,
 "factors_ca_prox", _hoc_factors,
 0, 0
};
 /* declare global and static user variables */
#define DCa DCa_ca_prox
 double DCa = 0.6;
#define E_2 E_2_ca_prox
 double E_2 = 0.0255;
#define E_1 E_1_ca_prox
 double E_1 = 0.01315;
#define b_ATPase b_ATPase_ca_prox
 double b_ATPase = 0.005;
#define cao cao_ca_prox
 double cao = 2;
#define f_ATPase f_ATPase_ca_prox
 double f_ATPase = 100;
#define k2buf k2buf_ca_prox
 double k2buf = 0.03;
#define k1buf k1buf_ca_prox
 double k1buf = 30;
#define mM2M mM2M_ca_prox
 double mM2M = 0.001;
#define nao nao_ca_prox
 double nao = 152;
#define nai nai_ca_prox
 double nai = 7.6;
#define vrat vrat_ca_prox
 double vrat[5];
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "DCa_ca_prox", "um2/ms",
 "k1buf_ca_prox", "/mM",
 "k2buf_ca_prox", "/ms",
 "cao_ca_prox", "mM",
 "E_1_ca_prox", "/mV",
 "E_2_ca_prox", "/mV",
 "nai_ca_prox", "mM",
 "nao_ca_prox", "mM",
 "f_ATPase_ca_prox", "/mM",
 "b_ATPase_ca_prox", "/ms",
 "mM2M_ca_prox", "1",
 "vrat_ca_prox", "1",
 "B_ca_prox", "mM",
 "K2f_ex_ca_prox", "mA/cm2mM2",
 "K2f_ATPase_ca_prox", "mA/cm2",
 "ca_ca_prox", "mM",
 "CaBuffer_ca_prox", "mM",
 "Buffer_ca_prox", "mM",
 "n_ca_prox", "1",
 0,0
};
 static double Buffer0 = 0;
 static double CaBuffer0 = 0;
 static double ca0 = 0;
 static double delta_t = 0.01;
 static double n0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "DCa_ca_prox", &DCa_ca_prox,
 "k1buf_ca_prox", &k1buf_ca_prox,
 "k2buf_ca_prox", &k2buf_ca_prox,
 "cao_ca_prox", &cao_ca_prox,
 "E_1_ca_prox", &E_1_ca_prox,
 "E_2_ca_prox", &E_2_ca_prox,
 "nai_ca_prox", &nai_ca_prox,
 "nao_ca_prox", &nao_ca_prox,
 "f_ATPase_ca_prox", &f_ATPase_ca_prox,
 "b_ATPase_ca_prox", &b_ATPase_ca_prox,
 "mM2M_ca_prox", &mM2M_ca_prox,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "vrat_ca_prox", vrat_ca_prox, 5,
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"ca_prox",
 "B_ca_prox",
 "K2f_ex_ca_prox",
 "K2f_ATPase_ca_prox",
 0,
 0,
 "ca_ca_prox[5]",
 "CaBuffer_ca_prox[5]",
 "Buffer_ca_prox[5]",
 "n_ca_prox",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 static int _type_ica;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 42, _prop);
 	/*initialize range parameters*/
 	B = 0.025;
 	K2f_ex = 4.85e-13;
 	K2f_ATPase = 9.26259e-06;
 	_prop->param = _p;
 	_prop->param_size = 42;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[4]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
  _type_ica = prop_ion->_type;
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ca_prox_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_prop_size(_mechtype, 42, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "diam");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_ldifus1(_difusfunc);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ca_prox /Users/xiey/Dropbox/GitHub/multiscale-synaptic-model/model/electrical/MVNmodel/x86_64/ca_prox.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 9.6485309;
 static double PI = 3.14159265359;
 static double _zfactors_done ;
 static double _zfrat [ 5 ] ;
 static double _zdsq , _zdsqvol ;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int factors();
 extern double *_getelm();
 
#define _MATELM2(_row,_col)	*(_getelm(_row + 1, _col + 1))
 
#define _RHS2(_arg) _coef2[_arg + 1]
 static double *_coef2;
 
#define _linmat2  0
 static void* _sparseobj2;
 static void* _cvsparseobj2;
 
static int _ode_spec2(_threadargsproto_);
/*static int _ode_matsol2(_threadargsproto_);*/
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist2[15], _dlist2[15]; static double *_temp2;
 static int state();
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   Dn = f_ATPase * cai * ( 1.0 - n ) - b_ATPase * n ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 Dn = Dn  / (1. - dt*( ( f_ATPase * cai )*( ( ( - 1.0 ) ) ) - ( b_ATPase )*( 1.0 ) )) ;
 return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
    n = n + (1. - exp(dt*(( f_ATPase * cai )*( ( ( - 1.0 ) ) ) - ( b_ATPase )*( 1.0 ))))*(- ( ( ( f_ATPase )*( cai ) )*( ( 1.0 ) ) ) / ( ( ( f_ATPase )*( cai ) )*( ( ( - 1.0 ) ) ) - ( b_ATPase )*( 1.0 ) ) - n) ;
   }
  return 0;
}
 
static int  factors (  ) {
   double _lr , _ldr2 ;
 _lr = 1.0 / 2.0 ;
   _ldr2 = _lr / ( 5.0 - 1.0 ) / 2.0 ;
   vrat [ 0 ] = 0.0 ;
   _zfrat [ 0 ] = 2.0 * _lr ;
   {int  _li ;for ( _li = 0 ; _li <= 5 - 2 ; _li ++ ) {
     vrat [ _li ] = vrat [ _li ] + PI * ( _lr - _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     _lr = _lr - _ldr2 ;
     _zfrat [ _li + 1 ] = 2.0 * PI * _lr / ( 2.0 * _ldr2 ) ;
     _lr = _lr - _ldr2 ;
     vrat [ _li + 1 ] = PI * ( _lr + _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     } }
    return 0; }
 
static void _hoc_factors(void) {
  double _r;
   _r = 1.;
 factors (  );
 hoc_retpushx(_r);
}
 
static int state ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<15;_i++){
  	_RHS2(_i) = -_dt1*(_p[_slist2[_i]] - _p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
} 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 0, _i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 5, _i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 10) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 10, _i + 10) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
     ca CaBuffer Buffer }
   */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
     ca }
   */
 /* ~ ca [ 0 ] < < ( ( - ica - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS2( 10 +  0) += (b_flux =   ( ( - ica - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 5 - 2 ; _li ++ ) {
     /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 _RHS2( 10 +  _li) -= (f_flux - b_flux);
 _RHS2( 10 +  _li + 1) += (f_flux - b_flux);
 
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 10 +  _li ,10 +  _li)  += _term;
 _MATELM2( 10 +  _li + 1 ,10 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 10 +  _li ,10 +  _li + 1)  -= _term;
 _MATELM2( 10 +  _li + 1 ,10 +  _li + 1)  += _term;
 /*REACTION*/
  } }
   _zdsq = diam * diam ;
   {int  _li ;for ( _li = 0 ; _li <= 5 - 1 ; _li ++ ) {
     _zdsqvol = _zdsq * vrat [ _li ] ;
     /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 _RHS2( 0 +  _li) -= (f_flux - b_flux);
 _RHS2( 10 +  _li) -= (f_flux - b_flux);
 _RHS2( 5 +  _li) += (f_flux - b_flux);
 
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM2( 0 +  _li ,0 +  _li)  += _term;
 _MATELM2( 10 +  _li ,0 +  _li)  += _term;
 _MATELM2( 5 +  _li ,0 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM2( 0 +  _li ,10 +  _li)  += _term;
 _MATELM2( 10 +  _li ,10 +  _li)  += _term;
 _MATELM2( 5 +  _li ,10 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM2( 0 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 10 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
   cai = ca [ 0 ] ;
     } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec2() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<15;_i++) _p[_dlist2[_i]] = 0.0;}
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
   ca CaBuffer Buffer }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
   ca }
 */
 /* ~ ca [ 0 ] < < ( ( - ica - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca [ 0] += (b_flux =   ( ( - ica - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 5 - 2 ; _li ++ ) {
   /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 Dca [ _li] -= (f_flux - b_flux);
 Dca [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 5 - 1 ; _li ++ ) {
   _zdsqvol = _zdsq * vrat [ _li ] ;
   /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 DBuffer [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCaBuffer [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 cai = ca [ 0 ] ;
 for (_i=0; _i < 5; _i++) { _p[_dlist2[_i + 0]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 5; _i++) { _p[_dlist2[_i + 5]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 5; _i++) { _p[_dlist2[_i + 10]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol2() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<15;_i++){
  	_RHS2(_i) = _dt1*(_p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
} 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 0, _i + 0) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 5, _i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 5; _i++) {
  	_RHS2(_i + 10) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM2(_i + 10, _i + 10) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
 ca CaBuffer Buffer }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
 ca }
 */
 /* ~ ca [ 0 ] < < ( ( - ica - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 5 - 2 ; _li ++ ) {
 /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 10 +  _li ,10 +  _li)  += _term;
 _MATELM2( 10 +  _li + 1 ,10 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 10 +  _li ,10 +  _li + 1)  -= _term;
 _MATELM2( 10 +  _li + 1 ,10 +  _li + 1)  += _term;
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 5 - 1 ; _li ++ ) {
 _zdsqvol = _zdsq * vrat [ _li ] ;
 /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM2( 0 +  _li ,0 +  _li)  += _term;
 _MATELM2( 10 +  _li ,0 +  _li)  += _term;
 _MATELM2( 5 +  _li ,0 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM2( 0 +  _li ,10 +  _li)  += _term;
 _MATELM2( 10 +  _li ,10 +  _li)  += _term;
 _MATELM2( 5 +  _li ,10 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM2( 0 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 10 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
 cai = ca [ 0 ] ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ hoc_execerror("ca_prox", "cannot be used with CVODE"); return 0;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }
 static void* _difspace1;
extern double nrn_nernst_coef();
static double _difcoef1(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  diam * diam * vrat [ ((int) _i ) ] ;
 if (_i ==  0) {
  *_pdfcdc = nrn_nernst_coef(_type_ica)*( ( ( - _ion_dicadv  - i_Na_Ca_ex - i_ATPase ) * PI * diam / ( 2.0 * FARADAY ) ));
 }else{ *_pdfcdc=0.;}
   return DCa * diam * diam * vrat [ ((int) _i ) ] ;
}
 static void _difusfunc(ldifusfunc2_t _f, _NrnThread* _nt) {int _i;
  for (_i=0; _i < 5; ++_i) (*_f)(_mechtype, _difcoef1, &_difspace1, _i,  3, 25 , _nt);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 for (_i=0; _i<5; _i++) Buffer[_i] = Buffer0;
 for (_i=0; _i<5; _i++) CaBuffer[_i] = CaBuffer0;
 for (_i=0; _i<5; _i++) ca[_i] = ca0;
  n = n0;
 {
   if ( _zfactors_done  == 0.0 ) {
     _zfactors_done = 1.0 ;
     factors ( _threadargs_ ) ;
     }
   n = f_ATPase * cai / ( f_ATPase * cai + b_ATPase ) ;
   Kd = k1buf / k2buf ;
   B0 = B / ( 1.0 + Kd * cai ) ;
   {int  _li ;for ( _li = 0 ; _li <= 5 - 1 ; _li ++ ) {
     cai = 5e-5 ;
     ca [ _li ] = cai ;
     Buffer [ _li ] = B0 ;
     CaBuffer [ _li ] = B - B0 ;
     } }
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 initmodel();
  _ion_cai = cai;
  nrn_wrote_conc(_ca_sym, (&(_ion_cai)) - 1, _style_ca);
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 { error =  states();
 if(error){fprintf(stderr,"at line 85 in file ca_prox.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } { error = sparse(&_sparseobj2, 15, _slist2, _dlist2, _p, &t, dt, state,&_coef2, _linmat2);
 if(error){fprintf(stderr,"at line 88 in file ca_prox.mod:\n	SOLVE state METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
    if (secondorder) {
    int _i;
    for (_i = 0; _i < 15; ++_i) {
      _p[_slist2[_i]] += dt*_p[_dlist2[_i]];
    }}
 } {
   i_Na_Ca_ex = - K2f_ex * ( pow( nai , 3.0 ) * cao * exp ( E_1 * v ) - pow( nao , 3.0 ) * cai * exp ( - E_2 * v ) ) ;
   i_ATPase = K2f_ATPase * n ;
   }
  _ion_cai = cai;
}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
 for(_i=0;_i<5;_i++){_slist2[0+_i] = (Buffer + _i) - _p;  _dlist2[0+_i] = (DBuffer + _i) - _p;}
 for(_i=0;_i<5;_i++){_slist2[5+_i] = (CaBuffer + _i) - _p;  _dlist2[5+_i] = (DCaBuffer + _i) - _p;}
 for(_i=0;_i<5;_i++){_slist2[10+_i] = (ca + _i) - _p;  _dlist2[10+_i] = (Dca + _i) - _p;}
_first = 0;
}
