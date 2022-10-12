
#include "AutoGen/Project.h"
#include "Serialization/BeamJsonUtils.h"


void UProject ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("displayName"), &DisplayName, Serializer);
	Serializer->WriteValue(TEXT("secret"), Secret);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("customCharts"), CustomCharts, Serializer);
	Serializer->WriteValue(TEXT("root"), bRoot);
	Serializer->WriteValue(TEXT("archived"), bArchived);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sigval"), &bSigval, Serializer);
	Serializer->WriteValue(TEXT("plan"), Plan);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UProject::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("displayName"), &DisplayName, Serializer);
	Serializer->WriteValue(TEXT("secret"), Secret);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("customCharts"), CustomCharts, Serializer);
	Serializer->WriteValue(TEXT("root"), bRoot);
	Serializer->WriteValue(TEXT("archived"), bArchived);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sigval"), &bSigval, Serializer);
	Serializer->WriteValue(TEXT("plan"), Plan);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UProject ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("displayName", Bag, DisplayName, OuterOwner);
	Secret = Bag->GetStringField(TEXT("secret"));
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("children", Bag, Children, OuterOwner);
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("customCharts")), CustomCharts, OuterOwner);
	bRoot = Bag->GetBoolField(TEXT("root"));
	bArchived = Bag->GetBoolField(TEXT("archived"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("config", Bag, Config, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sigval", Bag, bSigval, OuterOwner);
	Plan = Bag->GetStringField(TEXT("plan"));
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}