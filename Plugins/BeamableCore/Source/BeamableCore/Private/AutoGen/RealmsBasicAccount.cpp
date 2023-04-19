
#include "BeamableCore/Public/AutoGen/RealmsBasicAccount.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicAccount::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("user"), User);
	Serializer->WriteValue(TEXT("password"), Password);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void URealmsBasicAccount::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("user"), User);
	Serializer->WriteValue(TEXT("password"), Password);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("projects"), Projects, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void URealmsBasicAccount::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	User = Bag->GetStringField(TEXT("user"));
	Password = Bag->GetStringField(TEXT("password"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("projects")), Projects, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}



