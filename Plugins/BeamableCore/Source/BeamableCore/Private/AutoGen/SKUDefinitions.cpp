
#include "BeamableCore/Public/AutoGen/SKUDefinitions.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USKUDefinitions::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);
}

void USKUDefinitions::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<USKU*>(TEXT("definitions"), Definitions, Serializer);		
}

void USKUDefinitions::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("version")), Version);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<USKU*>(Bag->GetArrayField(TEXT("definitions")), Definitions, OuterOwner);
}



