#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AttachmentRequestBody.h"

#include "AttachmentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAttachmentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AttachmentRequestBody To JSON String")
	static FString AttachmentRequestBodyToJsonString(const UAttachmentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AttachmentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Quantity, Specialization, Target, Outer", NativeMakeFunc))
	static UAttachmentRequestBody* Make(FString Symbol, FString Action, FOptionalInt32 Quantity, FOptionalString Specialization, FOptionalInt64 Target, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AttachmentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAttachmentRequestBody* Serializable, FString& Symbol, FString& Action, FOptionalInt32& Quantity, FOptionalString& Specialization, FOptionalInt64& Target);
};