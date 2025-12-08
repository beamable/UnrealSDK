#pragma once

#include "CoreMinimal.h"
#include "GoogleSignIn.generated.h"


UCLASS(Blueprintable)
class UGoogleSignIn : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Initialize the Google subsystem to enable Google authentication
     * Returns true if initialization succeeded
     */
    UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static bool Initialize();

    /**
	  * Check if the user index is logged in.
	  */
    UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static bool IsLoggedIn(int32 index);
	
    /**
     * Get the access token for a specific user index
     */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static FString GetAccessToken(int32 index);
};