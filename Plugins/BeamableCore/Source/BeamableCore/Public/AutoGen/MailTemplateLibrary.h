
#pragma once

#include "CoreMinimal.h"
#include "MailTemplate.h"

#include "MailTemplateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailTemplateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailTemplate To JSON String")
	static FString MailTemplateToJsonString(const UMailTemplate* Serializable, const bool Pretty);		
};