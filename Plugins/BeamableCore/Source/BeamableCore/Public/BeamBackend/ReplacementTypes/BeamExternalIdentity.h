#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamOptional.h"
#include "Dom/JsonObject.h"

#include "BeamExternalIdentity.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamExternalIdentity : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Id", Category="Beam")
	FString UserId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespace", Category="Beam")
	FString ProviderNamespace = {};	
	
	FBeamExternalIdentity() = default;

	friend bool operator==(const FBeamExternalIdentity& Lhs, const FBeamExternalIdentity& RHS)
	{
		return Lhs.ProviderNamespace.Equals(RHS.ProviderNamespace) && Lhs.ProviderService.Equals(RHS.ProviderService) && Lhs.UserId.Equals(RHS.UserId);
	}

	friend bool operator!=(const FBeamExternalIdentity& Lhs, const FBeamExternalIdentity& RHS)
	{
		return !(Lhs == RHS);
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ProviderService   = Bag->GetStringField(TEXT("providerService"));
		UserId            = Bag->GetStringField(TEXT("userId"));
		ProviderNamespace = Bag->GetStringField(TEXT("providerNamespace"));
	}
};
