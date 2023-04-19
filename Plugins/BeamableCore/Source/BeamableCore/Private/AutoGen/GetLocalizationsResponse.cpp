
#include "BeamableCore/Public/AutoGen/GetLocalizationsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetLocalizationsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetLocalizationsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FArrayOfLocalizedValue>(TEXT("localizations"), Localizations, Serializer);
}

void UGetLocalizationsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FArrayOfLocalizedValue>(TEXT("localizations"), Localizations, Serializer);		
}

void UGetLocalizationsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FArrayOfLocalizedValue>(Bag->GetObjectField(TEXT("localizations")), Localizations, OuterOwner);
}



