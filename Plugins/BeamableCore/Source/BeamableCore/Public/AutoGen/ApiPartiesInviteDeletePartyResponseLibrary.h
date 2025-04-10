#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInviteDeletePartyResponse.h"

#include "ApiPartiesInviteDeletePartyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiPartiesInviteDeletePartyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="ApiPartiesInviteDeletePartyResponse To JSON String")
	static FString ApiPartiesInviteDeletePartyResponseToJsonString(const UApiPartiesInviteDeletePartyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make ApiPartiesInviteDeletePartyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiPartiesInviteDeletePartyResponse* Make(UObject* Outer);

	
};