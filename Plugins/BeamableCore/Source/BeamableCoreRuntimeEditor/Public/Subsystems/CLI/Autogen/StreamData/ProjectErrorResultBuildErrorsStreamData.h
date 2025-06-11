
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorResultBuildErrorsStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectErrorResultBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Level = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FormattedMessage = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Uri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Line = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("level"), Level, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("formattedMessage"), FormattedMessage, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("column"), Column, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("level"), Level, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("formattedMessage"), FormattedMessage, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("column"), Column, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("level")), Level);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("formattedMessage")), FormattedMessage);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uri")), Uri);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("line")), Line);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("column")), Column);	
	}
};


