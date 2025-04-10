#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendMailObjectRequestBody.h"

#include "SendMailObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMailObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="SendMailObjectRequestBody To JSON String")
	static FString SendMailObjectRequestBodyToJsonString(const USendMailObjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make SendMailObjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Expires, PlayerRewards, Subject, Rewards, Id, BodyRef, Attachments, Outer", NativeMakeFunc))
	static USendMailObjectRequestBody* Make(int64 SenderGamerTag, FString Category, FOptionalString Body, FOptionalString Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 Id, FOptionalInt64 BodyRef, FOptionalArrayOfAttachmentRequestBody Attachments, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break SendMailObjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const USendMailObjectRequestBody* Serializable, int64& SenderGamerTag, FString& Category, FOptionalString& Body, FOptionalString& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& Id, FOptionalInt64& BodyRef, FOptionalArrayOfAttachmentRequestBody& Attachments);
};