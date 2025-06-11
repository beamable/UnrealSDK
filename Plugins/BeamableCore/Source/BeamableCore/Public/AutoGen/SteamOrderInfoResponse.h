#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoItem.h"

#include "SteamOrderInfoResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USteamOrderInfoResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Usstate", Category="Beam")
	FString Usstate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country", Category="Beam")
	FString Country = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timecreated", Category="Beam")
	FString Timecreated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transid", Category="Beam")
	int64 Transid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FString Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Orderid", Category="Beam")
	int64 Orderid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steamid", Category="Beam")
	int64 Steamid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency", Category="Beam")
	FString Currency = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time", Category="Beam")
	FString Time = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items", Category="Beam")
	TArray<USteamOrderInfoItem*> Items = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};