#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamFederationType.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamFederationType : uint8
{
	BEAM_IFederatedLogin UMETA(DisplayName="I Federated Login"),
	BEAM_IFederatedInventory UMETA(DisplayName="I Federated Inventory"),
	BEAM_IFederatedCommerce UMETA(DisplayName="I Federated Commerce"),
	BEAM_IFederatedGameServer UMETA(DisplayName="I Federated Game Server"),
	BEAM_IFederatedPlayerInit UMETA(DisplayName="I Federated Player Init")		
};
