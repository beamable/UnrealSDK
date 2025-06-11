#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateMailRequestBody.h"

#include "UpdateMailRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateMailRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="UpdateMailRequestBody To JSON String")
	static FString UpdateMailRequestBodyToJsonString(const UUpdateMailRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make UpdateMailRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bAcceptAttachments, Body, Expires, Subject, State, Category, Outer", NativeMakeFunc))
	static UUpdateMailRequestBody* Make(int64 MailId, FOptionalBool bAcceptAttachments, FOptionalString Body, FOptionalString Expires, FOptionalString Subject, FOptionalString State, FOptionalString Category, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break UpdateMailRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateMailRequestBody* Serializable, int64& MailId, FOptionalBool& bAcceptAttachments, FOptionalString& Body, FOptionalString& Expires, FOptionalString& Subject, FOptionalString& State, FOptionalString& Category);
};