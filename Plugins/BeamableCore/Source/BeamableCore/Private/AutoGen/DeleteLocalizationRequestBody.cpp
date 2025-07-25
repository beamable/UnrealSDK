
#include "BeamableCore/Public/AutoGen/DeleteLocalizationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDeleteLocalizationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULocalizationQuery*>(TEXT("localizations"), Localizations, Serializer);
}

void UDeleteLocalizationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULocalizationQuery*>(TEXT("localizations"), Localizations, Serializer);		
}

void UDeleteLocalizationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<ULocalizationQuery*>(TEXT("localizations"), Bag, Localizations, OuterOwner);
}



