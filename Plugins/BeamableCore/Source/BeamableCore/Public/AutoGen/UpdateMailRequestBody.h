
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "UpdateMailRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateMailRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mail Id", Category="Beam")
	int64 MailId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Accept Attachments", Category="Beam")
	FOptionalBool bAcceptAttachments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FOptionalString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires", Category="Beam")
	FOptionalString Expires;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subject", Category="Beam")
	FOptionalString Subject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State", Category="Beam")
	FOptionalString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category", Category="Beam")
	FOptionalString Category;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};