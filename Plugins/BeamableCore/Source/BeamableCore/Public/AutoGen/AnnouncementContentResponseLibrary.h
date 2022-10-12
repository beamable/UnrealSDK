
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementContentResponse.h"

#include "AnnouncementContentResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementContentResponse To JSON String")
	static FString AnnouncementContentResponseToJsonString(const UAnnouncementContentResponse* Serializable, const bool Pretty);		
};