
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "RealmsBasicAccount.generated.h"

UCLASS(BlueprintType)
class URealmsBasicAccount : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User")
	FString User;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password")
	FString Password;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Projects")
	TArray<FString> Projects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	FOptionalInt64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};