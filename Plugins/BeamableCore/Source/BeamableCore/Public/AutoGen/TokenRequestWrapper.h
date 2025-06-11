#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContextInfo.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalChallengeSolution.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "Serialization/BeamJsonUtils.h"

#include "TokenRequestWrapper.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTokenRequestWrapper : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Grant Type", Category="Beam")
	FString GrantType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Customer Scoped", Category="Beam")
	FOptionalBool bCustomerScoped = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id", Category="Beam")
	FOptionalString DeviceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Service", Category="Beam")
	FOptionalString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FOptionalString Token = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Code", Category="Beam")
	FOptionalString Code = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External Token", Category="Beam")
	FOptionalString ExternalToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Solution", Category="Beam")
	FOptionalChallengeSolution ChallengeSolution = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redirect Uri", Category="Beam")
	FOptionalString RedirectUri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party", Category="Beam")
	FOptionalString ThirdParty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Context", Category="Beam")
	FOptionalContextInfo Context = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token", Category="Beam")
	FOptionalString RefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Username", Category="Beam")
	FOptionalString Username = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Id", Category="Beam")
	FOptionalString ClientId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FOptionalString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope", Category="Beam")
	FOptionalArrayOfString Scope = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Init Properties", Category="Beam")
	FOptionalMapOfString InitProperties = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};