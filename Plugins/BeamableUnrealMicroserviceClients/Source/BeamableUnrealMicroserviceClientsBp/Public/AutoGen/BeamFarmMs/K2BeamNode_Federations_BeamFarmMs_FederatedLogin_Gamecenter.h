
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_BeamFarmMs_FederatedLogin_Gamecenter.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_BeamFarmMs_FederatedLogin_Gamecenter"

/**
* This is the code-gen'ed declaration for the federation: Federated Login - Gamecenter (gamecenter). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_BeamFarmMs_FederatedLoginData_Gamecenter : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamFarmMs - Federated Login Data - Gamecenter"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetFederatedLogin_Data_Gamecenter); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamBeamFarmMsApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE