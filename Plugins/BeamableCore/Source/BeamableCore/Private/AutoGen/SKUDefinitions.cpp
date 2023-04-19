
#include "BeamableCore/Public/AutoGen/SKUDefinitions.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USKUDefinitions::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("version"), Version);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);
}

void USKUDefinitions::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("version"), Version);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);		
}

void USKUDefinitions::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("version")), Version);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<USKU*>(Bag->GetArrayField(TEXT("definitions")), Definitions, OuterOwner);
}



