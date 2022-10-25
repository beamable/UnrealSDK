
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ChatV2ObjectMessage.h"

#include "ChatV2ObjectMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChatV2ObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ChatV2ObjectMessage To JSON String")
	static FString ChatV2ObjectMessageToJsonString(const UChatV2ObjectMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ChatV2ObjectMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UChatV2ObjectMessage* Make(FString RoomId, int64 GamerTag, int64 TimestampMillis, FString CensoredContent, FGuid MessageId, FString Content, TMap<FString, FString> Reactions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ChatV2ObjectMessage", meta=(NativeBreakFunc))
	static void Break(const UChatV2ObjectMessage* Serializable, FString& RoomId, int64& GamerTag, int64& TimestampMillis, FString& CensoredContent, FGuid& MessageId, FString& Content, TMap<FString, FString>& Reactions);
};