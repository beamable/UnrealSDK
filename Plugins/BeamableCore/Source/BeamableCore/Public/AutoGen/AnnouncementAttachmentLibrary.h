
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementAttachment.h"

#include "AnnouncementAttachmentLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementAttachmentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementAttachment To JSON String")
	static FString AnnouncementAttachmentToJsonString(const UAnnouncementAttachment* Serializable, const bool Pretty);		
};