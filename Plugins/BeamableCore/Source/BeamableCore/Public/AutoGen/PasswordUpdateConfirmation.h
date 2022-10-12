
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PasswordUpdateConfirmation.generated.h"

UCLASS(BlueprintType)
class UPasswordUpdateConfirmation : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Code")
	FString Code;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="New Password")
	FString NewPassword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FOptionalString Email;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};