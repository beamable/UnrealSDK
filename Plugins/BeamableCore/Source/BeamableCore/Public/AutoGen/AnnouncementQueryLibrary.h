
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementQuery.h"

#include "AnnouncementQueryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementQuery To JSON String")
	static FString AnnouncementQueryToJsonString(const UAnnouncementQuery* Serializable, const bool Pretty);		
};