
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ServerEvent.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "BasicNotificationPostServerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicNotificationPostServerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UServerEvent* Body = {};

	// Beam Base Request Declaration
	UBasicNotificationPostServerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make BasicNotificationPostServer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Payload,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicNotificationPostServerRequest* Make(FString _Event, bool _bToAll, FOptionalString _Payload, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicNotificationPostServerSuccess, FBeamRequestContext, Context, UBasicNotificationPostServerRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicNotificationPostServerError, FBeamRequestContext, Context, UBasicNotificationPostServerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicNotificationPostServerComplete, FBeamRequestContext, Context, UBasicNotificationPostServerRequest*, Request);

using FBasicNotificationPostServerFullResponse = FBeamFullResponse<UBasicNotificationPostServerRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicNotificationPostServerFullResponse, FBasicNotificationPostServerFullResponse);
