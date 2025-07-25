
#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetTemplatesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetTemplatesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceTemplate*>(TEXT("templates"), Templates, Serializer);
}

void UGetTemplatesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceTemplate*>(TEXT("templates"), Templates, Serializer);		
}

void UGetTemplatesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServiceTemplate*>(Bag->GetArrayField(TEXT("templates")), Templates, OuterOwner);
}



