#pragma once
#include "GameCenterSignIn.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnGameCenterEventComplete);

UCLASS(Blueprintable)
class UGameCenterSignIn : public UObject
{
	GENERATED_BODY()

	
public:
	/**
	 * Login to Game Center using the IOS online subsystem.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple Game Center")
	static void LoginGameCenter(APlayerController* PlayerController, FOnGameCenterEventComplete OnLoginSuccess, FOnGameCenterEventComplete OnLoginFail);

	/**
	 * Get the user id for the currently logged in user. That needs to be called after the login when it will be cached by the online subsystem
	 */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple Game Center")
	static FString GetGameCenterUserId(APlayerController* PlayerController);

};
