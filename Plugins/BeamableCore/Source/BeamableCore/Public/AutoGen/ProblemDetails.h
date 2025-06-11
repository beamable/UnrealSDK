#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "ProblemDetails.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UProblemDetails : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	FOptionalString Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FOptionalString Title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FOptionalInt32 Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Detail", Category="Beam")
	FOptionalString Detail = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Instance", Category="Beam")
	FOptionalString Instance = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};