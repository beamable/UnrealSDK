
#include "AutoGen/ArchiveProjectRequestBody.h"



void UArchiveProjectRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("pid"), Pid);
}

void UArchiveProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("pid"), Pid);		
}

void UArchiveProjectRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Pid = Bag->GetStringField(TEXT("pid"));
}