#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInviteDeletePartyResponse.h"

#include "ApiPartiesInviteDeletePartyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPartiesInviteDeletePartyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ApiPartiesInviteDeletePartyResponse To JSON String")
	static FString ApiPartiesInviteDeletePartyResponseToJsonString(const UApiPartiesInviteDeletePartyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ApiPartiesInviteDeletePartyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPartiesInviteDeletePartyResponse* Make(UObject* Outer);

	
};