#pragma once
#include "AppleSignIn.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnAppleEventComplete);

UCLASS(Blueprintable)
class UAppleSignIn : public UObject
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple")
	static void Login(APlayerController* PlayerController, FOnAppleEventComplete OnLoginSuccess, FOnAppleEventComplete OnLoginFail);

	UFUNCTION(BlueprintCallable, Category = "Sign In | Apple")
	static FString GetUserId(APlayerController* PlayerController);

};
