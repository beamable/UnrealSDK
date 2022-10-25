
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/GamerTagAssociation.h"

#include "GamerTagAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGamerTagAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GamerTagAssociation To JSON String")
	static FString GamerTagAssociationToJsonString(const UGamerTagAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GamerTagAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGamerTagAssociation* Make(FString ProjectId, int64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GamerTagAssociation", meta=(NativeBreakFunc))
	static void Break(const UGamerTagAssociation* Serializable, FString& ProjectId, int64& GamerTag);
};