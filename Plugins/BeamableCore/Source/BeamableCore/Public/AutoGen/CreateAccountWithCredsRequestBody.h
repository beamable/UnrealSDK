#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalChallengeSolution.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

#include "CreateAccountWithCredsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCreateAccountWithCredsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Username", Category="Beam")
	FOptionalString Username = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Solution", Category="Beam")
	FOptionalChallengeSolution ChallengeSolution = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External Token", Category="Beam")
	FOptionalString ExternalToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Service", Category="Beam")
	FOptionalString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FOptionalString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Init Properties", Category="Beam")
	FOptionalMapOfString InitProperties = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};