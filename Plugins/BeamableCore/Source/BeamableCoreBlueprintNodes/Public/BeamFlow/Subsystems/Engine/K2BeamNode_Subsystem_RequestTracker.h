#pragma once

#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "K2BeamNode_Subsystem_RequestTracker.generated.h"

/***
 *      ______                          _         
 *     |  ____|                        | |        
 *     | |__    __   __   ___   _ __   | |_   ___ 
 *     |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
 *     | |____   \ V /  |  __/ | | | | | |_  \__ \
 *     |______|   \_/    \___| |_| |_|  \__| |___/
 *                                                
 *                                                
 */




/***
 *  _                    _      ____  _        _       
 * | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
 * | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
 * | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
 * |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|
 * 
 */



#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_BeginOperation"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_BeginOperation : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - BeginOperation"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, BeginOperation); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_AddRequestToOperation"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_AddRequestToOperation : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - AddRequestToOperation"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, BP_AddRequestToOperation); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationSuccess"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationSuccess : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationSuccess"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationSuccess); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationError"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationError : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationError"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationError); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationCancelled"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationCancelled : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationCancelled"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationCancelled); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationSuccessWithData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationSuccessWithData : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationSuccessWithData"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationSuccessWithData); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationErrorWithData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationErrorWithData : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationErrorWithData"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationErrorWithData); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationCancelledWithData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationCancelledWithData : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationCancelledWithData"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationCancelledWithData); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationEvent"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationEvent : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationEvent"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationEvent); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TriggerOperationEventWithData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TriggerOperationEventWithData : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TriggerOperationEventWithData"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TriggerOperationEventWithData); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationEvents"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationEvents : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationEvents"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationEvents); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationSuccesses"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationSuccesses : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationSuccesses"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationSuccesses); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationErrors"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationErrors : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationErrors"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationErrors); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationCancelations"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationCancelations : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationCancelations"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationCancelations); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationSuccessesWithId"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationSuccessesWithId : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationSuccessesWithId"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationSuccessesWithId); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationErrorsWithId"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationErrorsWithId : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationErrorsWithId"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationErrorsWithId); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationCancelationsWithId"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationCancelationsWithId : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationCancelationsWithId"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationCancelationsWithId); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetOperationResult"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetOperationResult : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - TryGetOperationResult"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TryGetOperationResult); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsOperationActive"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsOperationActive : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - IsOperationActive"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, IsOperationActive); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsWaitSuccessful"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsWaitSuccessful : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - IsWaitSuccessful"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, IsWaitSuccessful); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsWaitFailed"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsWaitFailed : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - IsWaitFailed"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, IsWaitFailed); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsAnyWaitCancelled"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsAnyWaitCancelled : public UK2BeamNode_GetLocalState
{
 GENERATED_BODY()

 virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - RequestTracker - IsAnyWaitCancelled"); }

 virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf); }

 virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, IsAnyWaitCancelled); }

 virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRequestTracker::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE



/***
 *   ___                       _   _                 
 *  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
 * | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
 * | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
 *  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
 *       |_|     
 */
