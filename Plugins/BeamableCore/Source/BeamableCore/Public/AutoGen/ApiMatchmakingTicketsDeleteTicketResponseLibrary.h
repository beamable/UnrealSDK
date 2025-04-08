#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiMatchmakingTicketsDeleteTicketResponse.h"

#include "ApiMatchmakingTicketsDeleteTicketResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiMatchmakingTicketsDeleteTicketResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ApiMatchmakingTicketsDeleteTicketResponse To JSON String")
	static FString ApiMatchmakingTicketsDeleteTicketResponseToJsonString(const UApiMatchmakingTicketsDeleteTicketResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ApiMatchmakingTicketsDeleteTicketResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiMatchmakingTicketsDeleteTicketResponse* Make(UObject* Outer);

	
};