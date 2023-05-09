#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#include "GetActiveOffersResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetActiveOffersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetActiveOffersResponse To JSON String")
	static FString GetActiveOffersResponseToJsonString(const UGetActiveOffersResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetActiveOffersResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetActiveOffersResponse* Make(TArray<UPlayerStoreView*> Stores, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetActiveOffersResponse", meta=(NativeBreakFunc))
	static void Break(const UGetActiveOffersResponse* Serializable, TArray<UPlayerStoreView*>& Stores);
};