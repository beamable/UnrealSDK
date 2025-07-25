
#include "BeamableCore/Public/AutoGen/RealmsBasicAccount.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicAccount::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("user"), User, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void URealmsBasicAccount::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("user"), User, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void URealmsBasicAccount::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("user"), Bag, User);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("password"), Bag, Password);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("projects"), Bag, Projects, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



