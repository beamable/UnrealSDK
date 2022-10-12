

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfAnnouncementAttachment.h"

#include "OptionalArrayOfAnnouncementAttachmentLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAnnouncementAttachmentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfAnnouncementAttachment MakeOptionalArrayOfAnnouncementAttachment(TArray<UAnnouncementAttachment*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UAnnouncementAttachment*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfAnnouncementAttachment Conv_OptionalArrayOfAnnouncementAttachmentFromValue(TArray<UAnnouncementAttachment*> Value);
};
