#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "ContentTagFilter.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UContentTagFilter : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="All Of", Category="Beam")
	TArray<FString> AllOf = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Any Of", Category="Beam")
	TArray<FString> AnyOf = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="None Of", Category="Beam")
	TArray<FString> NoneOf = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};