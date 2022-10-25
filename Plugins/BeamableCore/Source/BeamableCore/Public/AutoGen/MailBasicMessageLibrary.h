
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/MailBasicMessage.h"

#include "MailBasicMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailBasicMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailBasicMessage To JSON String")
	static FString MailBasicMessageToJsonString(const UMailBasicMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailBasicMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Expires, PlayerRewards, Subject, Rewards, BodyRef, ClaimedTimeMs, Outer", NativeMakeFunc))
	static UMailBasicMessage* Make(int64 ReceiverGamerTag, FString State, int64 Id, int64 SenderGamerTag, int64 Sent, FString Category, TArray<UAttachment*> Attachments, FOptionalString Body, FOptionalInt32 Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 BodyRef, FOptionalInt64 ClaimedTimeMs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailBasicMessage", meta=(NativeBreakFunc))
	static void Break(const UMailBasicMessage* Serializable, int64& ReceiverGamerTag, FString& State, int64& Id, int64& SenderGamerTag, int64& Sent, FString& Category, TArray<UAttachment*>& Attachments, FOptionalString& Body, FOptionalInt32& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& BodyRef, FOptionalInt64& ClaimedTimeMs);
};