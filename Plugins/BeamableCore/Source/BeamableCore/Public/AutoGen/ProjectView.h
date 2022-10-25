
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "ProjectView.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProjectView : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Name", Category="Beam")
	FString ProjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	FOptionalBool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret", Category="Beam")
	FOptionalString Secret;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent", Category="Beam")
	FOptionalString Parent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalInt64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children", Category="Beam")
	FOptionalArrayOfString Children;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};