#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionLanguageContext.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "StartSessionRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UStartSessionRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source", Category="Beam")
	FOptionalString Source = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard", Category="Beam")
	FOptionalString Shard = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Locale", Category="Beam")
	FOptionalString Locale = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Language", Category="Beam")
	FOptionalSessionLanguageContext Language = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time", Category="Beam")
	FOptionalInt64 Time = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform", Category="Beam")
	FOptionalString Platform = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer", Category="Beam")
	FOptionalInt64 Gamer = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device", Category="Beam")
	FOptionalString Device = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Params", Category="Beam")
	FOptionalMapOfString CustomParams = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Params", Category="Beam")
	FOptionalMapOfString DeviceParams = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};