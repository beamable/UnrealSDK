
#include "BeamableCore/Public/AutoGen/Listing.h"
#include "Serialization/BeamJsonUtils.h"




void UListing::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UCohortRequirement*>(TEXT("cohortRequirements"), CohortRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("playerStatRequirements"), PlayerStatRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementRequirement*>(TEXT("entitlementRequirements"), EntitlementRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferRequirement*>(TEXT("offerRequirements"), OfferRequirements, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchaseLimit"), &PurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("scheduleInstancePurchaseLimit"), &ScheduleInstancePurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationCoolDownSeconds"), &ActiveDurationCoolDownSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationSeconds"), &ActiveDurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationPurchaseLimit"), &ActiveDurationPurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<UPeriod*>(TEXT("activePeriod"), &ActivePeriod, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("buttonText"), &ButtonText, Serializer);
}

void UListing::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UCohortRequirement*>(TEXT("cohortRequirements"), CohortRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("playerStatRequirements"), PlayerStatRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementRequirement*>(TEXT("entitlementRequirements"), EntitlementRequirements, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferRequirement*>(TEXT("offerRequirements"), OfferRequirements, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchaseLimit"), &PurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("scheduleInstancePurchaseLimit"), &ScheduleInstancePurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationCoolDownSeconds"), &ActiveDurationCoolDownSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationSeconds"), &ActiveDurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeDurationPurchaseLimit"), &ActiveDurationPurchaseLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<UPeriod*>(TEXT("activePeriod"), &ActivePeriod, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("buttonText"), &ButtonText, Serializer);		
}

void UListing::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	OfferSymbol = Bag->GetStringField(TEXT("offerSymbol"));
	UBeamJsonUtils::DeserializeUObject<UPrice*>("price", Bag, Price, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeArray<UCohortRequirement*>(Bag->GetArrayField(TEXT("cohortRequirements")), CohortRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerStatRequirement*>(Bag->GetArrayField(TEXT("playerStatRequirements")), PlayerStatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEntitlementRequirement*>(Bag->GetArrayField(TEXT("entitlementRequirements")), EntitlementRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UOfferRequirement*>(Bag->GetArrayField(TEXT("offerRequirements")), OfferRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("clientData")), ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("purchaseLimit", Bag, PurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("scheduleInstancePurchaseLimit", Bag, ScheduleInstancePurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USchedule*>("schedule", Bag, Schedule, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationCoolDownSeconds", Bag, ActiveDurationCoolDownSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationSeconds", Bag, ActiveDurationSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationPurchaseLimit", Bag, ActiveDurationPurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPeriod*>("activePeriod", Bag, ActivePeriod, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("buttonText", Bag, ButtonText, OuterOwner);
}



