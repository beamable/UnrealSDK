#include "GoogleSignIn.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"


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
		
		return true;
	}

	return false;
}

bool UGoogleSignIn::IsLoggedIn(int32 index)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	
	if (Identity.Get()->GetLoginStatus(index) != ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Error, TEXT("[GOOGLE] User is not logged in"));
		return false;
	}
	return true;
}

FString UGoogleSignIn::GetAccessToken(int32 index)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
        
	if (!IsLoggedIn(index)) return "";
        
	TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(index);
	
	TSharedPtr<FUserOnlineAccount> UserOnlineAccount = Identity->GetUserAccount(*UserId);
	
	if (!UserOnlineAccount.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GOOGLE] User account is invalid")); 
	}
        
	FString Token;
	UserOnlineAccount->GetAuthAttribute(AUTH_ATTR_ID_TOKEN, Token);
	return Token;
}