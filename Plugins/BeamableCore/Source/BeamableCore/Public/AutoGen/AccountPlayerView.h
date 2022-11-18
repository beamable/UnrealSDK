
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfExternalIdentity.h"

#include "AccountPlayerView.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountPlayerView : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids", Category="Beam")
	TArray<FString> DeviceIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes", Category="Beam")
	TArray<FString> Scopes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party App Associations", Category="Beam")
	TArray<FString> ThirdPartyAppAssociations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalString Language;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	FOptionalArrayOfExternalIdentity External;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};