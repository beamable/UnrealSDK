
#include "BeamableCore/Public/AutoGen/EntitlementGenerator.h"
#include "Serialization/BeamJsonUtils.h"




void UEntitlementGenerator::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("action"), Action, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<UEntitlementClaimWindow*>(TEXT("claimWindow"), &ClaimWindow, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("params"), &Params, Serializer);
}

void UEntitlementGenerator::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("action"), Action, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<UEntitlementClaimWindow*>(TEXT("claimWindow"), &ClaimWindow, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("params"), &Params, Serializer);		
}

void UEntitlementGenerator::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("action")), Action);
	UBeamJsonUtils::DeserializeOptional<int32>("quantity", Bag, Quantity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEntitlementClaimWindow*>("claimWindow", Bag, ClaimWindow, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("params", Bag, Params, OuterOwner);
}



