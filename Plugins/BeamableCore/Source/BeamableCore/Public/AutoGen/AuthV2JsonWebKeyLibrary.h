#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKey.h"

#include "AuthV2JsonWebKeyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2JsonWebKeyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2JsonWebKey To JSON String")
	static FString AuthV2JsonWebKeyToJsonString(const UAuthV2JsonWebKey* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2JsonWebKey", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alg, X5tS256, X5t, X, Use, Qi, Q, P, X5u, N, Kid, K, E, Dq, Dp, D, Crv, Kty, Y, Oth, KeyOps, X5c, Outer", NativeMakeFunc))
	static UAuthV2JsonWebKey* Make(FOptionalString Alg, FOptionalString X5tS256, FOptionalString X5t, FOptionalString X, FOptionalString Use, FOptionalString Qi, FOptionalString Q, FOptionalString P, FOptionalString X5u, FOptionalString N, FOptionalString Kid, FOptionalString K, FOptionalString E, FOptionalString Dq, FOptionalString Dp, FOptionalString D, FOptionalString Crv, FOptionalString Kty, FOptionalString Y, FOptionalArrayOfString Oth, FOptionalArrayOfString KeyOps, FOptionalArrayOfString X5c, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2JsonWebKey", meta=(NativeBreakFunc))
	static void Break(const UAuthV2JsonWebKey* Serializable, FOptionalString& Alg, FOptionalString& X5tS256, FOptionalString& X5t, FOptionalString& X, FOptionalString& Use, FOptionalString& Qi, FOptionalString& Q, FOptionalString& P, FOptionalString& X5u, FOptionalString& N, FOptionalString& Kid, FOptionalString& K, FOptionalString& E, FOptionalString& Dq, FOptionalString& Dp, FOptionalString& D, FOptionalString& Crv, FOptionalString& Kty, FOptionalString& Y, FOptionalArrayOfString& Oth, FOptionalArrayOfString& KeyOps, FOptionalArrayOfString& X5c);
};