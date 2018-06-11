#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _ANsyn_reg();
extern void _NMDAsyn_reg();
extern void _a_reg();
extern void _ahp_reg();
extern void _akfast_reg();
extern void _bkfast_reg();
extern void _ca_dist_reg();
extern void _ca_prox_reg();
extern void _ca_soma_reg();
extern void _caleak_reg();
extern void _clleak_reg();
extern void _gNPde_reg();
extern void _gNPde2_reg();
extern void _gNPdesin_reg();
extern void _gNPoiss_reg();
extern void _gNReg_reg();
extern void _gclamp_reg();
extern void _ggSBA_DestexheRudolph_reg();
extern void _hcurr_reg();
extern void _hva_reg();
extern void _kleak_reg();
extern void _kslow_reg();
extern void _lva_reg();
extern void _na_reg();
extern void _naleak_reg();
extern void _nap_reg();
extern void _nmda_reg();
extern void _presyn_reg();
extern void _sinstim_reg();

modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," ANsyn.mod");
fprintf(stderr," NMDAsyn.mod");
fprintf(stderr," a.mod");
fprintf(stderr," ahp.mod");
fprintf(stderr," akfast.mod");
fprintf(stderr," bkfast.mod");
fprintf(stderr," ca_dist.mod");
fprintf(stderr," ca_prox.mod");
fprintf(stderr," ca_soma.mod");
fprintf(stderr," caleak.mod");
fprintf(stderr," clleak.mod");
fprintf(stderr," gNPde.mod");
fprintf(stderr," gNPde2.mod");
fprintf(stderr," gNPdesin.mod");
fprintf(stderr," gNPoiss.mod");
fprintf(stderr," gNReg.mod");
fprintf(stderr," gclamp.mod");
fprintf(stderr," ggSBA_DestexheRudolph.mod");
fprintf(stderr," hcurr.mod");
fprintf(stderr," hva.mod");
fprintf(stderr," kleak.mod");
fprintf(stderr," kslow.mod");
fprintf(stderr," lva.mod");
fprintf(stderr," na.mod");
fprintf(stderr," naleak.mod");
fprintf(stderr," nap.mod");
fprintf(stderr," nmda.mod");
fprintf(stderr," presyn.mod");
fprintf(stderr," sinstim.mod");
fprintf(stderr, "\n");
    }
_ANsyn_reg();
_NMDAsyn_reg();
_a_reg();
_ahp_reg();
_akfast_reg();
_bkfast_reg();
_ca_dist_reg();
_ca_prox_reg();
_ca_soma_reg();
_caleak_reg();
_clleak_reg();
_gNPde_reg();
_gNPde2_reg();
_gNPdesin_reg();
_gNPoiss_reg();
_gNReg_reg();
_gclamp_reg();
_ggSBA_DestexheRudolph_reg();
_hcurr_reg();
_hva_reg();
_kleak_reg();
_kslow_reg();
_lva_reg();
_na_reg();
_naleak_reg();
_nap_reg();
_nmda_reg();
_presyn_reg();
_sinstim_reg();
}
