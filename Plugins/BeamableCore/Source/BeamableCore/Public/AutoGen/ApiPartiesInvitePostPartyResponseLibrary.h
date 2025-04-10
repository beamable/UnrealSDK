#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#include "ApiPartiesInvitePostPartyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPartiesInvitePostPartyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|4 - Json", DisplayName="ApiPartiesInvitePostPartyResponse To JSON String")
	static FString ApiPartiesInvitePostPartyResponseToJsonString(const UApiPartiesInvitePostPartyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|3 - Backend", DisplayName="Make ApiPartiesInvitePostPartyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPartiesInvitePostPartyResponse* Make(UObject* Outer);

	
};