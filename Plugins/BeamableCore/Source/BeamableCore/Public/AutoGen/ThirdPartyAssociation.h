
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "ThirdPartyAssociation.generated.h"

UCLASS(BlueprintType)
class UThirdPartyAssociation : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FOptionalString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Business Id")
	FOptionalString UserBusinessId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User App Id")
	FString UserAppId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta")
	TMap<FString, FString> Meta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="App Id")
	FString AppId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};