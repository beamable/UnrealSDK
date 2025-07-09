#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"

#include "OtelAuthConfig.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UOtelAuthConfig : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Endpoint", Category="Beam")
	FString Endpoint = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Username", Category="Beam")
	FString Username = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires At", Category="Beam")
	FOptionalDateTime ExpiresAt = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};