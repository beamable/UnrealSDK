#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetTemplateRequestBody.h"

#include "GetTemplateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetTemplateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="GetTemplateRequestBody To JSON String")
	static FString GetTemplateRequestBodyToJsonString(const UGetTemplateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make GetTemplateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetTemplateRequestBody* Make(FString TemplateName, int64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break GetTemplateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetTemplateRequestBody* Serializable, FString& TemplateName, int64& GamerTag);
};