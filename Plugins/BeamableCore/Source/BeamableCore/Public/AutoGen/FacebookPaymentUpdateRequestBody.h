
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/FacebookUpdatedEntry.h"

#include "FacebookPaymentUpdateRequestBody.generated.h"

UCLASS(BlueprintType)
class UFacebookPaymentUpdateRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object")
	FString Object;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entry")
	TArray<UFacebookUpdatedEntry*> Entry;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};