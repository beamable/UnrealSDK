
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/PingRsp.h"

#include "GetPingRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPingRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPingRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetPingRequest* MakeGetPingRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPingSuccess, FBeamRequestContext, Context, UGetPingRequest*, Request, UPingRsp*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPingError, FBeamRequestContext, Context, UGetPingRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPingComplete, FBeamRequestContext, Context, UGetPingRequest*, Request);

using FGetPingFullResponse = FBeamFullResponse<UGetPingRequest*, UPingRsp*>;
DECLARE_DELEGATE_OneParam(FOnGetPingFullResponse, FGetPingFullResponse);
