
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponse.h"

#include "GetNotificationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetNotificationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetNotificationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make GetNotification",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetNotificationRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetNotificationSuccess, FBeamRequestContext, Context, UGetNotificationRequest*, Request, USubscriberDetailsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetNotificationError, FBeamRequestContext, Context, UGetNotificationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetNotificationComplete, FBeamRequestContext, Context, UGetNotificationRequest*, Request);

using FGetNotificationFullResponse = FBeamFullResponse<UGetNotificationRequest*, USubscriberDetailsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetNotificationFullResponse, FGetNotificationFullResponse);
