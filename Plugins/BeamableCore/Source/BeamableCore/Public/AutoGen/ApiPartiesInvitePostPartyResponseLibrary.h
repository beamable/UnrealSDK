#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#include "ApiPartiesInvitePostPartyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPartiesInvitePostPartyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ApiPartiesInvitePostPartyResponse To JSON String")
	static FString ApiPartiesInvitePostPartyResponseToJsonString(const UApiPartiesInvitePostPartyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ApiPartiesInvitePostPartyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPartiesInvitePostPartyResponse* Make(UObject* Outer);

	
};