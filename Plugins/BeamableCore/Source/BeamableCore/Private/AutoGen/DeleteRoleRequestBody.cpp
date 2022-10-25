
#include "AutoGen/DeleteRoleRequestBody.h"



void UDeleteRoleRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("realm"), Realm);
	Serializer->WriteValue(TEXT("role"), Role);
}

void UDeleteRoleRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("realm"), Realm);
	Serializer->WriteValue(TEXT("role"), Role);		
}

void UDeleteRoleRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Realm = Bag->GetStringField(TEXT("realm"));
	Role = Bag->GetStringField(TEXT("role"));
}