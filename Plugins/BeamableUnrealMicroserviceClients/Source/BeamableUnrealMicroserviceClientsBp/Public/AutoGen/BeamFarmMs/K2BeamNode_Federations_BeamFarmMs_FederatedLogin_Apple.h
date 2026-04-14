
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_BeamFarmMs_FederatedLogin_Apple.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_BeamFarmMs_FederatedLogin_Apple"

/**
* This is the code-gen'ed declaration for the federation: Federated Login - Apple (apple). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_BeamFarmMs_FederatedLoginData_Apple : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamFarmMs - Federated Login Data - Apple"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetFederatedLogin_Data_Apple); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamBeamFarmMsApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE