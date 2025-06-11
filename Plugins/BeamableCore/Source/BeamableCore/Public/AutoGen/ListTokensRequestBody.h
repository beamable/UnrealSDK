#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"

#include "ListTokensRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UListTokensRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page Size", Category="Beam")
	int32 PageSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page", Category="Beam")
	int32 Page = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Or Account Id", Category="Beam")
	int64 GamerTagOrAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalBeamCid Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FOptionalBeamPid Pid = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};