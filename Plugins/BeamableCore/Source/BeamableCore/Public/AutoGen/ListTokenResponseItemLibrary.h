#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTokenResponseItem.h"

#include "ListTokenResponseItemLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTokenResponseItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ListTokenResponseItem To JSON String")
	static FString ListTokenResponseItemToJsonString(const UListTokenResponseItem* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ListTokenResponseItem", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListTokenResponseItem* Make(FString Token, FString Platform, FString Device, FString Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ListTokenResponseItem", meta=(NativeBreakFunc))
	static void Break(const UListTokenResponseItem* Serializable, FString& Token, FString& Platform, FString& Device, FString& Created);
};