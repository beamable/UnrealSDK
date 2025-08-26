#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "GetManifestDiffsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGetManifestDiffsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Id", Category="Beam")
	FBeamContentManifestId ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From Uid", Category="Beam")
	FOptionalString FromUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To Uid", Category="Beam")
	FOptionalString ToUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	FOptionalInt32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From Date", Category="Beam")
	FOptionalInt64 FromDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To Date", Category="Beam")
	FOptionalInt64 ToDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};