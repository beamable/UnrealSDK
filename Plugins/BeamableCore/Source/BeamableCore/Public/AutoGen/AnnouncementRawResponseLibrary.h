
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementRawResponse.h"

#include "AnnouncementRawResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementRawResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementRawResponse To JSON String")
	static FString AnnouncementRawResponseToJsonString(const UAnnouncementRawResponse* Serializable, const bool Pretty);		
};