
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementDto.h"

#include "AnnouncementDtoLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementDtoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementDto To JSON String")
	static FString AnnouncementDtoToJsonString(const UAnnouncementDto* Serializable, const bool Pretty);		
};