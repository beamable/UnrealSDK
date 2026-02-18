
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Federations_BeamballMs_FederatedGameServer_Beamball.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_BeamballMs_FederatedGameServer_Beamball"

/**
* This is the code-gen'ed declaration for the federation: Federated Game Server - Beamball (beamball). 
*/
UCLASS(meta=(BeamGetLocalState))
class BEAMABLEUNREALMICROSERVICECLIENTSBP_API UK2BeamNode_BeamballMs_FederatedGameServerData_Beamball : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamballMs - Federated Game Server Data - Beamball"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetFederatedGameServer_Data_Beamball); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamBeamballMsApi::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE