#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"

#include "GoogleSignIn.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FGoogleUserData
{
    GENERATED_BODY()
    /*
     * The real name of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString RealName;
    /*
     * The display name of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString DisplayName;
    /*
     * The preferred display name of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString PreferredDisplayName;
    /*
     * The ID of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString ID;
    /*
     * The email of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString Email;
    /*
     * The alias of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString Alias;
    /*
     * The ID Token of the signed in user
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString IdToken;
};

/**
 * Response from a login process
 */
USTRUCT(BlueprintType)
struct FLoginCompletedResponse
{
	GENERATED_BODY()
    /*
     * Did the login process succeed
     */
	UPROPERTY(BlueprintReadWrite, Category="Sign In | Google")
    bool success;
    /*
     * If the process did not succeed, this field holds any errors
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FString Error;
    /*
     * Which local user is this for
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    int LocalUseNumber;
    /*
     * On successful login, this holds the signed in user's data
     */
    UPROPERTY(BlueprintReadWrite, Category = "Sign In | Google")
    FGoogleUserData UserData;
};
/*
 * Delegate for responses upon login process completion
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLoginCompletedCallback, FLoginCompletedResponse, LoginResponse);

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
     * Does the Google Subsystem exist and is initialized
     */
    UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static bool HasGoogleOnlineSubsystem() { return mOnlineSubsystem != nullptr; }
    /**
     * Do sign in using Google asynchronously and call callback on completion
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback utilized when method is called from Blueprints</param>
     */
    UFUNCTION(BlueprintCallable, Category = "Sign In | Google")
    static bool SignInWithGoogle(int LocalUserNumber, const FLoginCompletedCallback Callback);

private:
    static void LoginCompletedHandler(int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error, const FLoginCompletedCallback BPCallback);
    // Handle for keeping track of a google subsystem login process
    static FDelegateHandle LoginDelegateHandle;
    static IOnlineSubsystem* mOnlineSubsystem;
};