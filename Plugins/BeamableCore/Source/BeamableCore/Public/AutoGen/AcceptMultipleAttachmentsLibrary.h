
#pragma once

#include "CoreMinimal.h"
#include "AcceptMultipleAttachments.h"

#include "AcceptMultipleAttachmentsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAcceptMultipleAttachmentsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AcceptMultipleAttachments To JSON String")
	static FString AcceptMultipleAttachmentsToJsonString(const UAcceptMultipleAttachments* Serializable, const bool Pretty);		
};