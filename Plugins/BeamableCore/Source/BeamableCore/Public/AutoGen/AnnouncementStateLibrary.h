
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementState.h"

#include "AnnouncementStateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementState To JSON String")
	static FString AnnouncementStateToJsonString(const UAnnouncementState* Serializable, const bool Pretty);		
};