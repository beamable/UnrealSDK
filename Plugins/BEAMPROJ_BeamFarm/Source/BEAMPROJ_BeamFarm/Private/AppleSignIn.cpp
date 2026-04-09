// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleSignIn.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineExternalUIInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"


void UAppleSignIn::LoginAppleSign(
    APlayerController* PlayerController,
    FOnAppleEventComplete OnLoginSuccess,
    FOnAppleEventComplete OnLoginFail)
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(APPLE_SUBSYSTEM);

    if (!OnlineSub)
    {
        UE_LOG(LogTemp, Error, TEXT("Apple OnlineSubsystem not found"));
        OnLoginFail.ExecuteIfBound();
        return;
    }

    IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
    IOnlineExternalUIPtr ExternalUI = OnlineSub->GetExternalUIInterface();

    if (!Identity.IsValid() || !ExternalUI.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Apple Identity or ExternalUI invalid"));
        OnLoginFail.ExecuteIfBound();
        return;
    }

    const int32 ControllerId =
        CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();

    Identity->AddOnLoginCompleteDelegate_Handle(
        ControllerId,
        FOnLoginCompleteDelegate::CreateLambda(
            [OnLoginFail, OnLoginSuccess](
                int32 LocalUserNum,
                bool bWasSuccessful,
                const FUniqueNetId& UserId,
                const FString& Error)
            {
                if (bWasSuccessful)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Apple Login Complete!"));
                    OnLoginSuccess.ExecuteIfBound();
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Apple Login failed: %s"), *Error);
                    OnLoginFail.ExecuteIfBound();
                }
            }
        )
    );

    ExternalUI->ShowLoginUI(
        ControllerId,
        true,   // bShowOnlineOnly
        false,  // bShowSkipButton
        FOnLoginUIClosedDelegate::CreateLambda(
            [OnLoginFail](FUniqueNetIdPtr UniqueId, const int ControllerIndex, const FOnlineError& Error)
            {
                if (!UniqueId.IsValid())
                {
                    UE_LOG(LogTemp, Warning, TEXT("Apple login UI closed without login"));
                    OnLoginFail.ExecuteIfBound();
                }
            }
        )
    );
}

FString UAppleSignIn::GetAppleUserToken(APlayerController* PlayerController)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(APPLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();

	UE_LOG(LogTemp, Warning, TEXT("PLAYER ID: %s"), *Identity->GetUniquePlayerId(ControllerId)->ToString());
	
	// Getting the token from the online subsystem
	return *Identity->GetAuthToken(ControllerId);
}