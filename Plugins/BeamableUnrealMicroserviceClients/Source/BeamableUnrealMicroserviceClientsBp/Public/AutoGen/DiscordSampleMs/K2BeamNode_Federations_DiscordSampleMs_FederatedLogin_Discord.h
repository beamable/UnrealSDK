
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamDiscordSampleMsApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_DiscordSampleMs_FederatedLogin_Discord.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_DiscordSampleMs_FederatedLogin_Discord"

/**
* This is the code-gen'ed declaration for the federation: Federated Login - Discord (discord). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_DiscordSampleMs_FederatedLoginData_Discord : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - DiscordSampleMs - Federated Login Data - Discord"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, GetFederatedLogin_Data_Discord); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamDiscordSampleMsApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE