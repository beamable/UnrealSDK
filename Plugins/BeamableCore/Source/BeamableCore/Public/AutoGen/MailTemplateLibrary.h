#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailTemplate.h"

#include "MailTemplateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailTemplateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailTemplate To JSON String")
	static FString MailTemplateToJsonString(const UMailTemplate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailTemplate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailTemplate* Make(FString Subject, FString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailTemplate", meta=(NativeBreakFunc))
	static void Break(const UMailTemplate* Serializable, FString& Subject, FString& Body);
};