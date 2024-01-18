#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "SigmaDelta2nd_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#else
#include "builtin_typeid_types.h"
#include "SigmaDelta2nd.h"
#include "SigmaDelta2nd_capi.h"
#include "SigmaDelta2nd_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"SigmaDelta2nd/Gain" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0
, TARGET_STRING ( "SigmaDelta2nd/Gain1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 2 , 0 , TARGET_STRING ( "SigmaDelta2nd/Gain2" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 3 , 0 , TARGET_STRING (
"SigmaDelta2nd/Gain3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 4 ,
0 , TARGET_STRING ( "SigmaDelta2nd/Integrator" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 0 } , { 5 , 0 , TARGET_STRING ( "SigmaDelta2nd/Integrator1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 6 , 0 , TARGET_STRING (
"SigmaDelta2nd/Product" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 7
, 0 , TARGET_STRING ( "SigmaDelta2nd/FIR Decimation to 128 MHz" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"SigmaDelta2nd/FIR Decimation to 32 MHz" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 2 } , { 9 , 0 , TARGET_STRING ( "SigmaDelta2nd/FIR Decimation to 8 MHz"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 10 , 0 , TARGET_STRING (
"SigmaDelta2nd/Sign" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 11 ,
0 , TARGET_STRING ( "SigmaDelta2nd/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 12 , 0 , TARGET_STRING ( "SigmaDelta2nd/Sum1" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 13 , 0 , TARGET_STRING (
"SigmaDelta2nd/Transport Delay" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0
} , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 14 , TARGET_STRING (
"SigmaDelta2nd/Gain" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 15 ,
TARGET_STRING ( "SigmaDelta2nd/Gain1" ) , TARGET_STRING ( "Gain" ) , 0 , 0 ,
0 } , { 16 , TARGET_STRING ( "SigmaDelta2nd/Gain2" ) , TARGET_STRING ( "Gain"
) , 0 , 0 , 0 } , { 17 , TARGET_STRING ( "SigmaDelta2nd/Gain3" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 18 , TARGET_STRING (
"SigmaDelta2nd/Integrator" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 ,
0 } , { 19 , TARGET_STRING ( "SigmaDelta2nd/Integrator1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 20 , TARGET_STRING (
"SigmaDelta2nd/FIR Decimation to 128 MHz" ) , TARGET_STRING ( "FILT" ) , 0 ,
1 , 0 } , { 21 , TARGET_STRING ( "SigmaDelta2nd/FIR Decimation to 32 MHz" ) ,
TARGET_STRING ( "FILT" ) , 0 , 1 , 0 } , { 22 , TARGET_STRING (
"SigmaDelta2nd/FIR Decimation to 8 MHz" ) , TARGET_STRING ( "FILT" ) , 0 , 1
, 0 } , { 23 , TARGET_STRING ( "SigmaDelta2nd/Carrier" ) , TARGET_STRING (
"Amplitude" ) , 0 , 0 , 0 } , { 24 , TARGET_STRING ( "SigmaDelta2nd/Carrier"
) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 25 , TARGET_STRING (
"SigmaDelta2nd/Carrier" ) , TARGET_STRING ( "Frequency" ) , 0 , 0 , 0 } , {
26 , TARGET_STRING ( "SigmaDelta2nd/Carrier" ) , TARGET_STRING ( "Phase" ) ,
0 , 0 , 0 } , { 27 , TARGET_STRING ( "SigmaDelta2nd/Modulated" ) ,
TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING (
"SigmaDelta2nd/Modulated" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 } , { 29 ,
TARGET_STRING ( "SigmaDelta2nd/Modulated" ) , TARGET_STRING ( "Frequency" ) ,
0 , 0 , 0 } , { 30 , TARGET_STRING ( "SigmaDelta2nd/Modulated" ) ,
TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 31 , TARGET_STRING (
"SigmaDelta2nd/Transport Delay" ) , TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0
} , { 32 , TARGET_STRING ( "SigmaDelta2nd/Transport Delay" ) , TARGET_STRING
( "InitialOutput" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } }
; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0
} } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . bhb2jtlude , & rtB . aiuvh1nbjv ,
& rtB . cyljhahbp4 , & rtB . nwvay2kmxd , & rtB . lu0v52hhki , & rtB .
mrrqtpofed , & rtB . lqvljim52a , & rtB . fglzwg0gpe , & rtB . dbb1z0mm3j , &
rtB . dblm24swqm , & rtB . iyb4nnud3n , & rtB . koecjb54sh , & rtB .
e4dbl2cfl3 , & rtB . cecrguin1q , & rtP . Gain_Gain , & rtP . Gain1_Gain , &
rtP . Gain2_Gain , & rtP . Gain3_Gain , & rtP . Integrator_IC , & rtP .
Integrator1_IC , & rtP . FIRDecimationto128MHz_FILT [ 0 ] , & rtP .
FIRDecimationto32MHz_FILT [ 0 ] , & rtP . FIRDecimationto8MHz_FILT [ 0 ] , &
rtP . Carrier_Amp , & rtP . Carrier_Bias , & rtP . Carrier_Freq , & rtP .
Carrier_Phase , & rtP . Modulated_Amp , & rtP . Modulated_Bias , & rtP .
Modulated_Freq , & rtP . Modulated_Phase , & rtP . TransportDelay_Delay , &
rtP . TransportDelay_InitOutput , } ; static int32_T * rtVarDimsAddrMap [ ] =
{ ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } }
;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 2 , 2 , 0 } } ;
static const uint_T rtDimensionArray [ ] = { 1 , 1 , 24 , 4 } ; static const
real_T rtcapiStoredFloats [ ] = { 0.0 , 7.8124E-9 , 3.12496E-8 , 1.249984E-7
, 1.0 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , (
NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , (
int8_T ) 0 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ]
, ( const void * ) & rtcapiStoredFloats [ 0 ] , ( int8_T ) 3 , ( uint8_T ) 0
} , { ( const void * ) & rtcapiStoredFloats [ 2 ] , ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( int8_T ) 4 , ( uint8_T ) 0 } , { ( const void *
) & rtcapiStoredFloats [ 3 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] ,
( int8_T ) 5 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 0
] , ( const void * ) & rtcapiStoredFloats [ 4 ] , ( int8_T ) 1 , ( uint8_T )
0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals
, 14 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 19 ,
rtModelParameters , 0 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 2669508275U , 3852389557U , 854899528U , 2228287752U } , ( NULL ) , 0 , (
boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * SigmaDelta2nd_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void SigmaDelta2nd_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void SigmaDelta2nd_host_InitializeDataMapInfo (
SigmaDelta2nd_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
