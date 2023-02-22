
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ContentReference.h"
#include "AutoGen/TextReference.h"
#include "AutoGen/BinaryReference.h"

#include "BaseContentReference.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBaseContentReference : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content", Category="Beam")
	UContentReference* Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Text", Category="Beam")
	UTextReference* Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Binary", Category="Beam")
	UBinaryReference* Binary;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	FString GetCurrentType() const;
};