#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Store.h"

#include "StoreLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="Store To JSON String")
	static FString StoreToJsonString(const UStore* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make Store", meta=(DefaultToSelf="Outer", AdvancedDisplay="bShowInactiveListings, ActiveListingLimit, Choose, RefreshTime, Title, Outer", NativeMakeFunc))
	static UStore* Make(FString Symbol, TArray<UListing*> Listings, FOptionalBool bShowInactiveListings, FOptionalInt32 ActiveListingLimit, FOptionalInt32 Choose, FOptionalInt32 RefreshTime, FOptionalString Title, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break Store", meta=(NativeBreakFunc))
	static void Break(const UStore* Serializable, FString& Symbol, TArray<UListing*>& Listings, FOptionalBool& bShowInactiveListings, FOptionalInt32& ActiveListingLimit, FOptionalInt32& Choose, FOptionalInt32& RefreshTime, FOptionalString& Title);
};