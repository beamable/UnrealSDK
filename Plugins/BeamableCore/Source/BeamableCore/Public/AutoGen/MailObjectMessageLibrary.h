
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailObjectMessage.h"

#include "MailObjectMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailObjectMessage To JSON String")
	static FString MailObjectMessageToJsonString(const UMailObjectMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailObjectMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Expires, PlayerRewards, Subject, Rewards, BodyRef, ClaimedTimeMs, Outer", NativeMakeFunc))
	static UMailObjectMessage* Make(int64 ReceiverGamerTag, FString State, int64 Id, int64 SenderGamerTag, int64 Sent, FString Category, TArray<UAttachment*> Attachments, FOptionalString Body, FOptionalInt32 Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 BodyRef, FOptionalInt64 ClaimedTimeMs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailObjectMessage", meta=(NativeBreakFunc))
	static void Break(const UMailObjectMessage* Serializable, int64& ReceiverGamerTag, FString& State, int64& Id, int64& SenderGamerTag, int64& Sent, FString& Category, TArray<UAttachment*>& Attachments, FOptionalString& Body, FOptionalInt32& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& BodyRef, FOptionalInt64& ClaimedTimeMs);
};