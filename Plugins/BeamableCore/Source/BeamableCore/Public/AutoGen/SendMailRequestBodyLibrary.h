#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendMailRequestBody.h"

#include "SendMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="SendMailRequestBody To JSON String")
	static FString SendMailRequestBodyToJsonString(const USendMailRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make SendMailRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Expires, PlayerRewards, Subject, Rewards, Id, BodyRef, Attachments, Outer", NativeMakeFunc))
	static USendMailRequestBody* Make(int64 ReceiverGamerTag, int64 SenderGamerTag, FString Category, FOptionalString Body, FOptionalString Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 Id, FOptionalInt64 BodyRef, FOptionalArrayOfAttachmentRequestBody Attachments, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break SendMailRequestBody", meta=(NativeBreakFunc))
	static void Break(const USendMailRequestBody* Serializable, int64& ReceiverGamerTag, int64& SenderGamerTag, FString& Category, FOptionalString& Body, FOptionalString& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& Id, FOptionalInt64& BodyRef, FOptionalArrayOfAttachmentRequestBody& Attachments);
};