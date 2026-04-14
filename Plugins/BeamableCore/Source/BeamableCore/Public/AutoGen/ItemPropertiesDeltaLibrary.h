#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemPropertiesDelta.h"

#include "ItemPropertiesDeltaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemPropertiesDeltaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ItemPropertiesDelta To JSON String")
	static FString ItemPropertiesDeltaToJsonString(const UItemPropertiesDelta* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ItemPropertiesDelta", meta=(DefaultToSelf="Outer", AdvancedDisplay="Properties, Outer", NativeMakeFunc))
	static UItemPropertiesDelta* Make(FString ContentId, int64 ItemId, FOptionalMapOfPropertyDelta Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ItemPropertiesDelta", meta=(NativeBreakFunc))
	static void Break(const UItemPropertiesDelta* Serializable, FString& ContentId, int64& ItemId, FOptionalMapOfPropertyDelta& Properties);
};