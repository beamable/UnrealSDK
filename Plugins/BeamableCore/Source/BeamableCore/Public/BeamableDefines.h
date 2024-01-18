#pragma once

/**
 * @brief Semantic separation for longs representing a Beamable Request Id.
 * Every request sent out from any of the UBeam***Api subsystems gets one of these.
 */
typedef int64 FBeamRequestId;

// Defines here are meant to be used with the OnlineSubsystemBeamable plugin.
namespace OSS
{

	// Use this for FOnlineAccountCredentials::Type, for signing up with Email/Password 
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL
#define OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL() FString(TEXT("signup_email"))
#endif
	
	// Use this for FOnlineAccountCredentials::Type, for Email/Password 
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_EMAIL
#define OSS_BEAMABLE_IDENTITY_TYPE_EMAIL() FString(TEXT("email"))
#endif

	// Use this for FOnlineAccountCredentials::Type, for federated identity via microservice
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED
#define OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED(ServiceName, Namespace) FString::Printf(TEXT("extern_%s/%s"), *ServiceName, *Namespace)
#endif
}
