
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "AnnouncementState.generated.h"

UCLASS(BlueprintType)
class UAnnouncementState : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Read")
	bool bIsRead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Claimed")
	bool bIsClaimed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Deleted")
	bool bIsDeleted;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};