
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/SteamOrderInfoItem.h"

#include "SteamOrderInfoResponse.generated.h"

UCLASS(BlueprintType)
class USteamOrderInfoResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Usstate")
	FString Usstate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	TArray<USteamOrderInfoItem*> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Country")
	FString Country;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timecreated")
	FString Timecreated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transid")
	int64 Transid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status")
	FString Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Orderid")
	int64 Orderid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steamid")
	int64 Steamid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency")
	FString Currency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Time")
	FString Time;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};