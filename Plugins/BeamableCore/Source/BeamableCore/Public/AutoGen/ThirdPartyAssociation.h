#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "ThirdPartyAssociation.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UThirdPartyAssociation : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User App Id", Category="Beam")
	FString UserAppId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="App Id", Category="Beam")
	FString AppId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta", Category="Beam")
	TMap<FString, FString> Meta = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FOptionalString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Business Id", Category="Beam")
	FOptionalString UserBusinessId = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};