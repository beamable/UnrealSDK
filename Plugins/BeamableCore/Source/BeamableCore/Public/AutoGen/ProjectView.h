#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamPid.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"
#include "BeamBackend/SemanticTypes/BeamPid.h"

#include "ProjectView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UProjectView : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Name", Category="Beam")
	FString ProjectName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FBeamPid Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	FOptionalBool bSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret", Category="Beam")
	FOptionalString Secret = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent", Category="Beam")
	FOptionalBeamPid Parent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalBeamCid Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children", Category="Beam")
	FOptionalArrayOfBeamPid Children = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};