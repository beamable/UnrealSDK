#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Message.h"

#include "MessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="Message To JSON String")
	static FString MessageToJsonString(const UMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make Message", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Expires, PlayerRewards, Subject, Rewards, BodyRef, ClaimedTimeMs, Outer", NativeMakeFunc))
	static UMessage* Make(int64 ReceiverGamerTag, FString State, int64 Id, int64 SenderGamerTag, int64 Sent, FString Category, TArray<UAttachment*> Attachments, FOptionalString Body, FOptionalInt64 Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 BodyRef, FOptionalInt64 ClaimedTimeMs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break Message", meta=(NativeBreakFunc))
	static void Break(const UMessage* Serializable, int64& ReceiverGamerTag, FString& State, int64& Id, int64& SenderGamerTag, int64& Sent, FString& Category, TArray<UAttachment*>& Attachments, FOptionalString& Body, FOptionalInt64& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& BodyRef, FOptionalInt64& ClaimedTimeMs);
};