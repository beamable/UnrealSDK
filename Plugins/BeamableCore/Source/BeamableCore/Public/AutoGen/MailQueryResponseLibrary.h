#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailQueryResponse.h"

#include "MailQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailQueryResponse To JSON String")
	static FString MailQueryResponseToJsonString(const UMailQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailQueryResponse* Make(int64 UnreadCount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UMailQueryResponse* Serializable, int64& UnreadCount);
};