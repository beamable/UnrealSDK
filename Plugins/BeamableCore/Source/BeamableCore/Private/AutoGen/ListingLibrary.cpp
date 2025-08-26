
#include "BeamableCore/Public/AutoGen/ListingLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListingLibrary::ListingToJsonString(const UListing* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UListing* UListingLibrary::Make(FString OfferSymbol, UPrice* Price, FString Symbol, TArray<UCohortRequirement*> CohortRequirements, TArray<UPlayerStatRequirement*> PlayerStatRequirements, TArray<UEntitlementRequirement*> EntitlementRequirements, TArray<UOfferRequirement*> OfferRequirements, TMap<FString, FString> ClientData, FOptionalInt32 PurchaseLimit, FOptionalInt32 ScheduleInstancePurchaseLimit, FOptionalSchedule Schedule, FOptionalInt32 ActiveDurationCoolDownSeconds, FOptionalInt32 ActiveDurationSeconds, FOptionalInt32 ActiveDurationPurchaseLimit, FOptionalPeriod ActivePeriod, FOptionalMapOfString ButtonText, UObject* Outer)
{
	auto Serializable = NewObject<UListing>(Outer);
	Serializable->OfferSymbol = OfferSymbol;
	Serializable->Price = Price;
	Serializable->Symbol = Symbol;
	Serializable->CohortRequirements = CohortRequirements;
	Serializable->PlayerStatRequirements = PlayerStatRequirements;
	Serializable->EntitlementRequirements = EntitlementRequirements;
	Serializable->OfferRequirements = OfferRequirements;
	Serializable->ClientData = ClientData;
	Serializable->PurchaseLimit = PurchaseLimit;
	Serializable->ScheduleInstancePurchaseLimit = ScheduleInstancePurchaseLimit;
	Serializable->Schedule = Schedule;
	Serializable->ActiveDurationCoolDownSeconds = ActiveDurationCoolDownSeconds;
	Serializable->ActiveDurationSeconds = ActiveDurationSeconds;
	Serializable->ActiveDurationPurchaseLimit = ActiveDurationPurchaseLimit;
	Serializable->ActivePeriod = ActivePeriod;
	Serializable->ButtonText = ButtonText;
	
	return Serializable;
}

void UListingLibrary::Break(const UListing* Serializable, FString& OfferSymbol, UPrice*& Price, FString& Symbol, TArray<UCohortRequirement*>& CohortRequirements, TArray<UPlayerStatRequirement*>& PlayerStatRequirements, TArray<UEntitlementRequirement*>& EntitlementRequirements, TArray<UOfferRequirement*>& OfferRequirements, TMap<FString, FString>& ClientData, FOptionalInt32& PurchaseLimit, FOptionalInt32& ScheduleInstancePurchaseLimit, FOptionalSchedule& Schedule, FOptionalInt32& ActiveDurationCoolDownSeconds, FOptionalInt32& ActiveDurationSeconds, FOptionalInt32& ActiveDurationPurchaseLimit, FOptionalPeriod& ActivePeriod, FOptionalMapOfString& ButtonText)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OfferSymbol = Serializable->OfferSymbol;
		Price = Serializable->Price;
		Symbol = Serializable->Symbol;
		CohortRequirements = Serializable->CohortRequirements;
		PlayerStatRequirements = Serializable->PlayerStatRequirements;
		EntitlementRequirements = Serializable->EntitlementRequirements;
		OfferRequirements = Serializable->OfferRequirements;
		ClientData = Serializable->ClientData;
		PurchaseLimit = Serializable->PurchaseLimit;
		ScheduleInstancePurchaseLimit = Serializable->ScheduleInstancePurchaseLimit;
		Schedule = Serializable->Schedule;
		ActiveDurationCoolDownSeconds = Serializable->ActiveDurationCoolDownSeconds;
		ActiveDurationSeconds = Serializable->ActiveDurationSeconds;
		ActiveDurationPurchaseLimit = Serializable->ActiveDurationPurchaseLimit;
		ActivePeriod = Serializable->ActivePeriod;
		ButtonText = Serializable->ButtonText;
	}
		
}

