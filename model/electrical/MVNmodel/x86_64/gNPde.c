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
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__gNPde
#define _nrn_initial _nrn_initial__gNPde
#define nrn_cur _nrn_cur__gNPde
#define _nrn_current _nrn_current__gNPde
#define nrn_jacob _nrn_jacob__gNPde
#define nrn_state _nrn_state__gNPde
#define _net_receive _net_receive__gNPde 
#define conductances conductances__gNPde 
 
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
#define rseed _p[0]
#define gmax _p[1]
#define e _p[2]
#define N _p[3]
#define freq _p[4]
#define tau1 _p[5]
#define tau2 _p[6]
#define i _p[7]
#define gsum _p[8]
#define gtot _p[9]
#define tpeak _p[10]
#define gpeak _p[11]
#define g (_p + 12)
#define z (_p + 213)
#define fdt1 _p[414]
#define fac1 _p[415]
#define fdt2 _p[416]
#define fac2 _p[417]
#define fac _p[418]
#define sp _p[419]
#define _g _p[420]
#define _nd_area  *_ppvar[0]._pval
 
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
 static double _hoc_conductances();
 static double _hoc_unirand();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "conductances", _hoc_conductances,
 "unirand", _hoc_unirand,
 0, 0
};
#define unirand unirand_gNPde
 extern double unirand( );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gmax", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmax", "uS",
 "e", "mV",
 "tau1", "ms",
 "tau2", "ms",
 "i", "nA",
 "gsum", "uS",
 "gtot", "uS",
 "tpeak", "ms",
 "gpeak", "1",
 0,0
};
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"gNPde",
 "rseed",
 "gmax",
 "e",
 "N",
 "freq",
 "tau1",
 "tau2",
 0,
 "i",
 "gsum",
 "gtot",
 "tpeak",
 "gpeak",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 421, _prop);
 	/*initialize range parameters*/
 	rseed = 0;
 	gmax = 0;
 	e = 0;
 	N = 1;
 	freq = 10;
 	tau1 = 3;
 	tau2 = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 421;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _gNPde_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 421, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 gNPde /Users/xiey/Dropbox/GitHub/multiscale-synaptic-model/model/electrical/MVNmodel/x86_64/gNPde.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "N conductances driven by Poisson-distributed spikes";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int conductances();
 
static int  conductances (  ) {
   double _li , _lspike ;
 gsum = 0.0 ;
   {int  _li ;for ( _li = 0 ; _li <= ((int) N ) - 1 ; _li ++ ) {
     _lspike = 0.0 ;
     if ( unirand ( _threadargs_ ) <= sp ) {
       _lspike = 1.0 ;
       }
     g [ _li ] = ( g [ _li ] * fdt2 ) + ( z [ _li ] * fac2 ) ;
     z [ _li ] = ( z [ _li ] * fdt1 ) + ( fac1 / dt ) * _lspike ;
     gsum = gsum + g [ _li ] ;
     } }
   gsum = gsum / gpeak ;
    return 0; }
 
static double _hoc_conductances(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 conductances (  );
 return(_r);
}
 
double unirand (  ) {
   double _lunirand;
 return ( _threadargscomma_ scop_random ( ) ) ;
   
return _lunirand;
 }
 
static double _hoc_unirand(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  unirand (  );
 return(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("gNPde", "cannot be used with CVODE"); return 0;}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 {
   gtot = 0.0 ;
   gsum = 0.0 ;
   {int  _li ;for ( _li = 0 ; _li <= 201 - 1 ; _li ++ ) {
     g [ _li ] = 0.0 ;
     z [ _li ] = 0.0 ;
     } }
   fdt1 = exp ( - dt / tau1 ) ;
   fac1 = tau1 * ( 1.0 - fdt1 ) ;
   fdt2 = exp ( - dt / tau2 ) ;
   fac2 = tau2 * ( 1.0 - fdt2 ) ;
   fac = tau1 * tau2 / ( tau1 - tau2 ) ;
   tpeak = fac * log ( tau1 / tau2 ) ;
   gpeak = fac * ( exp ( - tpeak / tau1 ) - exp ( - tpeak / tau2 ) ) ;
   sp = ( freq * dt ) / 1000.0 ;
   set_seed ( rseed ) ;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   gtot = gmax * gsum ;
   i = gtot * ( v - e ) ;
   }
 _current += i;

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
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
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
 { error =  conductances();
 if(error){fprintf(stderr,"at line 70 in file gNPde.mod:\n	SOLVE conductances\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}
