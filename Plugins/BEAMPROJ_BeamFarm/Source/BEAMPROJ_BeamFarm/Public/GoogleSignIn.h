#pragma once

#include "CoreMinimal.h"
#include "GoogleSignIn.generated.h"


UCLASS(Blueprintable)
class UGoogleSignIn : public UObject
{
    GENERATED_BODY()

public:
    /**
	  * Check if the user index is logged in.
	  */
    UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static bool IsLoggedIn(int32 index);
	
    /**
     * Get the access token for a specific user index
     * That needs to be called after the login when it will be cached by the online subsystem
     */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static FString GetAccessToken(int32 index);
};