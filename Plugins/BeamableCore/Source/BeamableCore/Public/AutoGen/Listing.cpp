
#include "AutoGen/Listing.h"
#include "Serialization/BeamJsonUtils.h"


void UListing ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCohortRequirement*>(TEXT("cohortRequirements"), CohortRequirements, Serializer);
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchaseLimit"), &PurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("playerStatRequirements"), PlayerStatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("buttonText"), &ButtonText, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("scheduleInstancePurchaseLimit"), &ScheduleInstancePurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementRequirement*>(TEXT("entitlementRequirements"), EntitlementRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationCoolDownSeconds"), &ActiveDurationCoolDownSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationSeconds"), &ActiveDurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationPurchaseLimit"), &ActiveDurationPurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferRequirement*>(TEXT("offerRequirements"), OfferRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<UPeriod*>(TEXT("activePeriod"), &ActivePeriod, Serializer);
}

void UListing::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCohortRequirement*>(TEXT("cohortRequirements"), CohortRequirements, Serializer);
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchaseLimit"), &PurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("playerStatRequirements"), PlayerStatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("buttonText"), &ButtonText, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("scheduleInstancePurchaseLimit"), &ScheduleInstancePurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementRequirement*>(TEXT("entitlementRequirements"), EntitlementRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationCoolDownSeconds"), &ActiveDurationCoolDownSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationSeconds"), &ActiveDurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationPurchaseLimit"), &ActiveDurationPurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferRequirement*>(TEXT("offerRequirements"), OfferRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<UPeriod*>(TEXT("activePeriod"), &ActivePeriod, Serializer);		
}

void UListing ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCohortRequirement*>(Bag->GetArrayField(TEXT("cohortRequirements")), CohortRequirements, OuterOwner);
	OfferSymbol = Bag->GetStringField(TEXT("offerSymbol"));
	UBeamJsonUtils::DeserializeOptional<int32>("purchaseLimit", Bag, PurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UPrice*>("price", Bag, Price, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerStatRequirement*>(Bag->GetArrayField(TEXT("playerStatRequirements")), PlayerStatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("buttonText", Bag, ButtonText, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("scheduleInstancePurchaseLimit", Bag, ScheduleInstancePurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEntitlementRequirement*>(Bag->GetArrayField(TEXT("entitlementRequirements")), EntitlementRequirements, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("clientData")), ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USchedule*>("schedule", Bag, Schedule, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationCoolDownSeconds", Bag, ActiveDurationCoolDownSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationSeconds", Bag, ActiveDurationSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationPurchaseLimit", Bag, ActiveDurationPurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UOfferRequirement*>(Bag->GetArrayField(TEXT("offerRequirements")), OfferRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPeriod*>("activePeriod", Bag, ActivePeriod, OuterOwner);
}