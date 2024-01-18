#include "rt_logging_mmi.h"
#include "SigmaDelta2nd_capi.h"
#include <math.h>
#include "SigmaDelta2nd.h"
#include "SigmaDelta2nd_private.h"
#include "SigmaDelta2nd_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 6 , & stopRequested ) ; }
rtExtModeShutdown ( 6 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 6 ; const char_T
* gbl_raccel_Version = "9.6 (R2021b) 14-May-2021" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 , 1 , 1 } ; const char *
raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ;
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ;
#endif
void * rt_TDelayCreateBuf ( int_T numBuffer , int_T bufSz , int_T elemSz ) {
return ( ( void * ) utMalloc ( numBuffer * bufSz * elemSz ) ) ; }
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * uBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * uBufPtr + bufSz ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ;
if ( istransportdelay ) { numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; }
testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <=
tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
uBufPtr = tempU ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T * uBuf ,
int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T
initOutput , boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput )
{ int_T i ; real_T yout , t1 , t2 , u1 , u2 ; real_T * tBuf = uBuf + bufSz ;
if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay > tStart ) )
return initOutput ; if ( tMinusDelay <= tStart ) return initOutput ; if ( (
tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [
oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx ==
bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ;
u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if (
tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 =
( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 +
f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput ) { if (
newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; } newIdx -- ;
} else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; } newIdx =
bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) { while (
tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < ( bufSz - 1
) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay ) { i = (
i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0
; } * lastIdx = i ; if ( discrete ) { double tempEps = ( DBL_EPSILON ) *
128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf [ i ] ) ; if (
tempEps > localEps ) { localEps = tempEps ; } localEps = localEps / 2.0 ; if
( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout = uBuf [ i ] ; } else {
if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ;
} } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1
] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ;
u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; }
else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 )
; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } } return ( yout ) ; }
#ifndef __RTW_UTFREE__  
extern void utFree ( void * ) ;
#endif
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } void MdlInitialize
( void ) { rtX . ajbbq1g4g5 = rtP . Integrator1_IC ; rtDW . bnlws2sh1t = 72 ;
rtDW . d5k240dd1f = 3 ; rtDW . o5hyij1dzr = 69 ; rtDW . eckossjxt3 = 0 ; rtDW
. myljyfih4p = 0.0 ; rtDW . n4rivhzg4g = 0.0 ; rtDW . bjfytdftqo = 72 ; rtDW
. n0gerj2i33 = 3 ; rtDW . n3gfvygdda = 69 ; rtDW . apwo5tufnb = 0 ; rtDW .
nrjeu0zetd = 0.0 ; rtDW . dumfjgwxhc = 0.0 ; rtDW . gygqelpgtp = 72 ; rtDW .
kurctjxgfu = 3 ; rtDW . f3whwvtp2b = 69 ; rtDW . ld5rza5xa5 = 0 ; rtDW .
ko2zssnvqw = 0.0 ; rtDW . fqos0o4h34 = 0.0 ; memset ( & rtDW . feyvwig01o [ 0
] , 0 , 92U * sizeof ( real_T ) ) ; memset ( & rtDW . laliiofkj3 [ 0 ] , 0 ,
92U * sizeof ( real_T ) ) ; memset ( & rtDW . mku35wrylx [ 0 ] , 0 , 92U *
sizeof ( real_T ) ) ; rtX . bhyqlswbyd = rtP . Integrator_IC ; } void
MdlStart ( void ) { { bool externalInputIsInDatasetFormat = false ; void *
pISigstreamManager = rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} { char ptrKey [ 1024 ] ; { real_T * pBuffer = ( real_T * )
rt_TDelayCreateBuf ( 2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer == ( NULL
) ) { ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ;
} rtDW . if4dnc4xux . Tail = 0 ; rtDW . if4dnc4xux . Head = 0 ; rtDW .
if4dnc4xux . Last = 0 ; rtDW . if4dnc4xux . CircularBufSize = 1024 ; pBuffer
[ 0 ] = rtP . TransportDelay_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ;
rtDW . kzc2xqxsxo . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; sprintf
( ptrKey , "SigmaDelta2nd/Transport Delay_TUbuffer%d" , 0 ) ;
slsaSaveRawMemoryForSimTargetOP ( rtS , ptrKey , ( void * * ) ( & rtDW .
kzc2xqxsxo . TUbufferPtrs [ 0 ] ) , 2 * 1024 * sizeof ( real_T ) , ( NULL ) ,
( NULL ) ) ; } } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) {
int32_T cffIdx ; int32_T jIdx ; int32_T maxWindow ; int32_T outBufIdx ;
int32_T phaseIdx ; rtB . lqvljim52a = ( muDoubleScalarSin ( rtP .
Carrier_Freq * ssGetTaskTime ( rtS , 0 ) + rtP . Carrier_Phase ) * rtP .
Carrier_Amp + rtP . Carrier_Bias ) * ( muDoubleScalarSin ( rtP .
Modulated_Freq * ssGetTaskTime ( rtS , 0 ) + rtP . Modulated_Phase ) * rtP .
Modulated_Amp + rtP . Modulated_Bias ) ; rtB . mrrqtpofed = rtX . ajbbq1g4g5
; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . mrrqtpofed > 0.0 ) { rtDW
. is1yc1voif = 1 ; } else if ( rtB . mrrqtpofed < 0.0 ) { rtDW . is1yc1voif =
- 1 ; } else { rtDW . is1yc1voif = 0 ; } rtB . iyb4nnud3n = rtDW . is1yc1voif
; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { phaseIdx = rtDW . d5k240dd1f + 1 ;
outBufIdx = rtDW . eckossjxt3 ; maxWindow = ( rtDW . d5k240dd1f + 1 ) * 23 ;
rtDW . n4rivhzg4g += rtB . iyb4nnud3n * rtP . FIRDecimationto128MHz_FILT [
rtDW . bnlws2sh1t ] ; cffIdx = rtDW . bnlws2sh1t + 1 ; for ( jIdx = rtDW .
o5hyij1dzr + 1 ; jIdx < maxWindow ; jIdx ++ ) { rtDW . n4rivhzg4g += rtDW .
feyvwig01o [ jIdx ] * rtP . FIRDecimationto128MHz_FILT [ cffIdx ] ; cffIdx ++
; } for ( jIdx = maxWindow - 23 ; jIdx <= rtDW . o5hyij1dzr ; jIdx ++ ) {
rtDW . n4rivhzg4g += rtDW . feyvwig01o [ jIdx ] * rtP .
FIRDecimationto128MHz_FILT [ cffIdx ] ; cffIdx ++ ; } rtDW . feyvwig01o [
rtDW . o5hyij1dzr ] = rtB . iyb4nnud3n ; maxWindow = rtDW . o5hyij1dzr + 23 ;
if ( rtDW . o5hyij1dzr + 23 >= 92 ) { maxWindow = rtDW . o5hyij1dzr - 69 ; }
if ( rtDW . d5k240dd1f + 1 >= 4 ) { rtDW . myljyfih4p = rtDW . n4rivhzg4g ;
outBufIdx = rtDW . eckossjxt3 + 1 ; rtDW . n4rivhzg4g = 0.0 ; phaseIdx = 0 ;
cffIdx = 0 ; maxWindow -- ; if ( maxWindow < 0 ) { maxWindow += 23 ; } } rtDW
. o5hyij1dzr = maxWindow ; rtDW . bnlws2sh1t = cffIdx ; rtDW . d5k240dd1f =
phaseIdx ; rtDW . eckossjxt3 = outBufIdx ; if ( ssIsSpecialSampleHit ( rtS ,
3 , 2 , 0 ) ) { rtB . fglzwg0gpe = rtDW . myljyfih4p ; rtDW . eckossjxt3 = 0
; } } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { phaseIdx = rtDW . n0gerj2i33 + 1
; outBufIdx = rtDW . apwo5tufnb ; maxWindow = ( rtDW . n0gerj2i33 + 1 ) * 23
; rtDW . dumfjgwxhc += rtB . fglzwg0gpe * rtP . FIRDecimationto32MHz_FILT [
rtDW . bjfytdftqo ] ; cffIdx = rtDW . bjfytdftqo + 1 ; for ( jIdx = rtDW .
n3gfvygdda + 1 ; jIdx < maxWindow ; jIdx ++ ) { rtDW . dumfjgwxhc += rtDW .
laliiofkj3 [ jIdx ] * rtP . FIRDecimationto32MHz_FILT [ cffIdx ] ; cffIdx ++
; } for ( jIdx = maxWindow - 23 ; jIdx <= rtDW . n3gfvygdda ; jIdx ++ ) {
rtDW . dumfjgwxhc += rtDW . laliiofkj3 [ jIdx ] * rtP .
FIRDecimationto32MHz_FILT [ cffIdx ] ; cffIdx ++ ; } rtDW . laliiofkj3 [ rtDW
. n3gfvygdda ] = rtB . fglzwg0gpe ; maxWindow = rtDW . n3gfvygdda + 23 ; if (
rtDW . n3gfvygdda + 23 >= 92 ) { maxWindow = rtDW . n3gfvygdda - 69 ; } if (
rtDW . n0gerj2i33 + 1 >= 4 ) { rtDW . nrjeu0zetd = rtDW . dumfjgwxhc ;
outBufIdx = rtDW . apwo5tufnb + 1 ; rtDW . dumfjgwxhc = 0.0 ; phaseIdx = 0 ;
cffIdx = 0 ; maxWindow -- ; if ( maxWindow < 0 ) { maxWindow += 23 ; } } rtDW
. n3gfvygdda = maxWindow ; rtDW . bjfytdftqo = cffIdx ; rtDW . n0gerj2i33 =
phaseIdx ; rtDW . apwo5tufnb = outBufIdx ; if ( ssIsSpecialSampleHit ( rtS ,
4 , 3 , 0 ) ) { rtB . dbb1z0mm3j = rtDW . nrjeu0zetd ; rtDW . apwo5tufnb = 0
; } } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) { phaseIdx = rtDW . kurctjxgfu + 1
; outBufIdx = rtDW . ld5rza5xa5 ; maxWindow = ( rtDW . kurctjxgfu + 1 ) * 23
; rtDW . fqos0o4h34 += rtB . dbb1z0mm3j * rtP . FIRDecimationto8MHz_FILT [
rtDW . gygqelpgtp ] ; cffIdx = rtDW . gygqelpgtp + 1 ; for ( jIdx = rtDW .
f3whwvtp2b + 1 ; jIdx < maxWindow ; jIdx ++ ) { rtDW . fqos0o4h34 += rtDW .
mku35wrylx [ jIdx ] * rtP . FIRDecimationto8MHz_FILT [ cffIdx ] ; cffIdx ++ ;
} for ( jIdx = maxWindow - 23 ; jIdx <= rtDW . f3whwvtp2b ; jIdx ++ ) { rtDW
. fqos0o4h34 += rtDW . mku35wrylx [ jIdx ] * rtP . FIRDecimationto8MHz_FILT [
cffIdx ] ; cffIdx ++ ; } rtDW . mku35wrylx [ rtDW . f3whwvtp2b ] = rtB .
dbb1z0mm3j ; maxWindow = rtDW . f3whwvtp2b + 23 ; if ( rtDW . f3whwvtp2b + 23
>= 92 ) { maxWindow = rtDW . f3whwvtp2b - 69 ; } if ( rtDW . kurctjxgfu + 1
>= 4 ) { rtDW . ko2zssnvqw = rtDW . fqos0o4h34 ; outBufIdx = rtDW .
ld5rza5xa5 + 1 ; rtDW . fqos0o4h34 = 0.0 ; phaseIdx = 0 ; cffIdx = 0 ;
maxWindow -- ; if ( maxWindow < 0 ) { maxWindow += 23 ; } } rtDW . f3whwvtp2b
= maxWindow ; rtDW . gygqelpgtp = cffIdx ; rtDW . kurctjxgfu = phaseIdx ;
rtDW . ld5rza5xa5 = outBufIdx ; if ( ssIsSpecialSampleHit ( rtS , 5 , 4 , 0 )
) { rtB . dblm24swqm = rtDW . ko2zssnvqw ; rtDW . ld5rza5xa5 = 0 ; } } rtB .
bhb2jtlude = rtP . Gain_Gain * rtB . lqvljim52a ; { real_T * * uBuffer = (
real_T * * ) & rtDW . kzc2xqxsxo . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP . TransportDelay_Delay ;
rtB . cecrguin1q = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
rtDW . if4dnc4xux . CircularBufSize , & rtDW . if4dnc4xux . Last , rtDW .
if4dnc4xux . Tail , rtDW . if4dnc4xux . Head , rtP .
TransportDelay_InitOutput , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ssGetTimeOfLastOutput ( rtS ) == ssGetT ( rtS ) ) ) ) ; } rtB . cyljhahbp4
= rtP . Gain2_Gain * rtB . cecrguin1q ; rtB . koecjb54sh = rtB . bhb2jtlude -
rtB . cyljhahbp4 ; rtB . aiuvh1nbjv = rtP . Gain1_Gain * rtB . koecjb54sh ;
rtB . lu0v52hhki = rtX . bhyqlswbyd ; rtB . e4dbl2cfl3 = rtB . lu0v52hhki -
rtB . cecrguin1q ; rtB . nwvay2kmxd = rtP . Gain3_Gain * rtB . e4dbl2cfl3 ;
UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) { { real_T * *
uBuffer = ( real_T * * ) & rtDW . kzc2xqxsxo . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( rtS ) ; rtDW . if4dnc4xux . Head = ( ( rtDW . if4dnc4xux .
Head < ( rtDW . if4dnc4xux . CircularBufSize - 1 ) ) ? ( rtDW . if4dnc4xux .
Head + 1 ) : 0 ) ; if ( rtDW . if4dnc4xux . Head == rtDW . if4dnc4xux . Tail
) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( & rtDW . if4dnc4xux .
CircularBufSize , & rtDW . if4dnc4xux . Tail , & rtDW . if4dnc4xux . Head , &
rtDW . if4dnc4xux . Last , simTime - rtP . TransportDelay_Delay , uBuffer , (
boolean_T ) 0 , false , & rtDW . if4dnc4xux . MaxNewBufSize ) ) {
ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ; return ; }
slsaSaveRawMemoryForSimTargetOP ( rtS ,
"SigmaDelta2nd/Transport Delay_TUbuffer0" , ( void * * ) ( & uBuffer [ 0 ] )
, 2 * rtDW . if4dnc4xux . CircularBufSize * sizeof ( real_T ) , ( NULL ) , (
NULL ) ) ; } ( * uBuffer + rtDW . if4dnc4xux . CircularBufSize ) [ rtDW .
if4dnc4xux . Head ] = simTime ; ( * uBuffer ) [ rtDW . if4dnc4xux . Head ] =
rtB . iyb4nnud3n ; } UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void
) { XDot * _rtXdot ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot ->
ajbbq1g4g5 = rtB . nwvay2kmxd ; _rtXdot -> bhyqlswbyd = rtB . aiuvh1nbjv ; }
void MdlProjection ( void ) { } void MdlZeroCrossings ( void ) { ZCV *
_rtZCSV ; _rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV
-> bq1odzp3h4 = rtB . mrrqtpofed ; } void MdlTerminate ( void ) {
rt_TDelayFreeBuf ( rtDW . kzc2xqxsxo . TUbufferPtrs [ 0 ] ) ; } static void
mr_SigmaDelta2nd_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j
, const void * srcData , size_t numBytes ) ; static void
mr_SigmaDelta2nd_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j
, const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_SigmaDelta2nd_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static
void mr_SigmaDelta2nd_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_SigmaDelta2nd_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) ; static void mr_SigmaDelta2nd_cacheBitFieldToMxArray
( mxArray * destArray , mwIndex i , int j , uint_T bitVal ) {
mxSetFieldByNumber ( destArray , i , j , mxCreateDoubleScalar ( ( double )
bitVal ) ) ; } static uint_T mr_SigmaDelta2nd_extractBitFieldFromMxArray (
const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) ; static
uint_T mr_SigmaDelta2nd_extractBitFieldFromMxArray ( const mxArray * srcArray
, mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_SigmaDelta2nd_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex
i , int j , mwIndex offset , const void * srcData , size_t numBytes ) ;
static void mr_SigmaDelta2nd_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_SigmaDelta2nd_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) ; static void mr_SigmaDelta2nd_restoreDataFromMxArrayWithOffset (
void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex
offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * )
mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T *
) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes )
; } static void mr_SigmaDelta2nd_cacheBitFieldToCellArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static
void mr_SigmaDelta2nd_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( double ) fieldVal ) ) ; } static uint_T
mr_SigmaDelta2nd_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_SigmaDelta2nd_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) {
const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_SigmaDelta2nd_GetDWork ( ) { static
const char * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "NULL_PrevZCX" , } ;
mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( rtB
) , sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 24 ] = {
"rtDW.n4rivhzg4g" , "rtDW.feyvwig01o" , "rtDW.myljyfih4p" , "rtDW.dumfjgwxhc"
, "rtDW.laliiofkj3" , "rtDW.nrjeu0zetd" , "rtDW.fqos0o4h34" ,
"rtDW.mku35wrylx" , "rtDW.ko2zssnvqw" , "rtDW.kly3raw3cg" , "rtDW.d5k240dd1f"
, "rtDW.bnlws2sh1t" , "rtDW.o5hyij1dzr" , "rtDW.eckossjxt3" ,
"rtDW.n0gerj2i33" , "rtDW.bjfytdftqo" , "rtDW.n3gfvygdda" , "rtDW.apwo5tufnb"
, "rtDW.kurctjxgfu" , "rtDW.gygqelpgtp" , "rtDW.f3whwvtp2b" ,
"rtDW.ld5rza5xa5" , "rtDW.if4dnc4xux" , "rtDW.is1yc1voif" , } ; mxArray *
rtdwData = mxCreateStructMatrix ( 1 , 1 , 24 , rtdwDataFieldNames ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) & (
rtDW . n4rivhzg4g ) , sizeof ( rtDW . n4rivhzg4g ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & (
rtDW . feyvwig01o ) , sizeof ( rtDW . feyvwig01o ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & (
rtDW . myljyfih4p ) , sizeof ( rtDW . myljyfih4p ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & (
rtDW . dumfjgwxhc ) , sizeof ( rtDW . dumfjgwxhc ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & (
rtDW . laliiofkj3 ) , sizeof ( rtDW . laliiofkj3 ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) & (
rtDW . nrjeu0zetd ) , sizeof ( rtDW . nrjeu0zetd ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) & (
rtDW . fqos0o4h34 ) , sizeof ( rtDW . fqos0o4h34 ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) & (
rtDW . mku35wrylx ) , sizeof ( rtDW . mku35wrylx ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) & (
rtDW . ko2zssnvqw ) , sizeof ( rtDW . ko2zssnvqw ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) & (
rtDW . kly3raw3cg ) , sizeof ( rtDW . kly3raw3cg ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) &
( rtDW . d5k240dd1f ) , sizeof ( rtDW . d5k240dd1f ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) &
( rtDW . bnlws2sh1t ) , sizeof ( rtDW . bnlws2sh1t ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) &
( rtDW . o5hyij1dzr ) , sizeof ( rtDW . o5hyij1dzr ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) &
( rtDW . eckossjxt3 ) , sizeof ( rtDW . eckossjxt3 ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) &
( rtDW . n0gerj2i33 ) , sizeof ( rtDW . n0gerj2i33 ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) &
( rtDW . bjfytdftqo ) , sizeof ( rtDW . bjfytdftqo ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) &
( rtDW . n3gfvygdda ) , sizeof ( rtDW . n3gfvygdda ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) &
( rtDW . apwo5tufnb ) , sizeof ( rtDW . apwo5tufnb ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) &
( rtDW . kurctjxgfu ) , sizeof ( rtDW . kurctjxgfu ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 19 , ( const void * ) &
( rtDW . gygqelpgtp ) , sizeof ( rtDW . gygqelpgtp ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 20 , ( const void * ) &
( rtDW . f3whwvtp2b ) , sizeof ( rtDW . f3whwvtp2b ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 21 , ( const void * ) &
( rtDW . ld5rza5xa5 ) , sizeof ( rtDW . ld5rza5xa5 ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 22 , ( const void * ) &
( rtDW . if4dnc4xux ) , sizeof ( rtDW . if4dnc4xux ) ) ;
mr_SigmaDelta2nd_cacheDataAsMxArray ( rtdwData , 0 , 23 , ( const void * ) &
( rtDW . is1yc1voif ) , sizeof ( rtDW . is1yc1voif ) ) ; mxSetFieldByNumber (
ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void mr_SigmaDelta2nd_SetDWork
( const mxArray * ssDW ) { ( void ) ssDW ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 , 0
, sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW ,
0 , 1 ) ; mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW .
n4rivhzg4g ) , rtdwData , 0 , 0 , sizeof ( rtDW . n4rivhzg4g ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . feyvwig01o )
, rtdwData , 0 , 1 , sizeof ( rtDW . feyvwig01o ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . myljyfih4p )
, rtdwData , 0 , 2 , sizeof ( rtDW . myljyfih4p ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . dumfjgwxhc )
, rtdwData , 0 , 3 , sizeof ( rtDW . dumfjgwxhc ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . laliiofkj3 )
, rtdwData , 0 , 4 , sizeof ( rtDW . laliiofkj3 ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . nrjeu0zetd )
, rtdwData , 0 , 5 , sizeof ( rtDW . nrjeu0zetd ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . fqos0o4h34 )
, rtdwData , 0 , 6 , sizeof ( rtDW . fqos0o4h34 ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . mku35wrylx )
, rtdwData , 0 , 7 , sizeof ( rtDW . mku35wrylx ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . ko2zssnvqw )
, rtdwData , 0 , 8 , sizeof ( rtDW . ko2zssnvqw ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . kly3raw3cg )
, rtdwData , 0 , 9 , sizeof ( rtDW . kly3raw3cg ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . d5k240dd1f )
, rtdwData , 0 , 10 , sizeof ( rtDW . d5k240dd1f ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . bnlws2sh1t )
, rtdwData , 0 , 11 , sizeof ( rtDW . bnlws2sh1t ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . o5hyij1dzr )
, rtdwData , 0 , 12 , sizeof ( rtDW . o5hyij1dzr ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . eckossjxt3 )
, rtdwData , 0 , 13 , sizeof ( rtDW . eckossjxt3 ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . n0gerj2i33 )
, rtdwData , 0 , 14 , sizeof ( rtDW . n0gerj2i33 ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . bjfytdftqo )
, rtdwData , 0 , 15 , sizeof ( rtDW . bjfytdftqo ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . n3gfvygdda )
, rtdwData , 0 , 16 , sizeof ( rtDW . n3gfvygdda ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . apwo5tufnb )
, rtdwData , 0 , 17 , sizeof ( rtDW . apwo5tufnb ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . kurctjxgfu )
, rtdwData , 0 , 18 , sizeof ( rtDW . kurctjxgfu ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . gygqelpgtp )
, rtdwData , 0 , 19 , sizeof ( rtDW . gygqelpgtp ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . f3whwvtp2b )
, rtdwData , 0 , 20 , sizeof ( rtDW . f3whwvtp2b ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . ld5rza5xa5 )
, rtdwData , 0 , 21 , sizeof ( rtDW . ld5rza5xa5 ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . if4dnc4xux )
, rtdwData , 0 , 22 , sizeof ( rtDW . if4dnc4xux ) ) ;
mr_SigmaDelta2nd_restoreDataFromMxArray ( ( void * ) & ( rtDW . is1yc1voif )
, rtdwData , 0 , 23 , sizeof ( rtDW . is1yc1voif ) ) ; } } mxArray *
mr_SigmaDelta2nd_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 1 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char * blockType [ 1 ] = { "Scope" , } ; static const char * blockPath [ 1 ]
= { "SigmaDelta2nd/Scope" , } ; static const int reason [ 1 ] = { 0 , } ; for
( subs [ 0 ] = 0 ; subs [ 0 ] < 1 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateDoubleScalar ( ( double ) reason [ subs [ 0 ] ] ) ) ; } }
return data ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
2 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ;
ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 6 ) ; ssSetNumBlocks ( rtS , 18 ) ;
ssSetNumBlockIO ( rtS , 14 ) ; ssSetNumBlockParams ( rtS , 304 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetSampleTime ( rtS , 2 , 1.9531E-9 ) ;
ssSetSampleTime ( rtS , 3 , 7.8124E-9 ) ; ssSetSampleTime ( rtS , 4 ,
3.12496E-8 ) ; ssSetSampleTime ( rtS , 5 , 1.249984E-7 ) ; ssSetOffsetTime (
rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS ,
2 , 0.0 ) ; ssSetOffsetTime ( rtS , 3 , 0.0 ) ; ssSetOffsetTime ( rtS , 4 ,
0.0 ) ; ssSetOffsetTime ( rtS , 5 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 2669508275U ) ; ssSetChecksumVal ( rtS , 1 ,
3852389557U ) ; ssSetChecksumVal ( rtS , 2 , 854899528U ) ; ssSetChecksumVal
( rtS , 3 , 2228287752U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; ( void ) memset ( ( char * ) rtS , 0 ,
sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0 , sizeof
( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ;
ssSetExecutionInfo ( rtS , executionInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 22 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
SigmaDelta2nd_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS
, true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "SigmaDelta2nd" ) ;
ssSetPath ( rtS , "SigmaDelta2nd" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal
( rtS , 10.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo
. loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo )
; } { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 92 , 1 , 1 , 92
, 1 , 1 , 92 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static
int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 92 , 1 , 1 , 92 , 1 , 1 , 92 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32
, SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32 , SS_INT32
} ; static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" ,
"CSTATE" , "Sums" , "StatesBuff" , "OutBuff" , "Sums" , "StatesBuff" ,
"OutBuff" , "Sums" , "StatesBuff" , "OutBuff" , "PhaseIdx" , "CoeffIdx" ,
"TapDelayIndex" , "OutIdx" , "PhaseIdx" , "CoeffIdx" , "TapDelayIndex" ,
"OutIdx" , "PhaseIdx" , "CoeffIdx" , "TapDelayIndex" , "OutIdx" } ; static
const char_T * rt_LoggedStateBlockNames [ ] = { "SigmaDelta2nd/Integrator1" ,
"SigmaDelta2nd/Integrator" , "SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 128 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 32 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" ,
"SigmaDelta2nd/FIR\nDecimation to 8 MHz" } ; static const char_T *
rt_LoggedStateNames [ ] = { "" , "" , "Sums" , "StatesBuff" , "OutBuff" ,
"Sums" , "StatesBuff" , "OutBuff" , "Sums" , "StatesBuff" , "OutBuff" ,
"PhaseIdx" , "CoeffIdx" , "TapDelayIndex" , "OutIdx" , "PhaseIdx" ,
"CoeffIdx" , "TapDelayIndex" , "OutIdx" , "PhaseIdx" , "CoeffIdx" ,
"TapDelayIndex" , "OutIdx" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ]
= { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ]
= { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32
, 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 ,
0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32
, 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 ,
0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32
, 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 ,
0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ;
static int_T rt_LoggedStateIdxList [ ] = { 0 , 1 , 12 , 0 , 13 , 16 , 3 , 17
, 20 , 6 , 21 , 1 , 14 , 15 , 2 , 4 , 18 , 19 , 5 , 7 , 22 , 23 , 8 } ;
static RTWLogSignalInfo rt_LoggedStateSignalInfo = { 23 ,
rt_LoggedStateWidths , rt_LoggedStateNumDimensions , rt_LoggedStateDimensions
, rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 23 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . ajbbq1g4g5 ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . bhyqlswbyd ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . n4rivhzg4g ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) rtDW . feyvwig01o ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtDW . myljyfih4p ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtDW . dumfjgwxhc ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) rtDW . laliiofkj3 ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtDW . nrjeu0zetd ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . fqos0o4h34 ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) rtDW . mku35wrylx ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtDW . ko2zssnvqw ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtDW . d5k240dd1f ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtDW . bnlws2sh1t ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtDW . o5hyij1dzr ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtDW . eckossjxt3 ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtDW . n0gerj2i33 ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) & rtDW . bjfytdftqo ;
rt_LoggedStateSignalPtrs [ 17 ] = ( void * ) & rtDW . n3gfvygdda ;
rt_LoggedStateSignalPtrs [ 18 ] = ( void * ) & rtDW . apwo5tufnb ;
rt_LoggedStateSignalPtrs [ 19 ] = ( void * ) & rtDW . kurctjxgfu ;
rt_LoggedStateSignalPtrs [ 20 ] = ( void * ) & rtDW . gygqelpgtp ;
rt_LoggedStateSignalPtrs [ 21 ] = ( void * ) & rtDW . f3whwvtp2b ;
rt_LoggedStateSignalPtrs [ 22 ] = ( void * ) & rtDW . ld5rza5xa5 ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"xFinal" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 2 ] ;
static real_T absTol [ 2 ] = { 1.0E-6 , 1.0E-6 } ; static uint8_T
absTolControl [ 2 ] = { 0U , 0U } ; static real_T
contStateJacPerturbBoundMinVec [ 2 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 2 ] ; static uint8_T zcAttributes [ 1 ] = {
( ZC_EVENT_ALL ) } ; static ssNonContDerivSigInfo nonContDerivSigInfo [ 1 ] =
{ { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . iyb4nnud3n ) , ( NULL ) } }
; { int i ; for ( i = 0 ; i < 2 ; ++ i ) { contStateJacPerturbBoundMinVec [ i
] = 0 ; contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } }
ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ;
ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ;
ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 1.9531E-9 )
; ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 0 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 1 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS
, 1 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol ) ; ssSetAbsTolControlVector (
rtS , absTolControl ) ; ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 1 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 1 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 2669508275U ) ; ssSetChecksumVal ( rtS , 1 ,
3852389557U ) ; ssSetChecksumVal ( rtS , 2 , 854899528U ) ; ssSetChecksumVal
( rtS , 3 , 2228287752U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 1 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_SigmaDelta2nd_GetSimStateDisallowedBlocks ) ; slsaGetWorkFcnForSimTargetOP
( rtS , mr_SigmaDelta2nd_GetDWork ) ; slsaSetWorkFcnForSimTargetOP ( rtS ,
mr_SigmaDelta2nd_SetDWork ) ; rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if
( ssGetErrorStatus ( rtS ) ) { return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = - 1 ; void MdlOutputsParameterSampleTime
( int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
