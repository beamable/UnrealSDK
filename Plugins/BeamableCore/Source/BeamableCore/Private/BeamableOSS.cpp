#include "BeamableOSS.h"

#include "OnlineSubsystem.h"
#include "UserSlots/BeamUserSlots.h"

void BeamOSS::InitializeOnlineSubsystemBeamable(IOnlineSubsystem* OnlineSubsystemInterface, UGameInstance* GameInstance)
{
	FString RawName = OSS_BEAMABLE_GAME_INSTANCE();
	OnlineSubsystemInterface->SetNamedInterface(FName(RawName), GameInstance);
}

FString BeamOSS::GetIdentityTypeSignUpEmail()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL();
	return Type;
}

FString BeamOSS::GetIdentityTypeEmail()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_EMAIL();
	return Type;
}

FString BeamOSS::GetIdentityTypeFederated(FString ServiceName, FString Namespace)
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED(ServiceName, Namespace);
	return Type;
}
