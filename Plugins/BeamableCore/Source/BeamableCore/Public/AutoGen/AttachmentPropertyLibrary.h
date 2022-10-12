
#pragma once

#include "CoreMinimal.h"
#include "AttachmentProperty.h"

#include "AttachmentPropertyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAttachmentPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AttachmentProperty To JSON String")
	static FString AttachmentPropertyToJsonString(const UAttachmentProperty* Serializable, const bool Pretty);		
};