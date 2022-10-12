
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalContextInfo.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "TokenRequestWrapper.generated.h"

UCLASS(BlueprintType)
class UTokenRequestWrapper : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id")
	FOptionalString DeviceId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Username")
	FOptionalString Username;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope")
	FOptionalArrayOfString Scope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token")
	FOptionalString RefreshToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Context")
	FOptionalContextInfo Context;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party")
	FOptionalString ThirdParty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redirect Uri")
	FOptionalString RedirectUri;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Id")
	FOptionalString ClientId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Code")
	FOptionalString Code;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	FOptionalString Token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Customer Scoped")
	FOptionalBool bCustomerScoped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Grant Type")
	FString GrantType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password")
	FOptionalString Password;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};