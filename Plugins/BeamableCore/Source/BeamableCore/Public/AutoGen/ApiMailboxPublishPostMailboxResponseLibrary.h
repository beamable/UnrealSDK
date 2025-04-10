#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiMailboxPublishPostMailboxResponse.h"

#include "ApiMailboxPublishPostMailboxResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiMailboxPublishPostMailboxResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mailbox|Utils|Json", DisplayName="ApiMailboxPublishPostMailboxResponse To JSON String")
	static FString ApiMailboxPublishPostMailboxResponseToJsonString(const UApiMailboxPublishPostMailboxResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mailbox|Utils|Make/Break", DisplayName="Make ApiMailboxPublishPostMailboxResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiMailboxPublishPostMailboxResponse* Make(UObject* Outer);

	
};