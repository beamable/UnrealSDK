
#include "BeamableCore/Public/AutoGen/SessionLanguageContextDto.h"
#include "Serialization/BeamJsonUtils.h"




void USessionLanguageContextDto::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("ctx"), &Ctx, Serializer);
}

void USessionLanguageContextDto::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("ctx"), &Ctx, Serializer);		
}

void USessionLanguageContextDto::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("code", Bag, Code, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("ctx", Bag, Ctx, OuterOwner);
}



