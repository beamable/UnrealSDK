
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_BeamballMs_FederatedLogin_Eos.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_BeamballMs_FederatedLogin_Eos"

/**
* This is the code-gen'ed declaration for the federation: Federated Login - Eos (eos). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_BeamballMs_FederatedLoginData_Eos : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamballMs - Federated Login Data - Eos"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetFederatedLogin_Data_Eos); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamBeamballMsApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE