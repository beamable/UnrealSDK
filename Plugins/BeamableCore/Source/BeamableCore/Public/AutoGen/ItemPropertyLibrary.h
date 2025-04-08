#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemProperty.h"

#include "ItemPropertyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ItemProperty To JSON String")
	static FString ItemPropertyToJsonString(const UItemProperty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ItemProperty", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemProperty* Make(FString Name, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break ItemProperty", meta=(NativeBreakFunc))
	static void Break(const UItemProperty* Serializable, FString& Name, FString& Value);
};