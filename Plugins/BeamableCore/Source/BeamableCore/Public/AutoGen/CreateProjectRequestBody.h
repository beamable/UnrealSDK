
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "CreateProjectRequestBody.generated.h"

UCLASS(BlueprintType)
class UCreateProjectRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Plan")
	FOptionalString Plan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded")
	FOptionalBool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent")
	FOptionalString Parent;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};