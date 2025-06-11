#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/ReplacementTypes/BeamRemoteContentManifestEntry.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "ClientManifestJsonResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UClientManifestJsonResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entries", Category="Beam")
	TArray<FBeamRemoteContentManifestEntry> Entries = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uid", Category="Beam")
	FOptionalString Uid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Publisher Account Id", Category="Beam")
	FOptionalInt64 PublisherAccountId = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};