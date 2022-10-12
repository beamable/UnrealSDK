
#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"

#include "AttachmentLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAttachmentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Attachment To JSON String")
	static FString AttachmentToJsonString(const UAttachment* Serializable, const bool Pretty);		
};