
#pragma once

#include "CoreMinimal.h"
#include "AnnouncementQueryResponse.h"

#include "AnnouncementQueryResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAnnouncementQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AnnouncementQueryResponse To JSON String")
	static FString AnnouncementQueryResponseToJsonString(const UAnnouncementQueryResponse* Serializable, const bool Pretty);		
};