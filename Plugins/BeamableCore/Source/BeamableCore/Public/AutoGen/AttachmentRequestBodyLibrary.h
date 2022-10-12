
#pragma once

#include "CoreMinimal.h"
#include "AttachmentRequestBody.h"

#include "AttachmentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAttachmentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AttachmentRequestBody To JSON String")
	static FString AttachmentRequestBodyToJsonString(const UAttachmentRequestBody* Serializable, const bool Pretty);		
};