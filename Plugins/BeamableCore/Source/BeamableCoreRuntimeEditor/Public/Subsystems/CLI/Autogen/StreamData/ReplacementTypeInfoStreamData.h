
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ReplacementTypeInfoStreamData.generated.h"


UCLASS(BlueprintType)
class UReplacementTypeInfoStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReferenceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EngineReplacementType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EngineOptionalReplacementType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EngineImport = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceId"), ReferenceId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineReplacementType"), EngineReplacementType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineOptionalReplacementType"), EngineOptionalReplacementType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineImport"), EngineImport, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceId"), ReferenceId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineReplacementType"), EngineReplacementType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineOptionalReplacementType"), EngineOptionalReplacementType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EngineImport"), EngineImport, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ReferenceId"), Bag, ReferenceId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("EngineReplacementType"), Bag, EngineReplacementType);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("EngineOptionalReplacementType"), Bag, EngineOptionalReplacementType);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("EngineImport"), Bag, EngineImport);	
	}
};


