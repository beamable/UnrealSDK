
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_LiveOpsDemoMS_FederatedPlayerInit_Default.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_LiveOpsDemoMS_FederatedPlayerInit_Default"

/**
* This is the code-gen'ed declaration for the federation: Federated Player Init - Default (default). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_LiveOpsDemoMS_FederatedPlayerInitData_Default : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - LiveOpsDemoMS - Federated Player Init Data - Default"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetFederatedPlayerInit_Data_Default); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLiveOpsDemoMSApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE