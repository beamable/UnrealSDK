#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

#include "AuthV2JsonWebKey.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAuthV2JsonWebKey : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alg", Category="Beam")
	FOptionalString Alg = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="X5t S256", Category="Beam")
	FOptionalString X5tS256 = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="X5t", Category="Beam")
	FOptionalString X5t = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="X", Category="Beam")
	FOptionalString X = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Use", Category="Beam")
	FOptionalString Use = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Qi", Category="Beam")
	FOptionalString Qi = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Q", Category="Beam")
	FOptionalString Q = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="P", Category="Beam")
	FOptionalString P = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="X5u", Category="Beam")
	FOptionalString X5u = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="N", Category="Beam")
	FOptionalString N = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Kid", Category="Beam")
	FOptionalString Kid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="K", Category="Beam")
	FOptionalString K = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="E", Category="Beam")
	FOptionalString E = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dq", Category="Beam")
	FOptionalString Dq = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dp", Category="Beam")
	FOptionalString Dp = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="D", Category="Beam")
	FOptionalString D = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Crv", Category="Beam")
	FOptionalString Crv = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Kty", Category="Beam")
	FOptionalString Kty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Y", Category="Beam")
	FOptionalString Y = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Oth", Category="Beam")
	FOptionalArrayOfString Oth = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Key Ops", Category="Beam")
	FOptionalArrayOfString KeyOps = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="X5c", Category="Beam")
	FOptionalArrayOfString X5c = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};