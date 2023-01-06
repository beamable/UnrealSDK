
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalBeamGamerTag.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalBeamAccountId.h"
#include "BeamBackend/SemanticTypes/BeamCid.h"
#include "AutoGen/Optionals/OptionalBeamPid.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "Token.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UToken : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FBeamCid Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FString Token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	int64 Created;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	FOptionalBeamGamerTag GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id", Category="Beam")
	FOptionalBeamAccountId AccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FOptionalBeamPid Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires Ms", Category="Beam")
	FOptionalInt64 ExpiresMs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform", Category="Beam")
	FOptionalString Platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device", Category="Beam")
	FOptionalString Device;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Revoked", Category="Beam")
	FOptionalBool bRevoked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes", Category="Beam")
	FOptionalArrayOfString Scopes;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};