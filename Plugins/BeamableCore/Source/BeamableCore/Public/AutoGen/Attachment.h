
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EntitlementGenerator.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "Attachment.generated.h"

UCLASS(BlueprintType)
class UAttachment : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Wrapped")
	UEntitlementGenerator* Wrapped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Target")
	FOptionalInt64 Target;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};