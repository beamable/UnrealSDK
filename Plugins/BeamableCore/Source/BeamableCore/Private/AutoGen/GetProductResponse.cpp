
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "Misc/DefaultValueHelper.h"


void UGetProductResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetProductResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("price"), Price);
}

void UGetProductResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("price"), Price);		
}

void UGetProductResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	Name = Bag->GetStringField(TEXT("name"));
	Description = Bag->GetStringField(TEXT("description"));
	Price = Bag->GetIntegerField(TEXT("price"));
}



