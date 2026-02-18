
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamSteamDemoApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_SteamDemo_FederatedLogin_Steam.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_SteamDemo_FederatedLogin_Steam"

/**
* This is the code-gen'ed declaration for the federation: Federated Login - Steam (steam). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_SteamDemo_FederatedLoginData_Steam : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - SteamDemo - Federated Login Data - Steam"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamSteamDemoApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamSteamDemoApi, GetFederatedLogin_Data_Steam); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamSteamDemoApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE