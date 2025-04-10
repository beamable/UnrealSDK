#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AcceptMultipleAttachments.h"

#include "AcceptMultipleAttachmentsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAcceptMultipleAttachmentsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="AcceptMultipleAttachments To JSON String")
	static FString AcceptMultipleAttachmentsToJsonString(const UAcceptMultipleAttachments* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make AcceptMultipleAttachments", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAcceptMultipleAttachments* Make(TArray<int64> MailIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break AcceptMultipleAttachments", meta=(NativeBreakFunc))
	static void Break(const UAcceptMultipleAttachments* Serializable, TArray<int64>& MailIds);
};