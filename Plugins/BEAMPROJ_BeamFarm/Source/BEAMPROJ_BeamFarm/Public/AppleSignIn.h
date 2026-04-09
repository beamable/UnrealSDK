// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AppleSignIn.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnAppleEventComplete);
/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMFARM_API UAppleSignIn : public UObject
{
	GENERATED_BODY()
	/**
	 * Login with apple sign in using the APPLE online subsystem.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple Sign")
	static void LoginAppleSign(APlayerController* PlayerController, FOnAppleEventComplete OnLoginSuccess,
	                    FOnAppleEventComplete OnLoginFail);
	
	/**
	 * Get the user id for the currently logged in user. That needs to be called after the login when it will be cached by the online subsystem
	 */
	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple Sign")
	static FString GetAppleUserToken(APlayerController* PlayerController);
};
