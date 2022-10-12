

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfAttachmentRequestBody.h"

#include "OptionalArrayOfAttachmentRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAttachmentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfAttachmentRequestBody MakeOptionalArrayOfAttachmentRequestBody(TArray<UAttachmentRequestBody*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UAttachmentRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfAttachmentRequestBody Conv_OptionalArrayOfAttachmentRequestBodyFromValue(TArray<UAttachmentRequestBody*> Value);
};
