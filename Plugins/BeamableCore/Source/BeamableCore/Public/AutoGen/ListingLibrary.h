#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Listing.h"

#include "ListingLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="Listing To JSON String")
	static FString ListingToJsonString(const UListing* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make Listing", meta=(DefaultToSelf="Outer", AdvancedDisplay="PurchaseLimit, ScheduleInstancePurchaseLimit, Schedule, ActiveDurationCoolDownSeconds, ActiveDurationSeconds, ActiveDurationPurchaseLimit, ActivePeriod, ButtonText, Outer", NativeMakeFunc))
	static UListing* Make(FString OfferSymbol, UPrice* Price, FString Symbol, TArray<UCohortRequirement*> CohortRequirements, TArray<UPlayerStatRequirement*> PlayerStatRequirements, TArray<UEntitlementRequirement*> EntitlementRequirements, TArray<UOfferRequirement*> OfferRequirements, TMap<FString, FString> ClientData, FOptionalInt32 PurchaseLimit, FOptionalInt32 ScheduleInstancePurchaseLimit, FOptionalSchedule Schedule, FOptionalInt32 ActiveDurationCoolDownSeconds, FOptionalInt32 ActiveDurationSeconds, FOptionalInt32 ActiveDurationPurchaseLimit, FOptionalPeriod ActivePeriod, FOptionalMapOfString ButtonText, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break Listing", meta=(NativeBreakFunc))
	static void Break(const UListing* Serializable, FString& OfferSymbol, UPrice*& Price, FString& Symbol, TArray<UCohortRequirement*>& CohortRequirements, TArray<UPlayerStatRequirement*>& PlayerStatRequirements, TArray<UEntitlementRequirement*>& EntitlementRequirements, TArray<UOfferRequirement*>& OfferRequirements, TMap<FString, FString>& ClientData, FOptionalInt32& PurchaseLimit, FOptionalInt32& ScheduleInstancePurchaseLimit, FOptionalSchedule& Schedule, FOptionalInt32& ActiveDurationCoolDownSeconds, FOptionalInt32& ActiveDurationSeconds, FOptionalInt32& ActiveDurationPurchaseLimit, FOptionalPeriod& ActivePeriod, FOptionalMapOfString& ButtonText);
};