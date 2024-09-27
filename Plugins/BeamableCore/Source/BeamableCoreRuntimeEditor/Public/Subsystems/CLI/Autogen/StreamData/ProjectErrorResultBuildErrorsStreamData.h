
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorResultBuildErrorsStreamData.generated.h"


UCLASS()
class UProjectErrorResultBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Level = {};
	UPROPERTY()
	FString FormattedMessage = {};
	UPROPERTY()
	FString Uri = {};
	UPROPERTY()
	int32 Line = {};
	UPROPERTY()
	int32 Column = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("level"), Level);
		Serializer->WriteValue(TEXT("formattedMessage"), FormattedMessage);
		Serializer->WriteValue(TEXT("uri"), Uri);
		Serializer->WriteValue(TEXT("line"), Line);
		Serializer->WriteValue(TEXT("column"), Column);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("level"), Level);
		Serializer->WriteValue(TEXT("formattedMessage"), FormattedMessage);
		Serializer->WriteValue(TEXT("uri"), Uri);
		Serializer->WriteValue(TEXT("line"), Line);
		Serializer->WriteValue(TEXT("column"), Column);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Level = Bag->GetStringField(TEXT("level"));
		FormattedMessage = Bag->GetStringField(TEXT("formattedMessage"));
		Uri = Bag->GetStringField(TEXT("uri"));
		Line = Bag->GetIntegerField(TEXT("line"));
		Column = Bag->GetIntegerField(TEXT("column"));	
	}
};


