#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailTemplate.h"

#include "MailTemplateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailTemplateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailTemplate To JSON String")
	static FString MailTemplateToJsonString(const UMailTemplate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailTemplate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailTemplate* Make(FString Subject, FString Body, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailTemplate", meta=(NativeBreakFunc))
	static void Break(const UMailTemplate* Serializable, FString& Subject, FString& Body);
};