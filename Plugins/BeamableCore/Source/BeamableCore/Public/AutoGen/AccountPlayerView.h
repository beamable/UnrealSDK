
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "AccountPlayerView.generated.h"

UCLASS(BlueprintType)
class UAccountPlayerView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FOptionalString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids")
	TArray<FString> DeviceIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes")
	TArray<FString> Scopes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party App Associations")
	TArray<FString> ThirdPartyAppAssociations;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};