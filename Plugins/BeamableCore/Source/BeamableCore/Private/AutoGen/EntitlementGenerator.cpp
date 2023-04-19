
#include "BeamableCore/Public/AutoGen/EntitlementGenerator.h"
#include "Serialization/BeamJsonUtils.h"




void UEntitlementGenerator::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("action"), Action);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<UEntitlementClaimWindow*>(TEXT("claimWindow"), &ClaimWindow, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("params"), &Params, Serializer);
}

void UEntitlementGenerator::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("action"), Action);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<UEntitlementClaimWindow*>(TEXT("claimWindow"), &ClaimWindow, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("params"), &Params, Serializer);		
}

void UEntitlementGenerator::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Action = Bag->GetStringField(TEXT("action"));
	UBeamJsonUtils::DeserializeOptional<int32>("quantity", Bag, Quantity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEntitlementClaimWindow*>("claimWindow", Bag, ClaimWindow, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("params", Bag, Params, OuterOwner);
}



