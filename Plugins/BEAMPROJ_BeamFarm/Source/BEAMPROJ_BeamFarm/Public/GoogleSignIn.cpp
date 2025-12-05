#include "GoogleSignIn.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"

IOnlineSubsystem* UGoogleSignIn::mOnlineSubsystem = nullptr;

FDelegateHandle UGoogleSignIn::LoginDelegateHandle = FDelegateHandle();

bool UGoogleSignIn::SignInWithGoogle(int LocalUserNumber, const FLoginCompletedCallback Callback)
{
	if(!HasGoogleOnlineSubsystem())
	{
		UE_LOG(LogTemp, Error, TEXT("Google SignIn not found"));
		return false;
	}

	if(mOnlineSubsystem->GetSubsystemName() != GOOGLE_SUBSYSTEM)
	{
		UE_LOG(LogTemp, Error, TEXT("subsystem %s not found"), *GOOGLE_SUBSYSTEM.ToString());
		return false;
	}

	if(LoginDelegateHandle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Login Delegate"));
        // Login is already in progress
		return false;
	}

	const IOnlineIdentityPtr IdentityInterface = mOnlineSubsystem->GetIdentityInterface();
	if(IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("IdentityInterface Fail"));
		return false;
	}

	if(IdentityInterface->GetLoginStatus(LocalUserNumber) == ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalUser %d is logged in"), LocalUserNumber);
        // User is already logged in
        return false;
	}

    // Add our method to be called upon login process completion and keep track of the handle
	LoginDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(
		LocalUserNumber, FOnLoginCompleteDelegate::CreateLambda(
			[Callback](int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				LoginCompletedHandler(LocalUserNumber, wasSuccessful, UserId, Error, Callback);
			}));

	IdentityInterface->Login(LocalUserNumber, FOnlineAccountCredentials{});
	return true;
}

void UGoogleSignIn::LoginCompletedHandler(int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error, const FLoginCompletedCallback Callback)
{
	if (!HasGoogleOnlineSubsystem())
	{
		Callback.ExecuteIfBound(FLoginCompletedResponse{ false, TEXT("No Subsystem set"), LocalUserNumber });
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = mOnlineSubsystem->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		Callback.ExecuteIfBound(FLoginCompletedResponse{ false, TEXT("Could not get Identity Interface"), LocalUserNumber });
		return;
	}

	if (!LoginDelegateHandle.IsValid())
	{
		Callback.ExecuteIfBound(FLoginCompletedResponse{ false, TEXT("Login handle was invalid"), LocalUserNumber });
		return;
	}

    // Clear the login handle and stop listening to callbacks for it
	IdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNumber, LoginDelegateHandle);
	LoginDelegateHandle.Reset();

	if (!wasSuccessful) {

		AsyncTask(ENamedThreads::GameThread, [Callback, wasSuccessful, Error, LocalUserNumber]()
			{
				Callback.ExecuteIfBound(FLoginCompletedResponse{ wasSuccessful, Error, LocalUserNumber });
			});
		return;
	}

	const TSharedPtr<FUserOnlineAccount> UserAccount = IdentityInterface->GetUserAccount(UserId);
	if(UserAccount == nullptr || !UserAccount.IsValid())
	{
		Callback.ExecuteIfBound(FLoginCompletedResponse{ false, TEXT("UserAccount was invalid"), LocalUserNumber });
		return;
	}

	FGoogleUserData UserData{
		UserAccount->GetRealName(),
		UserAccount->GetDisplayName(),
		"",
		UserAccount->GetUserId()->ToString(),
		"",
		"",
		""
	};
	UserAccount->GetAuthAttribute(AUTH_ATTR_ID_TOKEN, UserData.IdToken);
	FLoginCompletedResponse LoginResponse{
		wasSuccessful,
		Error,
		LocalUserNumber,
		UserData
	};

	Callback.ExecuteIfBound(LoginResponse);
}

bool UGoogleSignIn::Initialize()
{
	if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM))
	{
		if (OnlineSubsystem == nullptr)
		{
			return false;
		}
		if (!OnlineSubsystem->Init())
		{
			return false;
		}
        mOnlineSubsystem = OnlineSubsystem;
		return true;
	}

	return false;
}