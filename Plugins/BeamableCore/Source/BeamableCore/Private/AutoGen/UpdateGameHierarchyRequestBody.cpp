
#include "AutoGen/UpdateGameHierarchyRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateGameHierarchyRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rootPID"), RootPID);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);
}

void UUpdateGameHierarchyRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rootPID"), RootPID);
	UBeamJsonUtils::SerializeArray<UProjectView*>(TEXT("projects"), Projects, Serializer);		
}

void UUpdateGameHierarchyRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RootPID = Bag->GetStringField(TEXT("rootPID"));
	UBeamJsonUtils::DeserializeArray<UProjectView*>(Bag->GetArrayField(TEXT("projects")), Projects, OuterOwner);
}