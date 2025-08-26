
#include "BeamableCore/Public/AutoGen/Listing.h"
#include "Serialization/BeamJsonUtils.h"




void UListing::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offerSymbol"), OfferSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offerSymbol"), OfferSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("offerSymbol"), Bag, OfferSymbol);
	UBeamJsonUtils::DeserializeUObject<UPrice*>("price", Bag, Price, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeArray<UCohortRequirement*>(TEXT("cohortRequirements"), Bag, CohortRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPlayerStatRequirement*>(TEXT("playerStatRequirements"), Bag, PlayerStatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEntitlementRequirement*>(TEXT("entitlementRequirements"), Bag, EntitlementRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UOfferRequirement*>(TEXT("offerRequirements"), Bag, OfferRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("clientData"), Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("purchaseLimit", Bag, PurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("scheduleInstancePurchaseLimit", Bag, ScheduleInstancePurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USchedule*>("schedule", Bag, Schedule, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationCoolDownSeconds", Bag, ActiveDurationCoolDownSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationSeconds", Bag, ActiveDurationSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeDurationPurchaseLimit", Bag, ActiveDurationPurchaseLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPeriod*>("activePeriod", Bag, ActivePeriod, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("buttonText", Bag, ButtonText, OuterOwner);
}



