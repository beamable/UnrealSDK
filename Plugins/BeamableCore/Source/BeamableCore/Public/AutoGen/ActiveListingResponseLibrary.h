#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ActiveListingResponse.h"

#include "ActiveListingResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UActiveListingResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="ActiveListingResponse To JSON String")
	static FString ActiveListingResponseToJsonString(const UActiveListingResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make ActiveListingResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UActiveListingResponse* Make(FString StoreSymbol, UPlayerListingView* Listing, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break ActiveListingResponse", meta=(NativeBreakFunc))
	static void Break(const UActiveListingResponse* Serializable, FString& StoreSymbol, UPlayerListingView*& Listing);
};