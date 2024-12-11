
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ProjectErrorResultErrorRunFailErrorOutputStreamData.generated.h"


UCLASS(BlueprintType)
class UProjectErrorResultErrorRunFailErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
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


