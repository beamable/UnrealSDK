#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountSearchResponse.h"

#include "AccountSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AccountSearchResponse To JSON String")
	static FString AccountSearchResponseToJsonString(const UAccountSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AccountSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountSearchResponse* Make(TArray<UAccountsBasicAccount*> Accounts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AccountSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UAccountSearchResponse* Serializable, TArray<UAccountsBasicAccount*>& Accounts);
};