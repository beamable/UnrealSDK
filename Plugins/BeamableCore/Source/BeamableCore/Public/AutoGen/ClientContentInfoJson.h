#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamableCore/Public/AutoGen/Enums/ContentType.h"

#include "ClientContentInfoJson.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientContentInfoJson : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uri", Category="Beam")
	FString Uri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FString Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FBeamContentId ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EContentType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	TArray<FString> Tags = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};