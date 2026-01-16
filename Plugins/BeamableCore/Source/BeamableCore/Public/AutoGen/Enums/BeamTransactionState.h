#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamTransactionState.generated.h"

UENUM(BlueprintType, Category="Beam|Payment|Utils|Enums")
enum class EBeamTransactionState : uint8
{
	BEAM_STARTED UMETA(DisplayName="STARTED"),
	BEAM_VERIFIED UMETA(DisplayName="VERIFIED"),
	BEAM_PROVISIONED UMETA(DisplayName="PROVISIONED"),
	BEAM_COMPLETED UMETA(DisplayName="COMPLETED"),
	BEAM_CANCELLED UMETA(DisplayName="CANCELLED"),
	BEAM_PENDING UMETA(DisplayName="PENDING"),
	BEAM_FAILED UMETA(DisplayName="FAILED"),
	BEAM_DISPUTED UMETA(DisplayName="DISPUTED"),
	BEAM_RESOLVED UMETA(DisplayName="RESOLVED"),
	BEAM_CLIENT_ISSUE UMETA(DisplayName="CLIENT_ISSUE")		
};
