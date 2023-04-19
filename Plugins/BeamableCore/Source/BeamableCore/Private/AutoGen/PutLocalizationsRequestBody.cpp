
#include "BeamableCore/Public/AutoGen/PutLocalizationsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPutLocalizationsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FArrayOfLocalizedValue>(TEXT("localizations"), Localizations, Serializer);
}

void UPutLocalizationsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FArrayOfLocalizedValue>(TEXT("localizations"), Localizations, Serializer);		
}

void UPutLocalizationsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FArrayOfLocalizedValue>(Bag->GetObjectField(TEXT("localizations")), Localizations, OuterOwner);
}



