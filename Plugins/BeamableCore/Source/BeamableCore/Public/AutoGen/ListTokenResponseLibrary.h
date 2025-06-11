#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTokenResponse.h"

#include "ListTokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="ListTokenResponse To JSON String")
	static FString ListTokenResponseToJsonString(const UListTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ListTokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListTokenResponse* Make(TArray<UListTokenResponseItem*> Items, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break ListTokenResponse", meta=(NativeBreakFunc))
	static void Break(const UListTokenResponse* Serializable, TArray<UListTokenResponseItem*>& Items);
};