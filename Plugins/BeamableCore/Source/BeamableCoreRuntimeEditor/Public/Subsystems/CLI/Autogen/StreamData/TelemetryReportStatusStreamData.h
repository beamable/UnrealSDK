
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "TelemetryReportStatusStreamData.generated.h"


UCLASS(BlueprintType)
class UTelemetryReportStatusStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FilePath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Success = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ErrorMessage = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FilePath"), FilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Success"), Success, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ErrorMessage"), ErrorMessage, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FilePath"), FilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Success"), Success, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ErrorMessage"), ErrorMessage, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FilePath"), Bag, FilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Success"), Bag, Success);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ErrorMessage"), Bag, ErrorMessage);	
	}
};


