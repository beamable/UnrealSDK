
#include "BeamableCore/Public/AutoGen/BaseContentReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBaseContentReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	const auto Type = GetCurrentType();
	if (Type.Equals(TEXT("content")))
		UBeamJsonUtils::SerializeUObject(Content, Serializer);
	if (Type.Equals(TEXT("text")))
		UBeamJsonUtils::SerializeUObject(Text, Serializer);
	if (Type.Equals(TEXT("binary")))
		UBeamJsonUtils::SerializeUObject(Binary, Serializer);
	
}

void UBaseContentReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	const auto Type = GetCurrentType();
	if (Type.Equals(TEXT("content")))
		UBeamJsonUtils::SerializeUObject(Content, Serializer);
	if (Type.Equals(TEXT("text")))
		UBeamJsonUtils::SerializeUObject(Text, Serializer);
	if (Type.Equals(TEXT("binary")))
		UBeamJsonUtils::SerializeUObject(Binary, Serializer);
			
}

void UBaseContentReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	const auto Type = Bag->GetStringField(TEXT("type"));
	if (Type.Equals(TEXT("content")))
		UBeamJsonUtils::DeserializeUObject(TEXT(""), Bag, Content, OuterOwner);
	if (Type.Equals(TEXT("text")))
		UBeamJsonUtils::DeserializeUObject(TEXT(""), Bag, Text, OuterOwner);
	if (Type.Equals(TEXT("binary")))
		UBeamJsonUtils::DeserializeUObject(TEXT(""), Bag, Binary, OuterOwner);
	
}

FString UBaseContentReference::GetCurrentType() const
{
	checkf((Content && !Text && !Binary) || 
		(Text && !Content && !Binary) || 
		(Binary && !Content && !Text), TEXT("You should always only have one of these set. Set the others as nullptr."))

	if (Content) return TEXT("content");
	if (Text) return TEXT("text");
	if (Binary) return TEXT("binary");
	
	return TEXT("");
}

