
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "UpdateMailRequestBody.generated.h"

UCLASS(BlueprintType)
class UUpdateMailRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FOptionalString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires")
	FOptionalString Expires;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subject")
	FOptionalString Subject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FOptionalString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mail Id")
	int64 MailId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Category")
	FOptionalString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Accept Attachments")
	FOptionalBool bAcceptAttachments;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};