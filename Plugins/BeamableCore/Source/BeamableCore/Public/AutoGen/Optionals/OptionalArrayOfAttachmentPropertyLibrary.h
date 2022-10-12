

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfAttachmentProperty.h"

#include "OptionalArrayOfAttachmentPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAttachmentPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfAttachmentProperty MakeOptionalArrayOfAttachmentProperty(TArray<UAttachmentProperty*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UAttachmentProperty*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfAttachmentProperty Conv_OptionalArrayOfAttachmentPropertyFromValue(TArray<UAttachmentProperty*> Value);
};
