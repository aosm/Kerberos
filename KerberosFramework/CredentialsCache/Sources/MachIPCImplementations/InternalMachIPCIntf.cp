#include <Kerberos/mach_server_utilities.h>

#include "CCache.MachIPC.h"
#include "MachIPCInterface.h"
#ifdef Classic_Ticket_Sharing
#  include "ClassicSupport.h"
#  include "ClassicProtocol.h"
#endif

extern "C" {
    #include "CCacheIPCServer.h"
};

// Function to quit the CCache Server for the login window plugin:
kern_return_t  InternalIPC_TellServerToQuit (
	mach_port_t inServerPort,
	CCIResult *outResult) 
{
    dprintf ("InternalIPC_TellServerToQuit: quitting server.\n");
    mach_server_quit_self ();
     
    *outResult = ccNoError;  
    return KERN_SUCCESS;
}

#ifdef Classic_Ticket_Sharing
// Returns recent changes made to the caches
kern_return_t	InternalIPC_GetDiffs (
	mach_port_t				inServerPort,
        CCIUInt32				inServerID,
	CCIUInt32				inSeqNo,
	CCacheDiffs*			outDiffs,
	mach_msg_type_number_t*	outDiffsCnt,
	CCIResult*				outResult)
{
    try {
        if ((inServerID != 0) && (inServerID != static_cast <CCIUInt32> (getpid ()))) {
            CCIDebugThrow_ (CCIException (ccErrServerUnavailable));
        }
        
        CCIClassicSupport::RemoveDiffsUpTo (inSeqNo);

        Handle		diffs = CCIClassicSupport::GetAllDiffsSince (inSeqNo);
        
        if (diffs != NULL) {
            
            CCIMachIPCServerBuffer <char>	buffer (GetHandleSize (diffs));
            
            BlockMoveData (*diffs, buffer.Data (), GetHandleSize (diffs));
            *outDiffs = buffer.Data ();
            *outDiffsCnt = buffer.Size ();
        } else {
            *outDiffs = NULL;
            *outDiffsCnt = 0;
        }
        *outResult = ccNoError;
    } CatchForIPCReturn_ (outResult)
    
    return KERN_SUCCESS;
}

kern_return_t	InternalIPC_FabricateInitialDiffs (
	mach_port_t				inServerPort,
        CCIUInt32				inServerID,
	CCacheDiffs*			outDiffs,
	mach_msg_type_number_t*	outDiffsCnt,
	CCIResult*				outResult)
{
    try {
        if ((inServerID != 0) && (inServerID != static_cast <CCIUInt32> (getpid ()))) {
            CCIDebugThrow_ (CCIException (ccErrServerUnavailable));
        }
        
        Handle diffs = CCIClassicSupport::FabricateDiffs ();
        CCIClassicSupport::RemoveAllDiffs ();

        if (diffs != NULL) {
            
            CCIMachIPCServerBuffer <char>	buffer (GetHandleSize (diffs));
            
            BlockMoveData (*diffs, buffer.Data (), GetHandleSize (diffs));
            *outDiffs = buffer.Data ();
            *outDiffsCnt = buffer.Size ();
        } else {
            *outDiffs = NULL;
            *outDiffsCnt = 0;
        }

        *outResult = ccNoError;
    } CatchForIPCReturn_ (outResult)
    
    return KERN_SUCCESS;
}

kern_return_t	InternalIPC_CheckServerID (
	mach_port_t				inServerPort,
        CCIUInt32				inServerID,
	CCIUInt32*				outCorrect,
	CCIResult*				outResult)
{
    try {
        if ((inServerID != 0) && (inServerID != static_cast <CCIUInt32> (getpid ()))) {
            *outCorrect = false;
            *outResult = ccNoError;
        } else {
            *outCorrect = true;
            *outResult = ccNoError;
        }
        
    } CatchForIPCReturn_ (outResult)
    
    return KERN_SUCCESS;
}
#endif

kern_return_t	InternalIPC_GetServerPID (mach_port_t inServerPort,
                                          CCIPID*     outPID,
                                          CCIResult*  outResult)
{
    try {
        *outPID = getpid ();
        *outResult = ccNoError;
    } CatchForIPCReturn_ (outResult)
    
    return KERN_SUCCESS;
}
