
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestNotificationRequestArgs.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "MSPlaygroundTestNotificationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMSPlaygroundTestNotificationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTestNotificationRequestArgs* Body = {};

	// Beam Base Request Declaration
	UMSPlaygroundTestNotificationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|MSPlayground|Utils|Make/Break", DisplayName="Make MSPlaygroundTestNotification",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UMSPlaygroundTestNotificationRequest* Make(FString _A, FString _B, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundTestNotificationSuccess, FBeamRequestContext, Context, UMSPlaygroundTestNotificationRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMSPlaygroundTestNotificationError, FBeamRequestContext, Context, UMSPlaygroundTestNotificationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMSPlaygroundTestNotificationComplete, FBeamRequestContext, Context, UMSPlaygroundTestNotificationRequest*, Request);

using FMSPlaygroundTestNotificationFullResponse = FBeamFullResponse<UMSPlaygroundTestNotificationRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnMSPlaygroundTestNotificationFullResponse, FMSPlaygroundTestNotificationFullResponse);
