
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "Token.generated.h"

UCLASS(BlueprintType)
class UToken : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Revoked")
	FOptionalBool bRevoked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	FOptionalInt64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes")
	FOptionalArrayOfString Scopes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id")
	FOptionalInt64 AccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	int64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid")
	FOptionalString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires Ms")
	FOptionalInt64 ExpiresMs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	FString Token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform")
	FOptionalString Platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device")
	FOptionalString Device;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	int64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};