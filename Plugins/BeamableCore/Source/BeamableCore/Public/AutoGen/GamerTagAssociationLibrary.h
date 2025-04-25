#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GamerTagAssociation.h"

#include "GamerTagAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGamerTagAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="GamerTagAssociation To JSON String")
	static FString GamerTagAssociationToJsonString(const UGamerTagAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GamerTagAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGamerTagAssociation* Make(FBeamPid ProjectId, FBeamGamerTag GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break GamerTagAssociation", meta=(NativeBreakFunc))
	static void Break(const UGamerTagAssociation* Serializable, FBeamPid& ProjectId, FBeamGamerTag& GamerTag);
};