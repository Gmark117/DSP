#include "SigmaDelta2nd_capi_host.h"
static SigmaDelta2nd_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        SigmaDelta2nd_host_InitializeDataMapInfo(&(root), "SigmaDelta2nd");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}
