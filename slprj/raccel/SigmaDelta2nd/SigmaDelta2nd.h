#ifndef RTW_HEADER_SigmaDelta2nd_h_
#define RTW_HEADER_SigmaDelta2nd_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#include "rtw_modelmap_simtarget.h"
#ifndef SigmaDelta2nd_COMMON_INCLUDES_
#define SigmaDelta2nd_COMMON_INCLUDES_
#include <stdio.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "SigmaDelta2nd_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME SigmaDelta2nd
#define NSAMPLE_TIMES (6) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (14) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (2)   
#elif NCSTATES != 2
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T lqvljim52a ; real_T mrrqtpofed ; real_T iyb4nnud3n ;
real_T fglzwg0gpe ; real_T dbb1z0mm3j ; real_T dblm24swqm ; real_T bhb2jtlude
; real_T cecrguin1q ; real_T cyljhahbp4 ; real_T koecjb54sh ; real_T
aiuvh1nbjv ; real_T lu0v52hhki ; real_T e4dbl2cfl3 ; real_T nwvay2kmxd ; } B
; typedef struct { real_T n4rivhzg4g ; real_T feyvwig01o [ 92 ] ; real_T
myljyfih4p ; real_T dumfjgwxhc ; real_T laliiofkj3 [ 92 ] ; real_T nrjeu0zetd
; real_T fqos0o4h34 ; real_T mku35wrylx [ 92 ] ; real_T ko2zssnvqw ; struct {
real_T modelTStart ; } kly3raw3cg ; struct { void * LoggedData ; } mypftr2o5l
; struct { void * TUbufferPtrs [ 2 ] ; } kzc2xqxsxo ; int32_T d5k240dd1f ;
int32_T bnlws2sh1t ; int32_T o5hyij1dzr ; int32_T eckossjxt3 ; int32_T
n0gerj2i33 ; int32_T bjfytdftqo ; int32_T n3gfvygdda ; int32_T apwo5tufnb ;
int32_T kurctjxgfu ; int32_T gygqelpgtp ; int32_T f3whwvtp2b ; int32_T
ld5rza5xa5 ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } if4dnc4xux ; int_T is1yc1voif ; }
DW ; typedef struct { real_T ajbbq1g4g5 ; real_T bhyqlswbyd ; } X ; typedef
struct { real_T ajbbq1g4g5 ; real_T bhyqlswbyd ; } XDot ; typedef struct {
boolean_T ajbbq1g4g5 ; boolean_T bhyqlswbyd ; } XDis ; typedef struct {
real_T ajbbq1g4g5 ; real_T bhyqlswbyd ; } CStateAbsTol ; typedef struct {
real_T ajbbq1g4g5 ; real_T bhyqlswbyd ; } CXPtMin ; typedef struct { real_T
ajbbq1g4g5 ; real_T bhyqlswbyd ; } CXPtMax ; typedef struct { real_T
bq1odzp3h4 ; } ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
DataMapInfo ; struct P_ { real_T Carrier_Amp ; real_T Carrier_Bias ; real_T
Carrier_Freq ; real_T Carrier_Phase ; real_T Modulated_Amp ; real_T
Modulated_Bias ; real_T Modulated_Freq ; real_T Modulated_Phase ; real_T
Integrator1_IC ; real_T FIRDecimationto128MHz_FILT [ 96 ] ; real_T
FIRDecimationto32MHz_FILT [ 96 ] ; real_T FIRDecimationto8MHz_FILT [ 96 ] ;
real_T Gain_Gain ; real_T TransportDelay_Delay ; real_T
TransportDelay_InitOutput ; real_T Gain2_Gain ; real_T Gain1_Gain ; real_T
Integrator_IC ; real_T Gain3_Gain ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern P rtP ; extern mxArray * mr_SigmaDelta2nd_GetDWork ( ) ; extern void
mr_SigmaDelta2nd_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_SigmaDelta2nd_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * SigmaDelta2nd_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
