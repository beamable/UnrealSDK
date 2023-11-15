
#include "BeamableCore/Public/AutoGen/GamerTag.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGamerTag::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tag"), Tag);
	Serializer->WriteValue(TEXT("platform"), Platform);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("added"), &Added, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionUser*>(TEXT("user"), &User, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCohortEntry*>, UCohortEntry*>(TEXT("trials"), &Trials, Serializer);
}

void UGamerTag::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tag"), Tag);
	Serializer->WriteValue(TEXT("platform"), Platform);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("added"), &Added, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionUser*>(TEXT("user"), &User, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCohortEntry*>, UCohortEntry*>(TEXT("trials"), &Trials, Serializer);		
}

void UGamerTag::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("tag")), Tag);
	Platform = Bag->GetStringField(TEXT("platform"));
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("added", Bag, Added, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USessionUser*>("user", Bag, User, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCohortEntry*>, UCohortEntry*>("trials", Bag, Trials, OuterOwner);
}



