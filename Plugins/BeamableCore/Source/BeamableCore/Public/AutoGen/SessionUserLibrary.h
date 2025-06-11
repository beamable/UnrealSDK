#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionUser.h"

#include "SessionUserLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionUserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionUser To JSON String")
	static FString SessionUserToJsonString(const USessionUser* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionUser", meta=(DefaultToSelf="Outer", AdvancedDisplay="Cid, Heartbeat, Password, Outer", NativeMakeFunc))
	static USessionUser* Make(FString Name, FString Email, int64 GamerTag, FString Username, FString LastName, FString FirstName, int64 Id, FString Lang, FOptionalString Cid, FOptionalInt64 Heartbeat, FOptionalString Password, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionUser", meta=(NativeBreakFunc))
	static void Break(const USessionUser* Serializable, FString& Name, FString& Email, int64& GamerTag, FString& Username, FString& LastName, FString& FirstName, int64& Id, FString& Lang, FOptionalString& Cid, FOptionalInt64& Heartbeat, FOptionalString& Password);
};