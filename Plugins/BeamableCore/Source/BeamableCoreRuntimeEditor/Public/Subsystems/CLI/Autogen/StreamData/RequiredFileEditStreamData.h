
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
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("code")), Code);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("beamoId")), BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("title")), Title);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("description")), Description);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("filePath")), FilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("replacementText")), ReplacementText);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("originalText")), OriginalText);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startIndex")), StartIndex);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endIndex")), EndIndex);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("line")), Line);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("column")), Column);	
	}
};


