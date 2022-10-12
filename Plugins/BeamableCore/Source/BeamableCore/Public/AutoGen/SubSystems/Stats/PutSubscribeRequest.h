
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatsSubscribeRequestBody* Body;

	// Beam Base Request Declaration
	UPutSubscribeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutSubscribeRequest* MakePutSubscribeRequest(FString _Service, TArray<FString> _Subscriptions, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSubscribeSuccess, FBeamRequestContext, Context, UPutSubscribeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSubscribeError, FBeamRequestContext, Context, UPutSubscribeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutSubscribeComplete, FBeamRequestContext, Context, UPutSubscribeRequest*, Request);

using FPutSubscribeFullResponse = FBeamFullResponse<UPutSubscribeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutSubscribeFullResponse, FPutSubscribeFullResponse);
