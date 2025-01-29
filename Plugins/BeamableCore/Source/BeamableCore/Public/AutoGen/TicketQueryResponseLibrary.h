#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"

#include "TicketQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTicketQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TicketQueryResponse To JSON String")
	static FString TicketQueryResponseToJsonString(const UTicketQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TicketQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Results, Outer", NativeMakeFunc))
	static UTicketQueryResponse* Make(FOptionalArrayOfTicket Results, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TicketQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UTicketQueryResponse* Serializable, FOptionalArrayOfTicket& Results);
};