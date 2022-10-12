
#include "AutoGen/Item.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UItem ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("proxyId"), &ProxyId, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);
}

void UItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("proxyId"), &ProxyId, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdAt"), &CreatedAt, Serializer);		
}

void UItem ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("proxyId", Bag, ProxyId, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeArray<UItemProperty*>(Bag->GetArrayField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdAt", Bag, CreatedAt, OuterOwner);
}