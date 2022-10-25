
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/StatsSubscribeRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutSubscribeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutSubscribeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatsSubscribeRequestBody* Body;

	// Beam Base Request Declaration
	UPutSubscribeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make PutSubscribe",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutSubscribeRequest* Make(FString _Service, TArray<FString> _Subscriptions, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSubscribeSuccess, FBeamRequestContext, Context, UPutSubscribeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSubscribeError, FBeamRequestContext, Context, UPutSubscribeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutSubscribeComplete, FBeamRequestContext, Context, UPutSubscribeRequest*, Request);

using FPutSubscribeFullResponse = FBeamFullResponse<UPutSubscribeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutSubscribeFullResponse, FPutSubscribeFullResponse);
