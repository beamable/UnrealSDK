
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/ServerEvent.h"
#include "AutoGen/CommonResponse.h"

#include "PostServerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UServerEvent* Body;

	// Beam Base Request Declaration
	UPostServerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Notification", DisplayName="Beam - Make PostServer",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Payload,Outer"))
	static UPostServerRequest* Make(FString _Event, bool _bToAll, FOptionalString _Payload, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServerSuccess, FBeamRequestContext, Context, UPostServerRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServerError, FBeamRequestContext, Context, UPostServerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServerComplete, FBeamRequestContext, Context, UPostServerRequest*, Request);

using FPostServerFullResponse = FBeamFullResponse<UPostServerRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostServerFullResponse, FPostServerFullResponse);
