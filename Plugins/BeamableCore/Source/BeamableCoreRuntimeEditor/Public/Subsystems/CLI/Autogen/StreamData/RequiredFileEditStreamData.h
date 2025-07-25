
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "RequiredFileEditStreamData.generated.h"


UCLASS(BlueprintType)
class URequiredFileEditStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Code = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FilePath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplacementText = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OriginalText = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartIndex = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EndIndex = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Line = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("filePath"), FilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("replacementText"), ReplacementText, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("originalText"), OriginalText, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startIndex"), StartIndex, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("endIndex"), EndIndex, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("column"), Column, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("filePath"), FilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("replacementText"), ReplacementText, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("originalText"), OriginalText, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startIndex"), StartIndex, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("endIndex"), EndIndex, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("column"), Column, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("code"), Bag, Code);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("beamoId"), Bag, BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("title"), Bag, Title);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("description"), Bag, Description);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("filePath"), Bag, FilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("replacementText"), Bag, ReplacementText);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("originalText"), Bag, OriginalText);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startIndex"), Bag, StartIndex);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("endIndex"), Bag, EndIndex);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("line"), Bag, Line);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("column"), Bag, Column);	
	}
};


