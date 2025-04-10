#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemContentResponse.h"

#include "ItemContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ItemContentResponse To JSON String")
	static FString ItemContentResponseToJsonString(const UItemContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ItemContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemContentResponse* Make(TArray<UItemArchetype*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ItemContentResponse", meta=(NativeBreakFunc))
	static void Break(const UItemContentResponse* Serializable, TArray<UItemArchetype*>& Content);
};